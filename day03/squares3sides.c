#include <stdio.h>

#define LINE_MAX 20

int isTriangle(int a, int b, int c) {
    return (a+b > c && a+c > b && b+c > a);
}

int main(int argc, char *argv[]) {
    char line[LINE_MAX];
    FILE *puzzleFile;

    puzzleFile = fopen(argv[1], "r");
    int rowTriangles=0;
    int colTriangles=0;
    int rowNumber=0;
    int aa,ab,ac,ba,bb,bc,ca,cb,cc;
    while(fgets(line, LINE_MAX, puzzleFile) > 0) {
        int a,b,c;
        sscanf(line, "%d %d %d", &a, &b, &c);
        if (isTriangle(a, b, c))
            rowTriangles++;
        switch(rowNumber%3) {
            case 0:
                aa = a; ab = b; ac = c;
                break;
            case 1:
                ba = a; bb = b; bc = c;
                break;
            case 2:
                ca = a; cb = b; cc = c;
                if (isTriangle(aa, ba, ca)) colTriangles++;
                if (isTriangle(ab, bb, cb)) colTriangles++;
                if (isTriangle(ac, bc, cc)) colTriangles++;
                break;
        }
        rowNumber++;

    }
    fclose(puzzleFile);
    printf("part1: %d\n", rowTriangles);
    printf("part2: %d\n", colTriangles);
}
