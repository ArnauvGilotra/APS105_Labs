#include <stdio.h>
int main(void) {
   //Declare required variables and arrays
   int thresholdTemp;
   int boilingTemp;
   int setBoilingPoints [5] = {100, 357, 1187, 2193, 2660};
   int upperbounds [5];
   int lowerbounds [5];
   
   // Request threshold and boilingpoint inputs from the user
   printf("Enter the threshold in Celsius: ");
   scanf("%d",&thresholdTemp);
   printf("Enter the observed boiling point in Celsius: ");
   scanf("%d",&boilingTemp);

   //calculate upper and lower bounds using for loop
   for (int i = 0; i < 5; i = i+1){
        upperbounds [i] = setBoilingPoints[i] + thresholdTemp;
        lowerbounds [i] = setBoilingPoints[i] - thresholdTemp;
   }
   
   //Figuring out which substance could it be using if else statements
   if (boilingTemp <= upperbounds[0] && boilingTemp >= lowerbounds[0]){
       printf("The substance you tested is: Water");
   } else if (boilingTemp <= upperbounds[1] && boilingTemp >= lowerbounds[1])
   {
       printf("The substance you tested is: Mercury");
   } else if (boilingTemp <= upperbounds[2] && boilingTemp >= lowerbounds[2])
   {
       printf("The substance you tested is: Copper");
   } else if (boilingTemp <= upperbounds[3] && boilingTemp >= lowerbounds[3])
   {
       printf("The substance you tested is: Silver");
   } else if (boilingTemp <= upperbounds[4] && boilingTemp >= lowerbounds[4])
   {
    printf("The substance you tested is: Gold");  
   } else
   {
    printf("Substance unknown.");
   }
   return 0;
}

//The substance you tested is: Mercury
//Water 100
//Mercury 357
//Copper 1187
//Silver 2193
//Gold 2660