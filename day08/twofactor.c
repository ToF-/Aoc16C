#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINE_MAX 30
#define FALSE 0
#define TRUE 0

void rect(char screen[6][50], int cols, int rows) {
    for(int r=0; r<rows; r++) {
        for(int c=0; c<cols; c++) {
            screen[r][c] = '*';
        }
    }
}

void rotateCol(char screen[6][50], int col, int row) {
    for(int i=0; i<row; i++) {
        int temp = screen[5][col];
        for(int r=5; r>0; r--) {
            screen[r][col] = screen[r-1][col];
        }
        screen[0][col] = temp;
    }
}


void rotateRow(char screen[6][50], int row, int col) {
    for(int i=0; i<col; i++) {
        int temp = screen[row][49];
        for(int c=49; c>0; c--) {
            screen[row][c] = screen[row][c-1];
        }
        screen[row][0] = temp;
    }
}

void printScreen(char screen[6][50]) {
    for(int r=0; r<6; r++) {
        for(int c=0; c<50; c++) {
            printf("%c", screen[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void initScreen(char screen[6][50]) {
    for(int r=0; r<6; r++) {
        for(int c=0; c<50; c++) {
            screen[r][c] = '.';
        }
    }
}

int countPixels(char screen[6][50]) {
    int result = 0;
    for(int r = 0; r<6; r++)
        for(int c = 0; c<50; c++)
            if(screen[r][c] == '*')
                result++;
    return result;
}

int main(int argc, char *argv[]) {
    char line[LINE_MAX];
    FILE *puzzleFile;
    int col, row;

    char screen[6][50];
    initScreen(screen);

    puzzleFile = fopen(argv[1], "r");
    if(puzzleFile == NULL) {
        fprintf(stderr, "can't open %s\n", argv[1]);
    }
    printScreen(screen);
    while(fgets(line, LINE_MAX, puzzleFile)) {
        if(sscanf(line, "rect %dx%d", &col,&row)) {
            rect(screen, col, row);
            printScreen(screen);
        }
        else if(sscanf(line, "rotate column x=%d by %d", &col,&row)) {
            rotateCol(screen, col, row);
            printScreen(screen);
        }
        else if(sscanf(line, "rotate row y=%d by %d", &row,&col)) {
            rotateRow(screen, row, col);
            printScreen(screen);
        }
    }
    printf("%d\n", countPixels(screen));
    fclose(puzzleFile);
    return 0;
}
