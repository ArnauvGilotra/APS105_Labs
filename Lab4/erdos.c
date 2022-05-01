#include <stdio.h>
#include <stdbool.h>
//This Code will print Erdos-Woods Number with a certain range of K & A values. 
int main(void) {
    //declaring the reqd gcd function
    int gcd(int a, int b);

    //declaring variables reqd
    int aFinal;
    int eWood;
    int counter;
    bool exit = false;

    //start taking input from the user
    //simple while loops to ensure correct user input is only accepted as per handout
    int kStart = 1;
    while (kStart <= 2)
    {
        printf("Enter the number to start searching for k (> 2, inclusive): ");
        scanf("%d",&kStart);
    }
    int kEnd = 1;
    while (kEnd < kStart)
    {
        printf("Enter the number to stop searching for k (inclusive): ");
        scanf("%d",&kEnd);
    }
    int aStart = 0;
    while (aStart <= 0)
    {
        printf("Enter the number to start searching for a (> 0, inclusive): ");
        scanf("%d",&aStart);
    }
    int aEnd = 0;
    while (aEnd < aStart)
    {
        printf("Enter the number to stop searching for a (inclusive): ");
        scanf("%d",&aEnd);
    }

    //Erdos-Woods Loops to go here. 
    /*
            [Loop Hierarchy]
                Grandfather goes through the intial k value from the last k value 
                    father goes through the intial a value to the last a value
                        child inherits the current iterating k value from grandparent and current ierating a value from parent
                            {
                                child inputs the k and a values with him to the gcd function to find non co prime k & a
                                if found... child updates grandparent to exit
                                if not grandparent and parent move the next k and a value which are inherited by the child again
                                and so on
                            }
            Print result outside the loop
    */
    //iterate from kStart val to kEnd value //GrandParent
    for (int i = kStart; i <= kEnd; i++)
    {
        if(exit == true) // exit when eWood and aFinal found and printed
        {
            break;
        } else
        {
            //print the required "trying statement iterating through k until exit"
            printf("Trying k = %d...\n", i);
            // iterate from aStart t aEnd //Parent 1
            for(int j = aStart; j <= aEnd; j++)
            {
                counter = 0;
                // interate through j (current a value from parent loop) to j + i (current a from parent loop and k value from the grandparent loop).
                for (int l = j; l <= j+i; l++) //child
                {
                    if(gcd(j,l) > 1 || gcd(j+i, l) > 1)
                    {
                    counter = counter + 1; //tracks all the vals from j to j+i that arent co-prime.

                    }
                }
                if (counter == i+1){
                    aFinal = j;
                    eWood = i;
                    exit = true;
                }
                
            }
        }
    }
    //print final result
    printf("Erdos-Woods number: %d\na: %d", eWood, aFinal);
    return 0;
}
/* GCD function using
    Methododlogy and tools used
    1. "%=" Modulus AND assignment operator. It takes modulus using two operands and assigns the result to the left operand. C %= A is equivalent to C = C % A
    2. "^=" Bitwise exclusive OR and assignment operator. C ^= 2 is same as C = C ^ 2

    benefits:
    Low memory utlization
    No temporarty variable creation leads to reduction in CPU cycles

    Why:
    To not cause timeouts in examify.ca
*/
int gcd(int a, int b)
{
    while (b != 0)
    {
        a %= b;
        a ^= b;
        b ^= a;
        a ^= b;
    }
    return a;
}