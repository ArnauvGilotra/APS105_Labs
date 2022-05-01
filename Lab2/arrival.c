#include <stdio.h>
#include <math.h>
int main(void) {
    int currentTimeHrs;
    int currentTimeMins;
    double tripTime;
    int tripTimeHrs;
    int tripTimeMins;
    int arrivalTimeHrs;
    int arrivalTimeMins;
    printf("Enter current time: ");
    scanf("%d",&currentTimeHrs);
    scanf("%d",&currentTimeMins);
    printf("Enter trip time:");
    scanf("%lf",&tripTime);
    printf("Current time is %d:%d\n",currentTimeHrs,currentTimeMins);
    tripTimeHrs = tripTime/1;
    tripTimeMins = 60*(tripTime - tripTimeHrs);

    arrivalTimeMins = currentTimeMins + tripTimeMins;
    arrivalTimeHrs = currentTimeHrs + tripTimeHrs;
    if (arrivalTimeMins > 59){
        printf("%d",arrivalTimeMins);
        arrivalTimeMins = arrivalTimeMins - 60;
        arrivalTimeHrs = arrivalTimeHrs + 1;
    }
    
    if (arrivalTimeHrs > 23){
        arrivalTimeHrs = arrivalTimeHrs - 24;
        printf("Arrival Time is next day %02d:%02d",arrivalTimeHrs,arrivalTimeMins);
    } else {
        printf("Arrival Time is same day %d:%d",arrivalTimeHrs,arrivalTimeMins);
    } 
}
