#include <stdio.h>
#include <string.h>

#define LINE_MAX 1000

char keypad[] = "################123####456####789##########################1#####234###56789###ABC#####D##########";

int main(int argc, char *argv[]) {
    char line[LINE_MAX];
    FILE *puzzleFile;
    for(int part = 0; part < 2; part++) {
        int x = 0; int y = 0;
        puzzleFile = fopen(argv[1],"r");

        while(keypad[part*49+y*7+x] != '5') {
            x++;
            if(x > 6) {
                x = 0;
                y++;
            }
        }
        printf("part %d:\n", part+1);
        for(int i=0; i<7; i++) {
            for(int j=0; j<7; j++) {
                printf("%c", keypad[part*49+i*7+j]);
            }
            printf("\n");
        }
        printf("x=%d,y=%d\n",x,y);
        while(fgets(line, LINE_MAX, puzzleFile) > 0) {
            char *c = line;
            while((*c == 'U') || (*c == 'D') || (*c == 'L') || (*c == 'R')) {
                switch(*c) {
                    case 'U':
                        if(keypad[part*49+(y-1)*7+x] != '#') y--;
                        break;
                    case 'D':
                        if(keypad[part*49+(y+1)*7+x] != '#') y++;
                        break;
                    case 'L':
                        if(keypad[part*49+y*7+x-1] != '#') x--;
                        break;
                    case 'R':
                        if(keypad[part*49+y*7+x+1] != '#') x++;
                        break;
                }
                c++;
            }
            char key = keypad[part*49+y*7+x];
            printf("%c", key);
        } 
        printf("\n");
        fclose(puzzleFile);
    }
    return 0;
}
