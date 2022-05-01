#include <stdio.h>
#include <stdlib.h>

//This function uses dynamic programming to find the LCS of two int arrays
void longestMutualSequence(int firstArr[], int secondArr[], int sizeA, int sizeB){
    
    //Initialising a 2D array with sizes sizeA+1 x sizeB+1
    int dp[sizeA + 1][sizeB + 1]; 
    //Creating a 2D array with the given arays as the heads of the rows and cols.
    for (int i = 0; i <= sizeA; i++) {
        for (int j = 0; j <= sizeB; j++)
            dp[i][j] = 0;
    }/* Bottom up we match the row and col integers and if they are equal then we mark the (i,j) as 1 
    and if consectively the rows and col ints match we mark that (i,j) as [previous location (diagonally) +1] */
    for (int i = sizeA - 1; i >= 0; i--) {
        for (int j = sizeB - 1; j >= 0; j--) {
            if (firstArr[i] == secondArr[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
        }
    }

        /* 
        -- ZX  ZY  ZZ  XX  XY  XZ
        X  0   0   0   0   0   0
        Y  0   0   0   0   0   0
        Z  0   0   0   0   0   0
        XX 0   0   0   3   0   0
        XY 0   0   0   0   2   0
        XZ 0   0   0   0   0   1
        // The THREE is our seq length and the corresponding i,j values are th starting points of the seqs for arr1 and arr2
        */

    //declaring the max len variable and the start i and j point variable used ahead
    int maxi = 0, maxj = 0, maxm = 0;
    // finding the max int in the 2d array which will be our max lenght and the corresponding i,j value as our starting points of the seqs
    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (maxm < dp[i][j]) {
                maxm = dp[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    //printing the results
    printf("Longest common sequence is");
    if (maxm > 0) {
        for (int i = 0; i < maxm; i++) {
            if (i < maxm - 1) printf(" %d,", firstArr[maxi + i]);
            else printf(" %d.\n", firstArr[maxi + i]);
        }
    }
}

//driver
int main() {
    int firstArr[] = { 1, 2, 3, 4, 1000, 90, 100, 110, 200, 202};
    int secondArr[] = { 1, 1, 2, 3, 90, 100, 110, 200, 202};
    int sizeA = sizeof(firstArr) / sizeof(firstArr[0]);
    int sizeB = sizeof(secondArr) / sizeof(secondArr[0]);
    longestMutualSequence(firstArr, secondArr, sizeA, sizeB);
    return 0;
}
