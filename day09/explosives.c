#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int SRCE_MAX = 50000;
const int DEST_MAX = 500000;
/*
 * openPar -> number(w) -> times -> number(r) -> closePar
 * extract the pattern (if it's there)
 * then the w next chars form a pattern that should be inserted r times.
 * then start scanning again for openPar
 */

char *extractMarker(char *input, int *width, int *times) {
    char *c = input;
    *width = 0;
    *times = 0;
    if(*c++ != '(') return NULL;
    while(isdigit(*c)) {
        *width = *width * 10 + (*c - '0');
        c++;
    }
    if(*width == 0) return NULL;
    if(*c++ != 'x') return NULL;
    while(isdigit(*c)) {
        *times = *times * 10 + (*c - '0');
        c++;
    }
    if(*times == 0) return NULL;
    if(*c++ != ')') return NULL;
    return c;
}

long decompress(char *input) {
    char *srce = input;
    long result = 0;
    int width;
    int times;
    while(*srce != '\0') {
        char *pattern = extractMarker(srce, &width, &times);
        if(pattern == NULL) {
            srce++;
            result++;
        }
        else {
            char* excerpt = (char *)calloc(width+1, sizeof(char));
            strncpy(excerpt, pattern, width);
            long sub = decompress(excerpt);
            free(excerpt);
            result += times * sub;
            srce = pattern + width;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    char input[SRCE_MAX];
    if(argc < 2) {
        fprintf(stderr, "missing parameter: test <input> <expected> | <fileName>\n");
        return 1;
    }
    if(!strcmp(argv[1],"test")) {
        if(argc < 4) {
            fprintf(stderr, "incorrect parameter: test <input> <expected>\n");
            return 1;
        }
        long expected = atoi(argv[3]);
        strcpy(input, argv[2]);
        long output = decompress(input);
        if(expected != output) {
            fprintf(stderr, "expected: %ld, actual: %ld\n", expected, output);
            return 1;
        }
        return 0;
    }
    if(argc == 2) {
        FILE *puzzleFile;

        puzzleFile = fopen(argv[1], "r");
        if(puzzleFile == NULL) {
            fprintf(stderr, "can't open %s\n", argv[1]);
        }
        while(fgets(input, SRCE_MAX, puzzleFile)) {
            input[strcspn(input, "\n")] = 0;
            printf("%ld\n", decompress(input));
        }
        fclose(puzzleFile);
        return 0;
    }
    return 0;
}
