#include <stdio.h>
int main(void){
    double median(int A[], int B[], int sizeA, int sizeB);

    int A[5] = {1,2,11,12,100};
    int B[5] = {3,11,20,500,600};

    printf("%.2f\n",median( A, B, 5,5));
    return 0;
}
//This function fins the median of sorted arrays
//Inspired and derived from "find Kth largest/smallest elements of an array"
//THe idea is to reduce the array size for easier and quicker computation
double median(int A[], int B[], int sizeA, int sizeB) {
    int getMiddleElement(int A[], int sizeA, int B[], int sizeB, int k);
    int combinedLength = sizeA + sizeB;
    //for even size
    if((combinedLength % 2) == 1) {
      return getMiddleElement(A, sizeA, B, sizeB, combinedLength/2);
      //for odd size
    } else {
      double a = (double)getMiddleElement(A, sizeA, B, sizeB, (combinedLength-1)/2);
      double b = (double)getMiddleElement(A, sizeA, B, sizeB, combinedLength/2);
      return (a + b)/2.0;
    }
}

/*

Consider an arr = {1,4,5,32,44,66} and we need to find the kth largest number. 
let K be 3. Hence we need to find the THIRD largest number which is 32

How this helps is that the time complexity is much much less since we are not really merging the Arrays 
along with the fact that we are not creating a whole new array leads to muh less memory use.

Why did I use this method?
I recently did KthLargest number question leetcode. It clicked that I could use this method to 
find the median of any array since the median will be basically the kth largest number and k will be te lenght/2 or (lenght-1)/2 depending on whether 
the array lenght is odd or even. It seemed easier for me to implement. 

*/

//This fucntion find the kth (k = combinedLength/2 or (combinedLength-1)/2). This basically finds you the middle values of the provided array without really merging them.
int getMiddleElement(int A[], int sizeA, int B[], int sizeB, int k) {
    //The idea here is to redice the array size and to focus on paticular side of the arrya depending upon the sum of sizeA + sizeB, k and sizeA and sizeB themselves
    if(sizeA <= 0) return B[k];
    if(sizeB <= 0) return A[k];
    if(B[sizeB/2] >= A[sizeA/2]) {
        if((sizeA/2 + sizeB/2) >= k)
            return getMiddleElement(A, sizeA, B, sizeB/2, k);
        else
            return getMiddleElement(A + sizeA/2 + 1, sizeA - (sizeA/2 + 1), B, sizeB, k - (sizeA/2 + 1));
        } else {
            if((sizeA/2 + sizeB/2) >= k)
                return getMiddleElement(A, sizeA/2, B, sizeB, k);
            else
                return getMiddleElement(A, sizeA, B + (sizeB/2 + 1), sizeB - (sizeB/2 + 1), k - (sizeB/2 + 1));
    }
}