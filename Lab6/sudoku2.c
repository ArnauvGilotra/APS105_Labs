#include <stdio.h>
void solveSudoko(const int Size, int sudoko[Size][Size]);
void rowReader(const int Size, int row[Size], int replacer[Size]);
void colReader(const int Size, int col[Size], int replacer[Size]);
int main(void)
{
    int board[4][4] = {
        {0, 1, 3, 2},
        {2, 0, 1, 0},
        {1, 0, 0, 3},
        {3, 4, 2, 1}};

    const int Size = 4;
    solveSudoko(Size, board);

    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/*
    Our expample: 
        {0, 1, 3, 2},
        {2, 0, 1, 0},
        {1, 0, 0, 3},
        {3, 4, 2, 1}}

Let us consider row = 0,1,3,2 and col 0,2,1,3. We can clearly see that this 0 intersection
has to replaced with 4. 

The way row reader works is that if 1,2,3 or 4 exist in the row then in the replacer[] array
which is 4 ints long will be updated with 1 in the index of position 1,2,3,4. 
For example here 0,1,3,2 . we can see that 1,2,3 exits therefore replacer[4] = {1,1,1,0} 
It has 1 at index 0,1,2 which represent 1,2,3 respectively. 

Col checkers works i the same way and it cross-checks which number we can place in the sudoku. 

Then we place the index of the zero int location plus one in the sudoku location where there exists a zero. 
*/
void rowReader(const int Size, int row[Size], int replacer[Size])
{
    for (int i = 0; i < Size; i++)
    {
        if (row[i] != 0) // 0,1,3,2
            replacer[row[i] - 1] = 1; // r[1-1] r[0] = 1 // r[2] = 1 // r[1] = 1 {1,1,1,0}
    }
}
void colReader(const int Size, int col[Size], int replacer[Size])
{
    for (int i = 0; i < Size; i++) //0,2,1,3
    {
        if (col[i] != 0)
            replacer[col[i] - 1] = 1; //{1,1,1,0} 
    }
}

void solveSudoko(const int Size, int sudoko[Size][Size])
{
    int row[4];
    int col[4];

    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (sudoko[i][j] == 0)
            {
                for (int m = 0; m < Size; m++)
                {
                    row[m] = sudoko[m][j];
                }
                for (int n = 0; n < Size; n++)
                {
                    col[n] = sudoko[i][n];
                }
                int replacer[4] = {0};
                rowReader(Size, row, replacer);
                colReader(Size, col, replacer);
                //replacer becomes {1,1,1,0} for our first zero in the test sudoku
                for (int k = 0; k < Size; k++)
                {
                    if (replacer[k] == 0) //{1,1,1,0}
                    {
                        sudoko[i][j] = k + 1; // at k = 3 replacer[3] = 0. so the sudoko[i][j] = 3+1 or 4. Which is correct ans
                        break;
                    }
                }
            }
        }
    }
}
