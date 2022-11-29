#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_MAX 1000
#define COL_MAX 8

char Message[ROW_MAX][COL_MAX];

int main(int argc, char *argv[]) {
    char line[COL_MAX+1];
    FILE *puzzleFile;
    puzzleFile = fopen(argv[1], "r");
    int maxRow = 0;
    int colSize;
    while(fgets(line, COL_MAX+1, puzzleFile)) {
        colSize = strlen(line);
        if(colSize) {
            strncpy(Message[maxRow], line, colSize);
            maxRow++;
        }
    }
    for(int j=0; j<COL_MAX; j++) {
        int occurs[26] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
        for(int i=0; i<maxRow; i++) {
            int letter = Message[i][j] - 'a';
            occurs[letter]++;
        }
        int max = 0;
        int min = 1000;
        char key_max;
        char key_min;
        for(int i=0; i<26; i++) {
            if(occurs[i] > max) {
                max = occurs[i];
                key_max = i + 'a';
            }
            if(occurs[i] > 0 && occurs[i] < min) {
                min = occurs[i];
                key_min = i + 'a';
            }
        }
        printf("%c %c\n",key_max, key_min);
    }
    printf("\n");
    fclose(puzzleFile);
}


