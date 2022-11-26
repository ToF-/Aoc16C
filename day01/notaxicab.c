#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *puzzleFile;
    char *puzzle;

    puzzleFile = fopen(argv[1],"r");
    if(puzzleFile == NULL)
        return 1;

    fseek(puzzleFile, 0L, SEEK_END);
    int n = ftell(puzzleFile);
    fseek(puzzleFile, 0L, SEEK_SET);

    puzzle = (char *)calloc(n, sizeof(char));
    if(puzzle == NULL)
        return 1;

    fread(puzzle, sizeof(char), n, puzzleFile);
    fclose(puzzleFile);

    int directions[] = { 0,1,0,-1 };
    int distX = 0; int distY = 0;
    int dirX  = 0; int dirY  = 1;
    char delim[] = " ";
    char *word = strtok(puzzle, delim);
    while(word != NULL) {
        char direction = *word++;
        int length = atoi(word);
        switch(direction) {
            case 'R':
                dirX = dirX == 3 ? 0 : dirX+1;
                dirY = dirY == 3 ? 0 : dirY+1;
                break;
            case 'L':
                dirX = dirX == 0 ? 3 : dirX-1;
                dirY = dirY == 0 ? 3 : dirY-1;
                break;
        }
        distX += (directions[dirX] * length);
        distY += (directions[dirY] * length);
        word = strtok(NULL, delim);
    }
    free(puzzle);
    printf("%d\n", abs(distX) + abs(distY));
    return 0;
}
