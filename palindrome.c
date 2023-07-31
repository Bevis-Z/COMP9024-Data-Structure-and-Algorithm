/** Algorithm & Complexity Analysis
 *
 * Palindrome(A[],len):
 *
 * Input:  char A of n characters
 * Output: determine char A is palindrome or not
 *
 * Statement                                                    # primitive operations
 * ----------------------------------------------------------------------------------------
 * function isPalindrome
 *      for all i=0...n/2 do                                            n/2 + n/2 -1
 *          if (A[first_point + i] != A[second_point - i]) then         n/2
 *          return false                                                1
 *          end if
 *      end for
 *                                                                      O(n)
 * main
 *      A_length = len(A)                                                n
 *
 *      if isPalindrome:                                                 n
 *          print Yes
 *      end if
 *
 *      if not isPalindrome:                                             n
 *          print No
 *      end if
 *
 * -------------------------------------------------------------------------------------------
 *                                              Total: 3 O(n) + n , which is O(n)
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool isPalindrome(char A[], int len) {
    int first_point = 0;
    int second_point = len - 1;
    int count = len / 2;
    for(int i = 0; i < count; i++) {
        if(A[first_point + i] != A[second_point - i]) return false;
    }

    return true;
}


int main () {

    char *A = (char *) malloc (sizeof (char) * BUFSIZ);
//    char A[BUFSIZ];
    int len;

    printf("Enter a word: ");
    scanf("%s", A);
    len = strlen(A);

    if (isPalindrome(A, len)) printf("yes");
    if (!isPalindrome(A, len)) printf("no");

    free(A);
    return 0;
}


