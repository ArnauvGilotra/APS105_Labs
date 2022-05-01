#include <stdio.h>
int main()
{
    int i, j;
    int requiredRows;//5
    printf("Enter the number of rows in the triangle: ");
    scanf("%d",&requiredRows);
    for(i=1; i<=requiredRows; i = i+1)
    {
        for(j=i; j<requiredRows; j = j+1)
        {
            printf(" ");
        }
        for(j=1; j<=(2*i-1); j = j+1)
        {
            if(i==requiredRows || j==1 || j==(2*i-1))
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}