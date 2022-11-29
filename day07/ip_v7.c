#include <stdio.h>
#include <string.h>

#define LINE_MAX 300

#define FALSE 0
#define TRUE 1

int supportsTLS(char *s) {
    int within_hypernet_sequence = FALSE;
    int result = FALSE;
    for(int i=0; i < strlen(s)-4; i++) {
        if(s[i] == s[i+3] && s[i+1] == s[i+2] && s[i] != s[i+1]) {
            if(within_hypernet_sequence) {
                return FALSE;
            }
            result |= TRUE;
        }
        if(s[i] == '[') {
            within_hypernet_sequence = TRUE;
        } else if (s[i] == ']') {
            within_hypernet_sequence = FALSE;
        }
    }
    return result;
}

int supportSSL(char *s) {
    int within_hypernet_sequence = FALSE;
    char *abas[200];
    int  abasCount = 0;
    char *babs[200];
    int  babsCount = 0;

    for(int i=0; i < strlen(s)-3; i++) {
        if(s[i] != s[i+1] && s[i+2] == s[i]) {
            if(within_hypernet_sequence) {
                babs[babsCount++] = &s[i];
            }
            else {
                abas[abasCount++] = &s[i];
            }
        }
        if(s[i] == '[') {
            within_hypernet_sequence = TRUE;
        } else if (s[i] == ']') {
            within_hypernet_sequence = FALSE;
        }
    }
    if(babsCount == 0 || abasCount == 0) {
        return FALSE;
    }
    for(int j = 0; j < babsCount; j++) {
        for(int i = 0; i < abasCount; i++) {
            if(abas[i][0] == babs[j][1] && abas[i][1] == babs[j][0]) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    FILE *puzzleFile;
    char line[LINE_MAX];
    puzzleFile = fopen(argv[1], "r");
    int countTLS = 0;
    int countSSL = 0;
    while(fgets(line, LINE_MAX, puzzleFile)) {
        if(supportsTLS(line))
            countTLS++;
        if(supportSSL(line))
            countSSL++;
    }
    printf("%d %d\n", countTLS, countSSL);
    fclose(puzzleFile);
}
