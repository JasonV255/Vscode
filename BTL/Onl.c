#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;             // Width for writing out an integer
const int charW = 1;             // Width for writing out a character
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone {NA, X, O};

struct Move {
    int row;
    int col;
    enum Stone stone;
};

static char* lineString( char left, char mid, char right, char horz, int wcell, int ncell ) {
    static char result[100];
    strcpy(result, "");
    char cell[10];
    for(int i = 0; i < wcell; i++){
        cell[i] = horz;
    }
    cell[wcell] = '\0';
    strncat(result,&left,1);
    char cellMid[20];
    strcpy(cellMid, cell);
    strncat(cellMid, &mid,1);
    for ( int i = 0; i < ncell - 1; i++ )
        strcat(result, cellMid);
    char cellRight[20];
    strcpy(cellRight, cell);
    strncat(cellRight, &right,1);
    strcat(result, cellRight);
    return result;
}

void displayBoardSimple(enum Stone arr[][15], int size) {
    //UPPERLINE
    printf("   ");
    for(int i = 0; i < size; i++) {
        printf("  %c ", (char)(i + 'a'));
    }
    printf("\n");
    printf("   %s\n", lineString( TL, TM, TR, HORZ, 3, numPerLine ));

    //MIDDLE
    for(int i = 0; i < size; i++) {
        printf("%2d %c", size - i, VERT);
        for(int j = 0; j < size; j++) {
            if(arr[i][j] == NA) printf("   %c", VERT);
            if(arr[i][j] == X) printf(" X %c", VERT);
            if(arr[i][j] == O) printf(" O %c", VERT);
        }
        printf("\n");
        if(i != size - 1) printf("   %s\n", lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ));
    }

    //UNDERLINE
    printf("   %s\n", lineString( BL, BM, BR, HORZ, 3, numPerLine ));
}

void displayBoard(enum Stone arr[][15], int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            printf("%d", arr[i][j]);
        }
    }
    printf("\n");
}

bool makeMove(enum Stone board[][15], int size, char* playerMove, bool isFirstPlayerTurn){
    //BEGIN TODO
    int length = strlen(playerMove);
    int MoveX, MoveY;
    bool legal = false;
    if (length == 2 && playerMove[1] >= 'a' && playerMove[1] <= 'o' && playerMove[0] >= '1' 
    && playerMove[0] <= '9')
    {
        //translate
        MoveX = abs(playerMove[0] - '1' - 14);
        MoveY = playerMove[1] - 'a'; 
        if (board[MoveX][MoveY] == NA)
            legal = true;
        else legal = false;       
    } else if (length == 3 && playerMove[2] >= 'a' && playerMove[2] <= 'o' 
    && playerMove[0] >= '0' && playerMove[0] <= '1' && playerMove[1] >= '0' && playerMove[1] <= '5')
    {
        //translate
        MoveY = playerMove[2] - 'a';
        MoveX = abs((playerMove[0] - '0')* 10 + playerMove[1] - '0' - 1 - 14);
        if (board[MoveX][MoveY] == NA) legal = true;
        else legal = false;
    } else legal = false;
    if (legal)
    {
        if (isFirstPlayerTurn)  board[MoveX][MoveY] = X;
        else  board[MoveX][MoveY] = O;
        return true;
    }
    else return false;
    //END TODO
}

bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
    
    bool check5Col = true;
    bool check5row = true;
    bool check5diag1 = true;
    bool check5diag2 = true;
    bool check2ene = false;
    bool checkMore5 = false;
    bool check5Move = false;
    enum Stone playing, enemy;
    if (isFirstPlayerTurn)
    {
        playing = X;
        enemy = O;
    } 
    else{
        playing = O;
        enemy = X;
    }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                check5Col = true;
                check5row = true;
                check5diag1 = true;
                check5diag2 = true;
                for (int k = 0; k < 5; k++)
                {
                    if ((i <= 10 && board[i + k][j] != playing) || i > 10)
                        check5Col = false;
                    if ((j <= 10 && board[i][j + k] != playing) || j > 10)
                        check5row = false;
                    if ((j <= 10 && i <= 10 & board[i + k][j + k] != playing) || j > 10 || i > 10)
                        check5diag1 = false;
                    if ((j >= 4 && i <= 10 && board[i + k][j - k] != playing) || i > 10 || j < 4)
                        check5diag2 = false;
                }
                if (check5Col || check5row || check5diag1 || check5diag2)
                    check5Move = true;
                if (check5Move)
                {
                    if (check5diag1)
                    {
                        if (((i == 0 && j != 10)|| (j == 0 && i != 10)) && board[i + 5][j + 5] == playing)
                            checkMore5 = true;
                        else if (((i == 10 && j != 0)|| (j == 10 && i != 0)) && board[i - 1][j - 1] == playing)
                            checkMore5 = true;
                        else if ((board[i - 1][j - 1] == playing || board[i + 5][j + 5] == playing))
                            checkMore5 = true; 
                        else 
                            checkMore5 = false;
                        if (i == 0 || i == 10)
                            check2ene = false;   
                        else
                            if ((board[i - 1][j - 1] == enemy && board[i + 5][j + 5] == enemy))
                                check2ene = true;
                        if (!check2ene && !checkMore5)
                            return true;                 
                    } 
                    if (check5diag2)
                    {
                        if (((i == 0 && j != 4) || (j == 14 && i != 10)) && board[i + 5][j - 5] == playing)
                            checkMore5 = true;
                        else if (((j == 4 && i != 0)|| (i == 10 && j != 14)) && board[i - 1][j + 1] == playing)
                            checkMore5 = true;
                        else if((board[i - 1][j + 1] == playing || board[i + 5][j - 5] == X))
                            checkMore5 = true;
                        else
                            checkMore5 = false;
                        if (j == 0 || j == 10 || j == 14)
                            check2ene = false;
                        else 
                            if((board[i - 1][j + 1] == enemy) && (board[i + 5][j - 5] == enemy))
                                check2ene = true;
                        if (!check2ene && !checkMore5)
                            return true; 
                    }
                    check2ene = false;
                    checkMore5 = false;
                    check5Move = false;
                    if (check5Col)
                    {
                        if (i == 0 && board[5][j] == playing)
                            checkMore5 = true;
                        else if (i == 10 && board[9][j] == playing)
                            checkMore5 = true;
                        else if ((board[i - 1][j] == X || board[i + 5][j] == playing))
                            checkMore5 = true;
                        else
                            checkMore5 = false;
                        if (i == 0 || i == 10)
                            check2ene = false; 
                        else if (j == 0 || j == 10)
                            check2ene = false;
                        else
                            if ((board[i - 1][j] == enemy) && (board[i + 5][j] == enemy))
                                check2ene = true;
                        if (!check2ene && !checkMore5)
                            return true; 
                    } 
                    check2ene = false;
                    checkMore5 = false;
                    check5Move = false;
                    if (check5row)
                    {
                        if (j == 0 && board[i][5] == playing)
                            checkMore5 = true;
                        else if (j == 10 && board[i][9] == playing)
                            checkMore5 = true;
                        else if ((board[i][j - 1] == X || board[i][j + 5] == playing))
                            checkMore5 = true;
                        else
                            checkMore5 = false;
                        if (i == 0 || i == 10)
                            check2ene = false; 
                        else if (j == 0 || j == 10)
                            check2ene = false;
                        else
                            if ((board[i][j - 1] == enemy) && (board[i][j + 5] == enemy))
                                check2ene = true;
                        if (!check2ene && !checkMore5)
                            return true; 
                    }
                    check2ene = false;
                    checkMore5 = false;
                    check5Move = false;
                }
            }
        }
    return false;
}
struct coordinate
{
    int xMove;
    int yMove;
};

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
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
     enum Stone Game[15][15];
     for (int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            Game[i][j] = NA;
        }
    }
      displayBoard(Game, MAX_SIZE);
            printf("%s", inputCommand);
             char result[10];
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
                result[j]=history[index[i-1]+j+1];
            }
            int length = strlen(result);
        int r = atoi(result);
        int c;
        if(length==2) {
            c = (result[1])-97;
        } 
        else {
            c = (result[2])-97;
        }
        if(player1Turn){
            Game[15-r][c] = X;
        }
        else if(!player1Turn) {
            Game[15-r][c] = O;
        }
            displayBoard(Game, MAX_SIZE);
             for (int j=0;j<index[i]-index[i-1];j++) {
                result[j]='\0';
            }
            printf("%s", inputCommand);
           } else {i=numOfMoves;
            printf("%s", endOfHistory);
             }break;
        } 
        case 'p': {
            if (i>0) {
            player1Turn = !player1Turn;
            for (int j=0;j<index[i]-index[i-1];j++) {
                result[j]=history[index[i-1]+j+1];
            }
             int length = strlen(result);
        int r = atoi(result);
        int c;
        if(length==2) c = (result[1])-97;
        else c = (result[2])-97;
            Game[15-r][c] = NA;
            
             displayBoard(Game, MAX_SIZE);
              for (int j=0;j<index[i]-index[i-1];j++) {
                result[j]='\0';
            }
            i--;
            printf("%s", inputCommand);
            } else {i=0;printf("%s",startOfGame);
            }break;
    }
    
     default: {printf("%s", invalidInput); break;}
    //END TODO
}
    }
}

void startGame() {
    enum Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    char playerMove[50];
    bool player1Turn = true;
    printf("Player 1 turn: ");
    while(true) {
        scanf("%s", playerMove);
        if(strcmp(playerMove,"ff") == 0) {
            printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
            break;
        }
        else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)){
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
                return;
            }
            player1Turn = !player1Turn;
            displayBoard(game, MAX_SIZE);
            printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
        } else {
            printf("Illegal move, please try again: ");
        }
    }
}

int main()
{
    printf("Welcome to Gomoku!\n");
    printf("1. Play game\n");
    printf("2. History\n");
    printf("3. Exit\n");
    printf("Please select mode [1/2/3]: ");
    int mode;
    while(true){
        scanf("%d", &mode);
        if(mode == 1) {
            startGame();
            return 0;
        } else if (mode == 2) {
            int numOfMoves;
            printf("Please enter number of moves: ");
            scanf("%d", &numOfMoves);
            char history[700];
            printf("Please enter history: ");
            scanf("%s", history);
            displayHistory(history, numOfMoves);
            return 0;
        } else if (mode == 3) {
            return 0;
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid mode, please try again: ");
        }
    }

    return 0;
}