#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct point {
    int x;
    int y;
};

#define MAXPOINT 1000
int MaxPoints = 0;

struct point Points[MAXPOINT];

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
    int minX  = INT_MAX;
    int maxX  = INT_MIN;
    int minY  = INT_MAX;
    int maxY  = INT_MIN;
    Points[MaxPoints].x = distX;
    Points[MaxPoints].y = distY;
    MaxPoints++;
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
        Points[MaxPoints].x = distX;
        Points[MaxPoints].y = distY;
        MaxPoints++;
        word = strtok(NULL, delim);
        minX = distX < minX ? distX : minX;
        maxX = distX > maxX ? distX : maxX;
        minY = distY < minY ? distY : minY;
        maxY = distY > maxY ? distY : maxY;
    }
    free(puzzle);
    int xOffset = -minX;
    int yOffset = -minY;
    int xLength = maxX-minX;
    int yLength = maxY-minY;
    char *cells = (char *)calloc(xLength*yLength, sizeof(char));
    memset(cells, 0, xLength*yLength);
    int distMin = INT_MAX;
    int x,y;
    for(int p = 0; p < MaxPoints-1; p++) {
        struct point start = Points[p];
        struct point end   = Points[p+1];
        if(start.y == end.y) {
            x = start.x;
            do {
                y = start.y;
                int i = x + xOffset;
                int j = y + yOffset;
                if(cells[j*xLength+i]) {
                    int dist = abs(i-xOffset) + abs(j-yOffset);
                    distMin = dist < distMin ? dist : distMin;
                }
                cells[j*xLength+i] = 1;
                x = start.x < end.x ? x+1 : x-1;
            }while(x != end.x);
        } else {
            y = start.y;
            do {
                x = start.x;
                int i = x + xOffset;
                int j = y + yOffset;
                if(cells[j*xLength+i]) {
                    int dist = abs(i-xOffset) + abs(j-yOffset);
                    distMin = dist < distMin ? dist : distMin;
                }
                cells[j*xLength+i] = 1;
                y = start.y < end.y ? y+1 : y-1;
            }while( y != end.y);
        }
    }
    free(cells);
    printf("distance to last (part 1): %d\n", abs(x) + abs(y));
    printf("distance min     (part 2): %d\n", distMin);
    return 0;
}
