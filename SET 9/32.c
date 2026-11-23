#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPS(char pattern[], int lps[]) {
    int m = strlen(pattern);
    int len = 0;
    int i = 1;

    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int *lps;
    int i = 0;
    int j = 0;
    int found = 0;

    if (m == 0)
        return;

    lps = (int *)malloc(m * sizeof(int));

    computeLPS(pattern, lps);

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found\n");

    free(lps);
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    KMP(text, pattern);

    return 0;
}