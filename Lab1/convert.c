#include <stdio.h>
int main(void) {
   const int inchesToYards = 36;
   const int inchesToFeet = 12;
   const double cmsToInches = 2.54; 
   double input_Ms;
   double inches;
   int yards;
   int feet;
   int remaining_inches;
   double remaining_inches_decimal;
   printf("Please provide a distance in metres: \n");
   scanf("%lf",& input_Ms);
   input_Ms = input_Ms*100; 
   inches = input_Ms/cmsToInches; 
   yards = inches/inchesToYards; 
   feet = (inches - (yards*inchesToYards))/inchesToFeet;
   remaining_inches = inches - (yards*inchesToYards) - (feet*inchesToFeet);
   remaining_inches_decimal = inches - (yards*inchesToYards) - (feet*inchesToFeet) - remaining_inches;
   printf("%d yards, %d feet, %d inches, and %.2f inch remainder\n", yards, feet, remaining_inches, remaining_inches_decimal);
   return 0;
}