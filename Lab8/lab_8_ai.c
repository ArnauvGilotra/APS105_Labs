#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Author: Arnauv Gilotra

This code builds on the Part 1 to make an AI that beats the University AI in Reversi. 
It is a a little incorrect to call it an AI, it is more of rule engine atleast how I built it. 
The idealogy is very simple: Calculate the tile count for the rule engine and for the opponent then
their diference would guide how much to update the score with and choose the next move. While doing so
we try to get the coners too. 

Functions have been picked directly from Lab7 or Lab8 part and modified slightly. 
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
        //For each delta vector expect 0,0
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
                    return;
                }                 
            }
        }
    }
}
//gets the tile count for a certain player
int getCount(char boardCopy[][26],int n, char colour, int tRow, int tCol){
    int deltaVector[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int countTemp = 0;
    int tempRow = tRow, tempCol = tCol;
    for (int k = 0; k < 8; k++) {
        if (checkLegalInDirection(boardCopy, n, tempRow, tempCol, colour, deltaVector[k][0], deltaVector[k][1])) {
            //Current iterating location checked
            tempRow += deltaVector[k][0], tempCol += deltaVector[k][1];//increament to next location
            //In case next position is opponent's tile
            if (boardCopy[tempRow][tempCol] != 'U' && boardCopy[tempRow][tempCol] != colour) {
                countTemp++;
                do { //Keeping counting untill in bounds and tile is not my rule engine's tile
                    tempRow += deltaVector[k][0], tempCol += deltaVector[k][1];
                        if (boardCopy[tempRow][tempCol] == colour && positionInBounds(n, tempRow, tempCol)) {
                            break;//exit loop when we hit rule engine's tile
                        }
                        countTemp++;
                } while (positionInBounds(n, tempRow, tempCol));//run when in bounds
            }
        }
    }
    return countTemp;
}
//The rule engine: Calculates the tile count for itself and the opponent in each round of play to decide it's move.
int makeMove(const char board[26][26], int n, char turn, int* row, int* col) {
    char opponent = turn == 'B' ? 'W' : 'B';
    int countTotal = 0, countTemp = 0, score = 0, totalscore = 0, difOptimal = 0, dif = 0;
    char boardCopy[26][26]; //initialise variable for a copy of the board
    //chose to use the direction vector 2d array to eliminate nested loop complexity for the aide or readability
    //Loop through the whole board and checking in each of the 8 direction     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int e = 0; e < n; e++) {
                for (int f = 0; f < n; f++) {
                    boardCopy[e][f] = board[e][f]; //Make a copy of the board. 
                }
            }
            //if current iterating location is empty
            if (boardCopy[i][j] == 'U') {
                countTemp = getCount(boardCopy, n, turn, i, j);
                //When temporary count exceeds total count 
                if (countTemp > countTotal) {
                    countTotal = countTemp; //equate them
                    if (score <= 5) { //if score is less then 5 or 5
                        score = 5; //make score 5
                    }
                }
                //If score is already 5 or more from previous iteration/move 
                if (score >= 5) {
                    int countTotalOpp = 0, countTempOpp = 0;
                    //check the validity of the input and if legal, flip
                    InputChecker(boardCopy, n, turn, i, j);
                    // Repeat the scoring process for updated board for the opponent 
                    // Check each location in all 8 directions
                    for (int l = 0; l < n; l++) {
                        for (int m = 0; m < n; m++) {
                            //if location is empty
                            if (boardCopy[l][m] == 'U') {
                                countTempOpp = getCount(boardCopy, n, opponent, l, m);
                                //temp count exceed then this is the new total count for opponent
                                if (countTempOpp > countTotalOpp) countTotalOpp = countTempOpp;
                                //reset temp count for next iteration
                                countTempOpp = 0;
                            }
                        }
                    }
                    //calculate tile dif
                    dif = countTotal - countTotalOpp;
                    //start adding to the score for the next iteration and moves
                    //values used below are result of on trial and test to win against test cases
                    //value corner locations more
                    if (i == 0 && j == 0 || i == n -1 && j == n -1 || i == 0 && j == n -1 || i == n -1 && j == 0) score += 15;
                    //My rule engine is winning
                    if (dif > 0) score = 15;
                    //almost tie running close
                    else if (dif = 0) score = 10;
                    //My rule engine is losing
                    else if (dif < 0) score = 5;
                }
                //current iterationg score is more thn total score then the score is the new total score
                //current iterating position (i,j) is the move
                if (score > totalscore) {
                    totalscore = score;
                    *row = i, *col = j;
                }
                //current iterationg score is equal to total and the new diference is less than the difOptimal then the dif is the new Optimal diference
                //current iterating position (i,j) is the move
                else if (score == totalscore && dif > difOptimal) {
                    difOptimal = dif;
                    *row = i, *col = j;
                }
                //When final score is the same as total score and dif is same bestDif choose the move closer to more of the player's own tiles
                else if (score == totalscore && dif == difOptimal) {
                    if (!(*row < i && *col < j)) *row = i, *col = j;
                }
                //reset vals for next iteration
                dif = 0,countTemp = 0,score = 0, countTotal = 0;
            }
        }
    }
    return totalscore;
}
// no driver code required