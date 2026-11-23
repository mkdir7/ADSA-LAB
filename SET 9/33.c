#include <stdio.h>
#include <string.h>

void badCharacterTable(char pattern[], int badChar[]) {
    int m = strlen(pattern);
    int i;

    for (i = 0; i < 256; i++)
        badChar[i] = -1;

    for (i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

void boyerMoore(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badChar[256];
    int shift = 0;
    int j;
    int found = 0;

    if (m == 0)
        return;

    if (m > n) {
        printf("Pattern not found\n");
        return;
    }

    badCharacterTable(pattern, badChar);

    while (shift <= n - m) {
        j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", shift);
            found = 1;

            if (shift + m < n)
                shift += m - badChar[(unsigned char)text[shift + m]];
            else
                shift++;
        } else {
            int move = j - badChar[(unsigned char)text[shift + j]];

            if (move < 1)
                move = 1;

            shift += move;
        }
    }

    if (!found)
        printf("Pattern not found\n");
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    boyerMoore(text, pattern);

    return 0;
}