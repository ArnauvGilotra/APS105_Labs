#include <stdio.h>
#include <math.h>
int main(void) {
double purchasePrice;
double downPaymnet;
double financingTerm;
double monthlyRate;
double monthlyPayment;
double num;
double denom;
printf("Enter the purchase price P: ");
scanf("%lf",&purchasePrice);
printf("Enter the amount of down payment D: ");
scanf("%lf",&downPaymnet);
printf("Enter the finance term (in months): ");
scanf("%lf",&financingTerm);
printf("Enter the monthly interest rate (in percent):");
scanf("%lf",&monthlyRate);
monthlyRate=monthlyRate/100;

num = (purchasePrice - downPaymnet)*monthlyRate*pow((1+monthlyRate), financingTerm);

denom = pow((1+monthlyRate), financingTerm) - 1;

monthlyPayment = num/denom;
printf("The monthly payment is: %.2f", monthlyPayment);
}