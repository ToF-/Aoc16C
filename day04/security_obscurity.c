#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_MAX 100

struct letter {
    char value;
    int  occurs;
};

int compare( const void* a, const void* b)
{
     struct letter letterA = *((struct letter *)a);
     struct letter letterB = *((struct letter *)b);

     if (letterA.occurs > letterB.occurs)
         return -1;
     if (letterA.occurs < letterB.occurs)
         return 1;
     return (letterA.value - letterB.value);
}

char rotateChar(char c, int n) {
    char result = c;
    if(isalpha(c)) {
        for(int i=0; i< (n%26); i++) {
            if(result < 'z')
                result++;
            else
                result = 'a';
        }
    }
    return result;
}

void rotate(char *s, int n) {
    for(char *p = s; *p; p++) {
        char c = *p;
        *p = c != '-' ? rotateChar(c, n) : ' ';
    }
}

int main(int argc, char *argv[]) {
    char line[LINE_MAX];
    char name[LINE_MAX];
    FILE *puzzleFile;

    struct letter letters[26];

    puzzleFile = fopen(argv[1], "r");
    int sum = 0;
    while(fgets(line, LINE_MAX, puzzleFile)) {
        for(int i = 0; i < 26; i++) {
            letters[i].value = 'a' + i;
            letters[i].occurs = 0;
        }
        char *p;
        int id = 0;
        memset(name, 0, LINE_MAX);
        char *n = name;
        for(p = line; *p != '['; p++, n++) {
            char c = *p;
            *n= c;
            *p = c;
            if(isalpha(c)) {
                letters[c-'a'].occurs++;
            }
            if(isdigit(c)) {
                id = id * 10 + (c-'0');
            }
        }
        rotate(name, id);
        qsort( letters, 26, sizeof(struct letter), compare );
        int valid = 1;
        p++;
        for(int i=0; *p != ']'; i++,p++) {
            char c = *p;
            valid &= c == letters[i].value;
        }
        sum += valid ? id : 0;
        if(valid)
            printf("name: %s\n", name); 

    }
    fclose(puzzleFile);
    return 0;
}
