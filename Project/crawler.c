/**
 * Use libcurl and libxml2 to create a web crawler
 *
 * derived from: https://raw.githubusercontent.com/curl/curl/master/docs/examples/crawler.c
 * curl project copyright: https://raw.githubusercontent.com/curl/curl/master/COPYING
 *
 * Written by: Dylan Brotherston <d.brotherston@unsw.edu.au>
 * Date: 2020/07/04
 *
 */

////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/uri.h>

#include "graph.h"
#include "pagerank.h"
#include "dijkstra.h"
#include "queue.h"
#include "set.h"

/* resizable buffer */
typedef struct memory {
    char *buf;
    size_t size;
} memory;

int do_crawl_command(string);
int do_pagerank_command(string, string, string);
int do_worstpath_command(string, string, string, string, string);
graph crawl(string);

bool is_html(string);
graph follow_link(string);
void find_links(queue, set, graph, memory *, string, string);
CURL *make_handle(string);
size_t grow_buffer(void *, size_t, size_t, void *);
void add_or_increment_edge(graph, string, string);
bool is_file(string);  
graph read_cache(string);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <url> (crawl | pagerank <damping> <delta> | worstpath <source-url> <dest-url> <damping> <delta>)\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Path option selected
    if (strcmp(argv[2], "crawl") == 0 && argc == 3) {
        return do_crawl_command(argv[1]);
    }
    
    // Pagerank option selected
    if (strcmp(argv[2], "pagerank") == 0 && argc == 5) {
        return do_pagerank_command(argv[1], argv[3], argv[4]);
    }
    
    // Worst path option selected
    if (strcmp(argv[2], "worstpath") == 0 && argc == 7) {
        return do_worstpath_command(argv[1], argv[3], argv[4], argv[5], argv[6]);
    }

    fprintf(stderr, "Usage: %s <url> (crawl | pagerank <damping> <delta> | worstpath <source-url> <dest-url> <damping> <delta>)\n", argv[0]);
    return EXIT_FAILURE;
}

int do_crawl_command(string url) {
    graph network = crawl(url);
    if (network == NULL) {
        return EXIT_FAILURE;
    }
    
    graph_show(network, stdout);
    graph_destroy(network);
    return EXIT_SUCCESS;
}

int do_pagerank_command(string url, string damping_s, string delta_s) {
    char *endptr = NULL;
    double damping_factor = strtod(damping_s, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "'%s' is not a floating point number\n", damping_s);
        return EXIT_FAILURE;
    }
    double delta = strtod(delta_s, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "'%s' is not a floating point number\n", delta_s);
        return EXIT_FAILURE;
    }

    graph network = crawl(url);
    if (network == NULL) {
        return EXIT_FAILURE;
    }
    
    graph_pagerank(network, damping_factor, delta);
    graph_show_pagerank(network, stdout);
    graph_destroy(network);
    
    return EXIT_SUCCESS;
}

int do_worstpath_command(string baseurl, string source, string dest, string damping_s, string delta_s) {
    char *endptr = NULL;
    double damping_factor = strtod(damping_s, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "'%s' is not a floating point number\n", damping_s);
        return EXIT_FAILURE;
    }
    double delta = strtod(delta_s, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "'%s' is not a floating point number\n", delta_s);
        return EXIT_FAILURE;
    }

    graph network = crawl(baseurl);
    if (network == NULL) {
        return EXIT_FAILURE;
    }
    
    if (!graph_has_vertex(network, source)) {
        fprintf(stderr, "'%s' is not a vertex in the network\n", dest);
        return EXIT_FAILURE;
    }
    if (!graph_has_vertex(network, dest)) {
        fprintf(stderr, "'%s' is not a vertex in the network\n", dest);
        return EXIT_FAILURE;
    }
    
    graph_worst_path(network, source, damping_factor, delta);
    graph_show_path(network, dest);
    graph_destroy(network);
    
    return EXIT_SUCCESS;
}

