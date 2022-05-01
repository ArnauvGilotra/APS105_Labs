#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Considering S & E to be positive and N & W to be negative
S = [1,0]
SW = [1,-1]
W = [0,-1]
NW = [-1,1]
N = [-1,0]
NE = [-1,1]
E = [0,1]
SE = [1,1]
*/
// directional array for x and y axis creating the direction vectors taken in a clockwise order starting from south.
int x[] = {1, 1, 0, -1, -1, -1, 0, 1};
int y[] = {0, -1, -1, -1, 0, 1, 1, 1};
void search2D(char word[], int wordSize, const int Size, char grid[Size][Size]);
bool search1D(char word[], int wordSize, const int Size, char grid[Size][Size], int row, int col);
void printFoundLocation(int rowDir, int colDir, int R, int C);
int rowDir = -2;
int colDir = -2;


void search2D(char word[], int wordSize, const int Size, char grid[Size][Size])
{
    bool isFound = false;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (word[0] == grid[i][j])
            {
                isFound = search1D(word, wordSize, Size, grid, i, j);
                if (isFound == true)
                {
                    printFoundLocation(rowDir, colDir, i, j);
                    i = Size;
                    break;
                }
            }
        }
    }
    if (isFound == false)
        printf("word not found");
}

bool search1D(char word[], int wordSize, const int Size, char grid[Size][Size], int row, int col)
{

    for (int dir = 0; dir < 8; dir++)
    {
        int k, rd = row + x[dir], cd = col + y[dir];

        for (k = 1; k < wordSize; k++)
        {
            // if out of bounds, break.
            if (rd >= Size || rd < 0 || cd >= Size || cd < 0)
                break;
            // if not matched, break.
            if (grid[rd][cd] != word[k])
                break;
            // incremeant the x,y coordintes according to the direction vector.
            rd += x[dir], cd += y[dir];
        }
        if (k == wordSize)
        {
            rowDir = x[dir];
            colDir = y[dir];
            return true;
        }
    }
    return false;
}

int main(void)
{
    char grid[5][5] = {
        {'N', 'O', 'N', 'X', 'N'},
        {'O', 'O', 'O', 'O', 'H'},
        {'N', 'E', 'B', 'O', 'N'},
        {'B', 'E', 'E', 'O', 'H'},
        {'N', 'N', 'N', 'N', 'N'}};

    char word[] = {'B', 'O', 'N'};
    int wordSize = 3;
    int gridSize = 5;

    search2D(word, wordSize, gridSize, grid);

    return 0;
}

void printFoundLocation(int rowDir, int colDir, int R, int C)
{
    if (rowDir == 1 && colDir == 0)
        printf("Word found at row %d and column %d in the south direction.", R, C);
    if (rowDir == 1 && colDir == -1)
        printf("Word found at row %d and column %d in the south-west direction.", R, C);
    if (rowDir == 0 && colDir == -1)
        printf("Word found at row %d and column %d in the west direction.", R, C);
    if (rowDir == -1 && colDir == -1)
        printf("Word found at row %d and column %d in the north-west direction.", R, C);
    if (rowDir == -1 && colDir == 0)
        printf("Word found at row %d and column %d in the north direction.", R, C);
    if (rowDir == -1 && colDir == 1)
        printf("Word found at row %d and column %d in the north-east direction.", R, C);
    if (rowDir == 0 && colDir == 1)
        printf("Word found at row %d and column %d in the east direction.", R, C);
    if (rowDir == 1 && colDir == 1)
        printf("Word found at row %d and column %d in the south-east direction.", R, C);
}