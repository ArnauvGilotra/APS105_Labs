#include<stdio.h>
#include<string.h>
#include<math.h>
//This Code will print pascals triangle. 
// Making the function to print Pascal's Triangle. "i" means we are on "(i+1)" row while buildArray is the pascal's triangle values of previous row
void PascalsTriangle(int requiredRows, int i, int* buildArray) {
    // if i>=n is true then it means we have printed all the inputed rows of the pascal triangle
    if (i >= requiredRows)
        return;
    int j;
    // printing spaces before each row
    for (j = 0; j < requiredRows - 1 - i; ++j) {
        printf("   ");
    }
    // First we calculate post which we print calculating then printing the data of the "i" row of the Pascals Trianle
    for (j = i; j >= 0; --j) {
        if (j == 0 || j == i)
            buildArray[j] = 1;
        else
            buildArray[j] = buildArray[j - 1] + buildArray[j];
            if (buildArray[j] <= 9){
                printf("%d     ", buildArray[j]);
            } else if (buildArray[j] > 9 && buildArray[j] < 100)
            {
                printf("%d    ", buildArray[j]);
            }else if (buildArray[j] >= 100)
            {
                printf("%d   ", buildArray[j]);
            }
    }
    printf("\n");
    PascalsTriangle(requiredRows, i + 1, buildArray);
}
//This Code will print pascals triangle. 
int main() {
    int requiredRows = 1;
    int buildArray[100];
    while(requiredRows <= 13 && requiredRows > 0) {
      printf("Enter the number of rows: "); 
      scanf("%d", &requiredRows);
      buildArray[0] = 1;
      PascalsTriangle(requiredRows, 0, buildArray);
    }
    return 0;
}