graph crawl(string url) {
    if (is_file(url)) {
        return read_cache(url);
    }

    // attempt some form on normalisation by removing any queries or fragments
    if (strchr(url, '?')) *strchr(url, '?') = '\0';
    if (strchr(url, '#')) *strchr(url, '#') = '\0';
    
    graph network = NULL;
    if (strstr(url, "cse.unsw.edu.au") || strstr(url, "localhost")) {
        network = follow_link(url);
    } else {
        fprintf(stderr, "refusing to touch non CSE pages.");
    }
    
    return network;
}

// webpage fetcher using libcurl
graph follow_link(string base_url) {
    curl_global_init(CURL_GLOBAL_ALL);
    queue q = queue_create();
    set visited = set_create();
    graph network = graph_create();
    queue_enqueue(q, base_url);
    set_insert(visited, base_url);
    while (!queue_empty(q)) {
        char *url, *ctype;
        memory *mem;
        base_url = queue_dequeue(q);
        CURL *handle = make_handle(base_url);
        CURLcode res = curl_easy_perform(handle);
        nanosleep(&(struct timespec){.tv_sec = 0, .tv_nsec = 500000000}, NULL);
        curl_easy_getinfo(handle, CURLINFO_CONTENT_TYPE, &ctype);
        curl_easy_getinfo(handle, CURLINFO_PRIVATE, &mem);
        curl_easy_getinfo(handle, CURLINFO_EFFECTIVE_URL, &url);

        if (res == CURLE_OK) {
            long res_status;
            curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &res_status);
            if (res_status == 200) {
                // printf("HTTP 200: %s\n", base_url);
                if (is_html(ctype)) {
                    find_links(q, visited, network, mem, url, base_url);
                }
            } else {
                fprintf(stderr, "HTTP %d: %s\n", (int)res_status, base_url);
            }
        } else {
            fprintf(stderr, "Connection failure: %s\n", base_url);
        }

        free(base_url);
        free(mem->buf);
        free(mem);
        curl_easy_cleanup(handle);
    }

    queue_destroy(q);
    set_destroy(visited);
    curl_global_cleanup();
    xmlCleanupParser();
    return network;
}

// HREF finder using libxml2
void find_links(queue q, set visited, graph network, memory *mem, string url, string base_url) {
    int opts = HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET;
    htmlDocPtr doc = htmlReadMemory(mem->buf, (int)mem->size, url, NULL, opts);
    if (!doc) return;

    xmlChar *xpath = (xmlChar*) "//a/@href";
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if (!result) {
        xmlFreeDoc(doc);
        return;
    }
    xmlNodeSetPtr nodeset = result->nodesetval;
    if (xmlXPathNodeSetIsEmpty(nodeset)) {
        xmlXPathFreeObject(result);
        xmlFreeDoc(doc);
        return;
    }

    for (int i = 0; i < nodeset->nodeNr; i++) {
        const xmlNode *node = nodeset->nodeTab[i]->xmlChildrenNode;
        xmlChar *href = xmlNodeListGetString(doc, node, 1);
        xmlChar *orig = href;
        href = xmlBuildURI(href, (xmlChar *) url);
        xmlFree(orig);
        char *link = (char *) href;
        if (!link) continue;
        // attempt some form on normalisation by removing any queries or fragments
        if (strchr(link, '?')) *strchr(link, '?') = '\0';
        if (strchr(link, '#')) *strchr(link, '#') = '\0';
        // we only want a map of hyperlinks, so restrict the scheme to http[s]
        if (!strncmp(link, "http://", 7) || !strncmp(link, "https://", 8)) {
            // use `base_url` not url as `url` has had redirects dereferenced
            add_or_increment_edge(network, base_url, link);
            // have some manners and restrict hyperlinks to domains inside UNSW CSE, and that we haven't already visited.
            if ((strstr(link, "cse.unsw.edu.au") || strstr(link, "localhost")) && !set_contains(visited, link)) {
                set_insert(visited, link);
                queue_enqueue(q, link);
            }
        }
        xmlFree(link);
    }
    xmlXPathFreeObject(result);
    xmlFreeDoc(doc);
}

