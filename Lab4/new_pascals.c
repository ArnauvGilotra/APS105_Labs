#include <stdio.h>
//This Code will print pascals triangle. 
// declaring input variable and a variable to print spaces
int requiredRows = 0;
int spacesPrefix = 0;

// declaring required functions according to the handout
void triangle(int requiredRows);
int choose(int n, int r);
int factorial(int n);

//new fucntion for printing spaces before each row
void printPrefixToRowSpaces(int spacesPrefix);
//This Code will print pascals triangle. 
int main() {
    // while loop used to run only when conditions met
    while (requiredRows >= 0 && requiredRows <= 13) {
        printf("Enter the number of rows: ");
        scanf("%d", &requiredRows);
        if (requiredRows > 13)
        {
            return 0;
        }
        triangle(requiredRows);
    }
    return 0;
}

// prints triangle
void triangle(int requiredRows) {
    
    // declaring variables required for "n" C "r" calculation 
    int n;
    int r;
    int digit_nCr;
    spacesPrefix = requiredRows;
    
    /* nested for loop used to print the spaces before the rows then calculating the number at each 
    position then printing them with appropriate spaces */
    for (n = 0; n < requiredRows; ++n) {
        printPrefixToRowSpaces(spacesPrefix);
        
        // nested for loop used with counter r as counter for calculation of nCr
        for (r = 0; r <= n; ++r) {
            digit_nCr = choose(n, r);
            
            if (digit_nCr < 10) {
                printf("%d     ", digit_nCr);
            } else if (digit_nCr >= 10 && digit_nCr < 100) {
                printf("%d    ", digit_nCr);
            } else {
                printf("%d   ", digit_nCr);
            }
        }
        
        //spacesPrefix reduces by one to print correct amount of spaces when iterating for printing later rows.
        spacesPrefix--;
        printf("\n");
    }
}

//calculates the number of spaces before each row according to the number of rows
void printPrefixToRowSpaces(int spacesPrefix) {
    spacesPrefix = spacesPrefix * 3 - 3;
    printf("%*s", spacesPrefix, "");
}

// choose function to calculate nCr according to handout formual
int choose(int n, int r) {
    int value;
    value = (factorial(n)) / ((factorial(r)) * (factorial(n-r)));
    return value;
}

// calculates the n! Factorial of an integer value
int factorial(int n) {
    int product;
    
    if (n == 0) {
        return 1; 
    } else {
        product = 1;
        for (int i = 1; i <= n; i++) {
            product *= i;
        }
        return product;
    }
}

/*this pascals triangle is actually a poor implementation. It fails due to integer overflow. A good implementation would not calcuate the factorial or nCr at all
rather if would use the special property of the traingle to calulate the postion value from the 2 value of the above row between which it will be placed in the rows below
it is close to 300 times faster and unbreakable until the space runs out int he terminal. refer to my previous attempts if they visible to instructors.
*/
