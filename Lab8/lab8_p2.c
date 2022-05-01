#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "reversi.h"
/*
Author: Arnauv Gilotra
This code basically sets up the Reversi or othelo game within C. It creates a 2D board
for upto 26 rows and cols. It also recevives the board config as input then it calculates
if there are moves availible for a player. It can also receive the player input and check for it's
legality and if legal flip the tiles correctly. 
In addition this code now also runs with the prescribed alogrithm to play against a computer or someone else. 
Functions from Lab7 remain unchanged expect a few modifcation to fit the requirement in the lab module
*/
//Functions in the order of calling or just before the fucntion they are called in 
// Helper Function: Set up the board according to the input of the dimensionn of the board by the user. 
void setUpBoard(char board[][26], int n)
{    
    //filling in the 2D char array row by row
    for (int i = 0; i <= n-1; i++)
    {
        for (int j = 0; j <= n-1; j++)
        {
            //white tile is "W" and Black tile is "B" as per the handout
            //Empty spot denoted by "U"
            board[i][j] = 'U';
            //the basic starting setup of the game 2 whites and blacks in the middle
            /*
            W B
            B W
            */
            //2 whites diagonally 1,4
            board[n/2][n/2] = 'W';
            board[n/2 - 1][n/2 - 1] = 'W';
            //2 blacks diagonally 2,3
            board[n/2 - 1][n/2] = 'B';
            board[n/2][n/2 - 1] = 'B';   
        }
    }
}
// Required Function: It will print the board whenever required during the game with the labelling of the rows and cols
void printBoard(char board[][26], int n)
{   
    //print the required spacing
    printf("  ");
    //prints the labels for the cols
    for (int k = 0; k <= n-1; k++)
    {
        printf("%c", 'a' + k);
    }
    printf("\n");
    //print the row and the individual board locations
    for (int i = 0; i <= n-1; i++)
    {
        //prints the row label
        printf("%c ", 'a' + i);
        //prints the individual board pieces row by row
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }        
}
// Helper Funtion: checks for any empty locations on the board. If true that means the game is over. 
bool gameOver(char board[][26], int n, bool *humanPlayedInvalid)
{
    if (*humanPlayedInvalid == true) return true;
    //go through and check each location
    for (int row = 0; row <= n-1; row++)
    {
        for (int col = 0; col <= n-1; col++)
        {
            //if any locaion is 'U': game can continue
            if (board[row][col] == 'U') return false;
        }
    }
    //game is over
    return true;
}
// Required Function: Returns true if the position we want to check for is within bounds of the board
bool positionInBounds(int n, int row, int col)
{
    return (row >= 0 && row <= n-1 && col >= 0 && col <= n-1);
}
/* 
Required function: checks whether the row and col are in a legal position of a given colour by traversing the
board using the vector creating by deltaRow & deltaCol. 

We use the positionInBounds to check whether the current iterating row & col are actually within
the bounds of the board 
*/
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    char colourOfEnemyPlayer;
    //set the enemy colour
    if(colour == 'W') colourOfEnemyPlayer = 'B';
    else colourOfEnemyPlayer = 'W';
    //iterating variable
    int i = 1;   
    /* 
      Checking in the direction of the delta Vector of the passed row & col
      Loop will run until we are within the bounds and the tiles in the direction of the delta vector
      are only of the enemy player.
    */
    while ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) && ((board[row + (deltaRow * i)][col + (deltaCol * i)]) != (colour)) && ((board[row + (deltaRow * i)][col + (deltaCol * i)]) != ('U'))) {
        i++; //increment the iterating variable
        //if the current iterating locaion in the delta vector direction is in bounds and has the tile of the colour in play
        if ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) && (board[row + (deltaRow * i)][col + (deltaCol * i)] == colour)) {
            return true;
        } else {
            //in bound & enemy colour
            if ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) && (board[row + (deltaRow * i)][col + (deltaCol * i)] == colourOfEnemyPlayer)) {
                //Next iteration all legal so far. 
                continue;
            } else {
                //not in bounds
                if((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i)) == false)) return false;
                else {
                    //in bounds & colour of play
                    if(board[row + (deltaRow * i)][col + (deltaCol * i)] == colour) return true;
                    else return false; 
                }
            }
        } 
    }
    //not in bound or not empty
    return false;
}
// Helper function: Figures out the availible moves for given colour according to th rules of the game and the given state of the board
bool movesAvailible(char board[][26], int n, char colour)
{
    //check every location row by row
    for (int row = 0; row <= n-1; row++)
    {
        for (int col = 0; col <= n-1; col++)
        {
            if (board[row][col] == 'U')//if the current iterating location is empty
            {
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++)//iterate for all 8 directions 
                {
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
                    {
                        if (deltaRow == 0 && deltaCol == 0){}//Do nothing since delta vector is a zero vector  
                        else
                        {
                            //if the current direction is legal then thats a availible move hence true
                            if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) return true;
                        }  
                    }
                }
            }
        }
    }
    return false;//no moves availible
}
// Helper Function: Flips the tiles
void tileFlipper(char board[][26], int n, int row, int col, char colour)
{
    board[row][col] = colour;
    int deltaVector[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    //Check for flip in each 8 directions
    for (int h = 0; h < 8; h++) {
        //check if it is legal to flip in this direction
        if (checkLegalInDirection(board, n, row, col, colour, deltaVector[h][0], deltaVector[h][1])) {
            //change every piece to colour until the same colour piece
            for(int i = row + deltaVector[h][0], j = col + deltaVector[h][1]; board[i][j] != colour; i += deltaVector[h][0], j += deltaVector[h][1]) {
                board[i][j] = colour;
            }
        }
    } 
    
}
// Helper Function: Facilitates the checking of the new move inputted by the user
void inputChecker(char board[][26], int n, char colour, char computerColour, int row, int col, bool *humanPlayedInvalid)
{
    if ((positionInBounds(n, row, col)) && (board[row][col] == 'U'))
    {   //for all 8 directions
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
        {
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
            {
                if((deltaRow != 0 || deltaCol != 0) && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
                {
                    //move legal if the direction is diagonal and the checkLegalInDirection return true
                    //flip the tiles as it is a legal move in the direction of the delta vector
                    tileFlipper(board, n, row, col, colour);
                    //print board as required by handout
                    printBoard(board, n);
                    return;
                }                 
            }
        }
    }
    //else print move is invalid
    printf("Invalid move.\n");
    printf("%c player wins.", computerColour);//comp wins
    *humanPlayedInvalid = true;//make true
    gameOver(board, n, humanPlayedInvalid);//gameover
    return;
}
// Helper Function: counts the number of flippped tiles in the given direction
int flippedTilesCounter(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int i = 1;//iterating variable
    int counter = 0;
    //in bounds and tiles are not the passed colour keep counting in delta direction. 
    while ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) && board[row + (deltaRow * i)][col + (deltaCol * i)] != colour)
    {
        i++; 
        counter++;//tiles flipped in one direction       
    }
    return counter;
}
/*
Required Function: Uses dynamic programming to calculate the possible score of each possible move and store it at the
location of the possible move in a dummy 2D array. 
Then we throught he 2d array to find the highest score location which becomes the move of the computer. 
*/
void makeMove(char board[][26], int n, char computerColour)
{
    int count = 0, maxRow = 0, maxCol = 0, maxScore = 0;
    int dummyCounterBoard[26][26] = {0};
    //loop through all locations
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if ((positionInBounds(n, row, col)) && (board[row][col] == 'U'))
            {
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
                {
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
                    {
                        if((deltaRow != 0 || deltaCol != 0) && checkLegalInDirection(board, n, row, col, computerColour, deltaRow, deltaCol))
                        {//calculates the count for each possible mov
                            count += flippedTilesCounter(board, n, row, col, computerColour, deltaRow, deltaCol);
                        }
                    }
                }
            }
            dummyCounterBoard[row][col] = count;//stores count at that moves r,c location
            count = 0;//set it back to zero. 
        }
    }
    //set the move
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {// goes through the dummy board and finds the location with the highest score which is a set as comp's move. 
            if (dummyCounterBoard[row][col] > maxScore)
            {
                maxScore = dummyCounterBoard[row][col];
                maxRow=row;
                maxCol=col;
            }
        }
    }
    //flip the tiles in all possible directions according to the set move. 
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
        { 
            if (checkLegalInDirection(board, n, maxRow, maxCol, computerColour, deltaRow, deltaCol))
            {
                tileFlipper(board, n, maxRow, maxCol, computerColour);
            }
        }
    }
    //print the move
    printf("Computer places %c at %c%c.\n", computerColour, maxRow + 97, maxCol + 97);
    printBoard(board, n);//print the board
    
}  
//Helper Function: Plays for the human.
void humanPlay(char board[][26], int n, char currentPlayer, char computerColour, char humanColour, bool *humanPlayedInvalid)
{
    char row, col;//if the player has moves availible
    if (movesAvailible(board, n, humanColour)) {
        printf("Enter move for colour %c (RowCol): ", humanColour);
        scanf(" %c%c", &row, &col);//check it's legality
        inputChecker(board, n, currentPlayer, computerColour, row - 'a', col - 'a', humanPlayedInvalid);
        return;
    } else{
        printf("%c player has no valid move.\n", humanColour);
        return;
    }
}
//Helper Function: Calls the makeMove fucntion for the computer if it has moves availible
void compPlay(char board[][26], int n, char currentPlayer, char computerColour, char humanColour)
{        
    if (movesAvailible(board, n, computerColour)) makeMove(board, n, computerColour);
    else printf("%c player has no valid move.\n", computerColour); 
}

