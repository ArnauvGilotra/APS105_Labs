#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "reversi.h"
/*
Author: Arnauv Gilotra
This code basically sets up the Reversi or othelo game within C. It creates a 2D board
for upto 26 rows and cols. It also recevives the board config as input then it calculates
availible moves for both the player. It can also receive the player input and check for it's
legality and if legal flip the tiles correctly. 
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
void movesAvailible(char board[][26], int n, char colour)
{
    bool alreadyFoundMove = false;//bool ensures we don't keep looping in different directions when we have realised the current iterating r,c is a possible moves
    printf("Available moves for %c:\n", colour);
    //check every location row by row
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 'U')//if the current iterating location is empty
            {
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++)//iterate for all 8 directions 
                {
                    printf("***");
                    
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
                    {
                        //Helps exit the loop
                        if (alreadyFoundMove == true ) { //already found a move
                            alreadyFoundMove = false; //set it to false 
                            break; //exit loop so that we can move on to another r,c location on the board and search for another possible move
                        }
                        if (deltaRow == 0 && deltaCol == 0){}//Do nothing since delta vector is a zero vector
                        else {
                            if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) && alreadyFoundMove == false)
                            {
                                //if the current direction is legal then thats a availible move; hence print the row & col
                                alreadyFoundMove = true;
                                printf("%c%c\n", row + 'a', col + 'a');
                            }
                        }  
                    }
                }
            }
        }
    }
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
void InputChecker(char board[][26], int n, char colour, int row, int col)
{
    if ((positionInBounds(n, row, col)) && (board[row][col] == 'U'))
    {
        //For each diagonal delta vector
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
        {
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
            {
                if((deltaRow != 0 || deltaCol != 0) && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
                {
                    //move legal if the direction is diagonal and the checkLegalInDirection return true
                    //update the colour
                    board[row][col] = colour;
                    //flip the tiles as it is a legal move in the direction of the delta vector
                    tileFlipper(board, n, row, col, colour);
                    //print valid move as required by handout
                    printf("Valid move.\n");
                    //print board as required by handout
                    printBoard(board, n);
                    return;
                }                 
            }
        }
        //when not legal
        //printing the requirement of handout
        printf("Invalid move.\n");
        printBoard(board, n);
        return;
    }
    //when not in bounds or not an empty spot    
    else{
        //printing the requirement of handout
        printf("Invalid move.\n");
        printBoard(board, n);
        return;
    }
}
// Driver code
int main(void)
{
    int n; //n is board dimension
    char board[26][26]; //initialise board
    char colour, row, col; //colour of the tile, its location vector.
    //take the dimension
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    setUpBoard(board, n);
    //print the board
    printBoard(board, n);
    printf("Enter board configuration:\n");
    //keep taking the current setup of the board one location at a time until the input for all three variables is "!"
    while (colour != '!' || row != '!' || col != '!')
    {
        scanf(" %c%c%c", &colour, &row, &col);
        //update
        board[row - 'a'][col - 'a'] = colour;
    }
    //print as the state of the board now
    printBoard(board, n);
    //Note: white then black for findng and printing the availible moves
    //find and print the availible moves for white 
    movesAvailible(board, n, 'W');
    //find and print the availible moves for black
    movesAvailible(board, n, 'B');
    //ask for the new move input from user
    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &row, &col);
    //check whether the move is legal
    InputChecker(board, n, colour, row - 'a', col - 'a');
    //done done done
    return 0;
}