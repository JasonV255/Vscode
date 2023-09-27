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

void displayBoard(enum Stone arr[][15], int size) {
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

void displayBoardSimple(enum Stone arr[][15], int size) {
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
    int xMove, yMove;
    bool legalMove = false;
    if (length == 2 && playerMove[1] >= 'a' && playerMove[1] <= 'o' && playerMove[0] >= '1' && playerMove[0] <= '9')
    {
        //reverse
        xMove = abs(playerMove[0] - '0'-14);
        yMove = playerMove[1] - 'a'; 
        if (board[xMove][yMove] == NA)
            legalMove = true;
        else legalMove = false;       
    } else if (length == 3 && playerMove[2] >= 'a' && playerMove[2] <= 'o' && playerMove[0] >= '0' && playerMove[0] <= '1'
    && playerMove[1] >= '0' && playerMove[1] <= '5')
    {
        yMove = playerMove[2] - 'a';
        xMove = abs((playerMove[0] - '0')* 10 + playerMove[1] - '0'-1-14 );
        if (board[xMove][yMove] == NA)
            legalMove = true;
        else legalMove = false;
    } else 
        legalMove = false;
    if (legalMove)
    {
        if (isFirstPlayerTurn)
            board[xMove][yMove] = X;
        else
            board[xMove][yMove] = O;
        return true;
    }
    else
        return false;
}
    //END TODO


bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
    //BEGIN TODO
      int i,j;
    for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(board[i][j]!=NA)
			{
			    char a=board[i][j];
				if (board[i-1][j]!=a&&board[i+1][j]==a&&board[i+2][j]==a&&board[i+3][j]==a&&board[i+4][j]==a&&board[i+5][j]!=a)
				{
				    if(board[i-1][j]!=NA&&board[i+5][j]!=NA)return false;
					else return true;
				}
				else if(board[i][j-1]!=a&&board[i][j+1]==a&&board[i][j+2]==a&&board[i][j+3]==a&&board[i][j+4]==a&&board[i][j+5]!=a)
				{
					if(board[i][j-1]!=NA&&board[i][j+5]!=NA)return false;
					else return true;
				}
                else if(board[i-1][j-1]!=a&&board[i+1][j+1]==a&&board[i+2][j+2]==a&&board[i+3][j+3]==a&&board[i+4][j+4]==a&&board[i+5][j+5]!=a)
                {
					if(board[i-1][j-1]!=NA&&board[i+5][j+5]!=NA)return false;
					else return true;
				}
                else if(board[i-1][j+1]!=a&&board[i+1][j-1]==a&&board[i+2][j-2]==a&&board[i+3][j-3]==a&&board[i+4][j-4]==a&&board[i+5][j-5]!=a)
                {
					if(board[i-1][j+1]!=NA&&board[i+5][j-5]!=NA)return false;
					else return true;
				}
			}
		}
	}
	return false;
    //END TODO


void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
 enum Stone game[15][15];
    struct coordinate hisOfgame[numOfMoves];
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            game[i][j] = NA;
    }
    displayBoard(game, 15);
    //read history
    int countChar = -1;
    int countNum = 0;
    for (int i = 0; i < numOfMoves; i++)
    {
        if (history[countNum + 1] >= '0' && history[countNum + 1] <= '9')
        {
            hisOfgame[i].xMove = abs((history[countNum] - '0')* 10 + history[countNum + 1] - '0' - 1 - 14);
            countNum += 3;
            countChar += 3;
        } 
        else
        {
            hisOfgame[i].xMove = abs(history[countNum] - '1' - 14);
            countNum += 2;
            countChar += 2;
        }
        hisOfgame[i].yMove = history[countChar] - 'a';
    }

    char decOfViewer;
    int orderMoves = -1;
    printf(inputCommand);
    int d;
    while ((d = getchar()) != '\n' && d != EOF);
    while (true)
    {
        scanf("%c", &decOfViewer);
        if (decOfViewer == 'n')
        {
            orderMoves++;
            if (orderMoves == numOfMoves)
            {
                orderMoves--;
                printf(endOfHistory);
            } else
            {
                (orderMoves % 2 == 0) ? (game[hisOfgame[orderMoves].xMove][hisOfgame[orderMoves].yMove] = X) : 
                (game[hisOfgame[orderMoves].xMove][hisOfgame[orderMoves].yMove] = O);
                displayBoard(game, 15);
                printf(inputCommand);
            }
        } else if (decOfViewer == 'p')
        {           
            if (orderMoves == -1)
            {
                orderMoves++;
                printf(startOfGame);
            } else
            {
                (orderMoves % 2 == 0) ? (game[hisOfgame[orderMoves].xMove][hisOfgame[orderMoves].yMove] = NA) : 
                (game[hisOfgame[orderMoves].xMove][hisOfgame[orderMoves].yMove] = NA);
                displayBoard(game, 15);
                printf(inputCommand);
            }
            orderMoves--;
        } else if (decOfViewer == 's')
            break;
        else 
            printf(invalidInput);
        while ((d = getchar()) != ' ' && d != EOF);
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