//Helper Function: figures out whoes turn it is in the game and call's their respective function while returning the currentPlayer: 
char whichColourTurn(char board[][26], int n, char currentPlayer, char computerColour, char humanColour, bool *humanPlayedInvalid)
{
    if (currentPlayer == humanColour) {
        humanPlay(board, n, currentPlayer, computerColour, humanColour, humanPlayedInvalid);
        currentPlayer = computerColour;     
    }
    else if (currentPlayer == computerColour){
        compPlay(board, n, currentPlayer, computerColour, humanColour);
        currentPlayer = humanColour;
    }
    return currentPlayer;
}
//Driver code
int main(void)
{
    int n; //boardSize
    char board[26][26], currentPlayer = 'B', computerColour, humanColour;
    bool humanPlayedInvalid = false;
    //get board dimensions
    printf("Enter the board dimension: ");
    scanf(" %d", &n);
    //pick computer's colour
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    //set up the board and print it
    setUpBoard(board, n);
    printBoard(board, n);
    //set human's colour
    if (computerColour == 'W') humanColour = 'B';
    else humanColour = 'W';
    //run the game in the loop until it's game over
    while (gameOver(board, n, &humanPlayedInvalid) == false)
    {
        currentPlayer = whichColourTurn(board, n, currentPlayer, computerColour, humanColour, &humanPlayedInvalid);
    }
    //when all the moves by human were legal
    if (humanPlayedInvalid == false)
    {
        int compCount = 0, humanCount = 0;
        //check all the locations and take count of both the tiles
        for (int row = 0; row <= n-1; row++)
        {
            for (int col = 0; col <= n-1; col++)
            {
                if (board[row][col] == computerColour) compCount++;
                else if(board[row][col] == humanColour) humanCount++; 
            }
        }
        //comp winner
        if (compCount>humanCount) {
            printf("%c player wins.", computerColour);
            return 0;
        } else if (humanCount>compCount) { //human winner
            printf("%c player wins.", humanColour);
            return 0;
        } else { //draw
            printf("Draw!");
            return 0;
        }
    }
    //done done done
    return 0;
}