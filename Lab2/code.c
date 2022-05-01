#include <stdio.h>
int main(void) {
    int inputNumber;
    int realDigit2;
    int realDigit3; //3333
    printf("Enter an encrypted 4-digit combination: ");
    scanf("%d",&inputNumber);
    int i = 0;
    int digits[4];
        while(inputNumber != 0){
            int digit = inputNumber % 10;
            inputNumber = inputNumber / 10;
            digits[i] = digit;
            i = i + 1;
    }

    realDigit2 = 9-digits[2];
    realDigit3 = 9-digits[1];
    printf("The real combination is: %d%d%d%d", digits[0],realDigit2,realDigit3,digits[3]);
    return 0;
}