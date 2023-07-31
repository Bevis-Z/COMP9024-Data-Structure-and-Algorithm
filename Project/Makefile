CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -Werror -O0 -g
BIN		= crawler

ifneq ($(shell which dcc),)
	CC = dcc
endif

.PHONE: all clear

all: $(BIN) 

crawler: crawler.c graph.c queue.c stack.c set.c pqueue.c graph.h queue.h stack.h set.h pqueue.h
	$(CC) $(CFLAGS) -o $@ crawler.c graph.c queue.c stack.c set.c pqueue.c -lxml2 -lcurl -I/usr/include/libxml2

clear:
	rm -f $(BIN)
