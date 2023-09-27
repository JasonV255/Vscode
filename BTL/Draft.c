#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char* invalidInput = "Illegal input, please try again: ";
int main()
{
    system("cls");
    printf("%s",invalidInput);
    return 0;
}
 bool player1Turn = false;
    int index[100];
    index[0]=-1;
    int k=1;
    for (int i=0;i<strlen(history);i++) {
       if(history[i]>=97 && history[i] <=111) {
        index[k] = i;
         k++;
       }
    }
     enum Stone game[15][15];
     for (int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
      displayBoard(game, MAX_SIZE);
            printf("%s",inputCommand);
             char kq[10];
    int i=0;
    while (true) {
        char h;

        scanf("%c",&h);
        scanf("%c",&h);
        switch (h) {
        case's': return;
        case 'n': {
            i++;
           if(i<=numOfMoves) {
            player1Turn = !player1Turn;
            for (int j=0;j<index[i]-index[i-1];j++) {
                kq[j]=history[index[i-1]+j+1];
            }
            int length = strlen(kq);
        int r = atoi(kq);
        int c;
        if(length==2) {
            c = (kq[1])-97;
        } 
        else {
            c = (kq[2])-97;
        }
        if(player1Turn){ // 1a
            game[15-r][c] = X;
        }
        else if(!player1Turn) { // 15a
            game[15-r][c] = O;
        }
            displayBoard(game, MAX_SIZE);
             for (int j=0;j<index[i]-index[i-1];j++) {
                kq[j]='\0';
            }
            printf("%s", inputCommand);
           } else {printf("This is the end of the match.\n");i=numOfMoves;
            printf("%s", inputCommand);
             }break;
        } 
        case 'p': {
            if (i>0) {
            player1Turn = !player1Turn;
            for (int j=0;j<index[i]-index[i-1];j++) {
                kq[j]=history[index[i-1]+j+1];
            }
             int length = strlen(kq);
        int r = atoi(kq);
        int c;
        if(length==2) c = (kq[1])-97;
        else c = (kq[2])-97;
            game[15-r][c] = NA;
            
             displayBoard(game, MAX_SIZE);
              for (int j=0;j<index[i]-index[i-1];j++) {
                kq[j]='\0';
            }
            i--;
            printf("%s", inputCommand);
            } else {printf("This is the start of the match.\n");i=0;
            printf("%s", inputCommand);
            }break;
    }
    
     default: {printf("%s", invalidInput); break;}
        }
    }