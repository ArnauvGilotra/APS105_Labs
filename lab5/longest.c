#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void longestSequence(int a[], int sizeA);

//driver
int main(){
//int a[] = {1, 2, 3, 3, 4, 5, 6, 30, 0};
int a[] = {2};
//int a[] = {-1, 0,-2, 1, -3, 3, -10, 5, -5, 8, -8,-10, 10, -6, 6, -7, 7, -9, 9, 0};
longestSequence(a, 1);
//longestSequence(a, 20);
return 0;
}

void longestSequence(int a[], int sizeA){
//declare the required variables
    int previous_len=0, start=0, len=0;

    //iterate till the second last number in any arr
    for (int i = 0; i < (sizeA)-1; ++i) {
        //check if the number currenlty being iterated is less than the next number in the arr
        if(a[i+1] > a[i]) {
            len++; //yes - then Seq Len increases
            //check if the new seq len is more than the previous longest seq len
            if (len > previous_len) {
                previous_len=len; // updates previous len
                start=i+1-len; // updates the starting point of the seq in the arr
            }
        } else {       
            len=0; // No - Seq Len is reset to ZERO
        }
    //Printing using iteration - 
} printf("Longest sequence is ");
//printf("Start: %d",start);
    for(int i = 0; i <= previous_len; ++i) {
        if(i < previous_len) printf("%d, ",a[start+i]); 
        else printf("%d.",a[start+i]);
    }
}