size_t grow_buffer(void *contents, size_t sz, size_t nmemb, void *ctx) {
    size_t realsize = sz * nmemb;
    memory *mem = (memory*) ctx;
    char *ptr = realloc(mem->buf, mem->size + realsize);
    if(!ptr) {
        fprintf(stderr, "OOM\n");
        return 0;
    }
    mem->buf = ptr;
    memcpy(&(mem->buf[mem->size]), contents, realsize);
    mem->size += realsize;
    return realsize;
}

CURL *make_handle(char *url) {
    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url);

    /* buffer body */
    memory *mem = malloc(sizeof(memory));
    mem->size = 0;
    mem->buf = malloc(1);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, grow_buffer);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, mem);
    curl_easy_setopt(handle, CURLOPT_PRIVATE, mem);

    /* For completeness */
    curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 10L);
    curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 2L);
    curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(handle, CURLOPT_FILETIME, 1L);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "COMP9024 crawler");
    curl_easy_setopt(handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    curl_easy_setopt(handle, CURLOPT_UNRESTRICTED_AUTH, 1L);
    curl_easy_setopt(handle, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
    curl_easy_setopt(handle, CURLOPT_EXPECT_100_TIMEOUT_MS, 0L);
    return handle;
}

bool is_html(string ctype) {
    return ctype != NULL && strstr(ctype, "text/html");
}

void add_or_increment_edge(graph g, string vertex1, string vertex2) {
    if (!graph_has_vertex(g, vertex1)) graph_add_vertex(g, vertex1);
    if (!graph_has_vertex(g, vertex2)) graph_add_vertex(g, vertex2);

    if (!graph_has_edge(g, vertex1, vertex2)) graph_add_edge(g, vertex1, vertex2,   1);
    else graph_update_edge(g, vertex1, vertex2,  graph_get_edge(g, vertex1, vertex2) + 1);
}

bool is_file(string filename)  {
    FILE *fp = fopen(filename, "r");

    if (fp != NULL) {
        fclose(fp);
        return true;
    }

    return false;
}

graph read_cache(string url) {
    FILE *cache = fopen(url, "r");
    if (!cache) return NULL;

    graph network = graph_create();
    if (!network) return NULL;

    char input_buffer[BUFSIZ];
    while (fgets(input_buffer, BUFSIZ, cache)) {

        if (!strchr(input_buffer, '\n')) {
            fprintf(stderr, "Line too Long: aborting reading cache file.\n");
            return NULL;
        }
        // split the line into an array of tokens
        size_t  n_tok = 1;
        char **toks = malloc(n_tok * sizeof(*toks));
        toks[n_tok - 1] = strtok(input_buffer, " \t\n");
        char *t = NULL;
        while ((t = strtok(NULL, " \t\n"))) {
            n_tok++;
            toks = realloc(toks, n_tok * sizeof(*toks));
            toks[n_tok - 1] = t;
        }
        switch (n_tok) {
            case 1: {
                graph_add_vertex(network, toks[0]);
                break;
            }
            case 3: {
                char *endptr = NULL;
                weight wt =  strtod(toks[2], &endptr);
                if (*endptr != '\0') {
                    fprintf(stderr, "weight is not numeric.\n");
                    free(toks);
                    graph_destroy(network);
                    return NULL;
                } else {
                    graph_add_edge(network, toks[0], toks[1], wt);
                }
                break;
            }
            default: {
                fprintf(stderr, "Line has incorrect number of tokens.\n");
                free(toks);
                graph_destroy(network);
                return NULL;
            }
        }
        free(toks);
    }

    fclose(cache);
    return network;
}
