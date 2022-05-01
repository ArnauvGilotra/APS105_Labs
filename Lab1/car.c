#include <stdio.h>
int main(void) {
   printf("Enter the daily rate: ");
   double dailyRate, numDays;
   const double HST = 1.13;
   scanf("%lf",& dailyRate); 
   printf("Enter the rental period (in days): \n");
   scanf("%lf",& numDays);
   int nonPaidDays = numDays/4;
   int paidDays = numDays - nonPaidDays;
   double rate = (paidDays*dailyRate)*HST;
   printf("Your total free day(s) in this rental is: %d \n",nonPaidDays);
   printf("Your total charge including taxes is: %.2f \n",rate);
   return 0;
}