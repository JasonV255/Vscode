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
//BEGIN TODO
    int i,j;
    bool won= false;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            if(board[i][j]!=NA)
            {
                char a=board[i][j];
                //check 5 and endings (more or different)
                if (board[i-1][j]!=a && board[i+1][j]==a && board[i+2][j]==a 
                && board[i+3][j]==a && board[i+4][j]==a && board[i+5][j]!=a)//Row
                {
                    if(board[i-1][j]!=NA && board[i+5][j]!=NA) won = false;
                    else won = true;
                }
                else if (board[i][j-1]!=a && board[i][j+1]==a  && board[i][j+2]==a 
                && board[i][j+3]==a && board[i][j+4]==a && board[i][j+5]!=a)//Collum
                {
                    if (board[i][j-1]!=NA && board[i][j+5]!=NA) won = false;
                    else won = true;
                }
                else if (board[i-1][j-1]!=a && board[i+1][j+1]==a && board[i+2][j+2]==a
                && board[i+3][j+3]==a && board[i+4][j+4]==a&&board[i+5][j+5]!=a)//DiagL
                {
                    if(board[i-1][j-1]!=NA&&board[i+5][j+5]!=NA) won = false;
                    else won = true;
                }
                else if(board[i-1][j+1]!=a && board[i+1][j-1]==a && board[i+2][j-2]==a
                && board[i+3][j-3]==a && board[i+4][j-4]==a && board[i+5][j-5]!=a) //DiagL
                {
                    if(board[i-1][j+1]!=NA && board[i+5][j-5]!=NA) won = false;
                    else won = true;
                }

            }
        }
    }
    if (won) return true; else return false;
    //END TODO
};

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
    bool FirstTurn=false;
    int locate[100];
    locate[0]=-1;
    int k=1;
    for (int i=1; i<strlen(history); i++)
    {
        if(history[1]>=97 && history[i]<=111)
        {
            locate[k]= 1; k++;
        }
    }
    enum Stone Game[15][15];
    for (int i=0; i< MAX_SIZE; i++)
    {
        for (int j=0; j<MAX_SIZE; j++)
        {
            Game[i][j]=NA;
        }
    }
    displayBoard(Game, MAX_SIZE);
    printf("%s", inputCommand);
    char result[10];
    int i=0;
    while (true)
    {
        char P;
        //fflush();
        scanf("%c", &P);
        scanf("%c", &P);
        switch(P)
        {
            case 's': return;
            case 'n':
            {
                i++;
                if(i<=numOfMoves)
                {
                    FirstTurn= !FirstTurn;
                    for (int j=0; j<locate[i]-locate[i-1]; i++)
                    {
                        result[j]=history[locate[i-1]+j+1]; 
                    }
                    int length = strlen(result);
                    int r= atoi(result);
                    int c;
                    if(length==2)c=result[1]-97;
                    else c=result[2]-97;
                    //translate
                    if(FirstTurn)Game[15-r][c]=X;
                    else if(!FirstTurn)Game[15-r][c]=O;
                    displayBoard(Game, MAX_SIZE);
                    for(int j=0; j<locate[i]-locate[i-1]; j++) result[j]='\0';
                    printf("%s", inputCommand);
                }
                else{ printf("%s",endOfHistory); i=numOfMoves;}
                break;

            }
            case 'p':
            {
             
                if(i>0)
                {
                    FirstTurn= !FirstTurn;
                    for(int j=0; j<locate[i]-locate[i-1]; j++)
                        result[j]=history[locate[i-1]+j+1];

                    int length= strlen(result);
                    int r = atoi(result);                        
                    int c;
                    if (length==2) c= result[1]-97;
                    else c= result[2]-97;
                    Game[15-r][c]=NA;
                    displayBoard(Game, MAX_SIZE);
                    for(int j=0; j<locate[i]-locate[i-1]; j++)result='\0';
                    i--;
                    printf("%s", inputCommand);
                }
                else {printf("%s",startOfGame); i=0}
                break;
            }
            default:
            {
                printf("%s", invalidInput); break;
            }
        }
    }
    //END TODO
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






