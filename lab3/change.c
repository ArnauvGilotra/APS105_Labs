#include <stdio.h>
int main()
{
    int inputAmount = 1;
    while (inputAmount > 0 && inputAmount < 100)
    {
        printf("Please give an amount in cents less than 100: ");
        scanf("%d",&inputAmount);
        int quarters = inputAmount/25;
        int dime = (inputAmount % 25)/10;
        int nickel = (inputAmount - quarters*25 - dime*10)/5;
        int cent = inputAmount - quarters*25 - dime*10 - nickel*5;
        if (inputAmount > 0 && inputAmount < 100)
        {
            if (quarters > 1)
            {
                printf("%d cents: %d quarters",inputAmount,quarters);
            } else if (quarters == 1)
            {
                printf("%d cents: %d quarter",inputAmount,quarters);
            } else
            {
                printf("%d cents: ",inputAmount);
            } 
            
            if (nickel == 0 && cent == 0)
            {
                if (quarters > 0){
                    if (dime > 1)
                    {
                        printf(" and %d dimes",dime);
                    } else if (dime == 1)
                    {
                        printf(" and %d dime",dime);
                    } else
                    {
                        printf("");
                    }
                }else
                {
                    if (dime > 1)
                    {
                        printf("%d dimes",dime);
                    } else if (dime == 1)
                    {
                        printf("%d dime",dime);
                    } else
                    {
                        printf("");
                    }
                }
                
            } else
            {
                if (quarters == 0)
                {
                    if (dime > 1)
                    {
                        printf("%d dimes",dime);
                    } else if (dime == 1)
                    {
                        printf("%d dime",dime);
                    } else
                    {
                        printf("");
                    }
                } else
                {
                    if (dime > 1)
                    {
                        printf(", %d dimes",dime);
                    } else if (dime == 1)
                    {
                        printf(", %d dime",dime);
                    } else
                    {
                        printf("");
                    }
                }
            }
            if (/*dime == 0 && cent == 0 ||*/ cent == 0)
            {
                if (quarters > 0)
                {
                    if (nickel > 1)
                    {
                        printf(" and %d nickels",nickel);
                    } else if (nickel == 1)
                    {
                        printf(" and %d nickel",nickel);
                    } else
                    {
                        printf("");
                    }
                } else
                {
                    if (dime == 0 && cent == 0)
                    {
                        if (nickel > 1)
                        {
                            printf("%d nickels",nickel);
                        } else if (nickel == 1)
                        {
                            printf("%d nickel",nickel);
                        } else
                        {
                        printf("");
                        }
                    } else if (dime == 0)
                    {
                        if (nickel > 1)
                        {
                            printf("%d nickels",nickel);
                        } else if (nickel == 1)
                        {
                            printf("%d nickel",nickel);
                        } else
                        {
                            printf("");
                        }
                    }else if (dime > 0 && cent == 0)
                        {
                        if (nickel > 1)
                        {
                            printf(", and %d nickels",nickel);
                        } else if (nickel == 1)
                        {
                            printf(", and %d nickel",nickel);
                        } else
                        {
                            printf("");
                        }
                    } 
                }   
            } else{
                    if (quarters == 0 && dime == 0)
                    {
                        if (nickel > 1)
                    {
                        printf("%d nickels",nickel);
                    } else if (nickel == 1)
                    {
                        printf("%d nickel",nickel);
                    } else
                    {
                        printf("");
                    }   
                } else
                {
                    if (nickel > 1)
                    {
                        printf(", %d nickels",nickel);
                    } else if (nickel == 1)
                    {
                        printf(", %d nickel",nickel);
                    } else
                    {
                        printf("");
                    }   
                }
            }
            if (quarters > 0 && dime == 0 && nickel == 0)
            {
                if (cent > 1)
                {
                    printf(" and %d cents.\n",cent);
                } else if (cent == 1)
                {
                    printf(" and %d cent.\n",cent);
                } else
                {
                    printf(".\n");
                }
            }else if (quarters == 0 && dime == 0 && nickel == 0)
            {
                if (cent > 1)
                {
                    printf("%d cents.\n",cent);
                } else if (cent == 1)
                {
                    printf("%d cent.\n",cent);
                } else
                {
                    printf(".\n");
                }
            }else
            {
                if (cent > 1)
                {
                    printf(", and %d cents.\n",cent);
                } else if (cent == 1)
                {
                    printf(", and %d cent.\n",cent);
                } else
                {
                    printf(".\n");
                }
            }  
        } else
        {
            printf("%d cents: invalid amount.\n",inputAmount);
        }
    }
    return 0;
}