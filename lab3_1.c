#include <stdio.h>
int main()
{
    int num;
    printf("INPUT YOUR NUMBER : ");
    scanf("%d",&num);
    //reverse code
    for(int i = num;i > 1;i--)//จำนวนบรรทัด
    {
        for(int j = num;j>=1;j--)//renderฝั่งซ้าย
        {
            if(j>i)
            printf(" ");
            else if(j<=i)
            printf("#");
        }
        for (int k = 1; k < i; k++)//renderฝั่งขวา
        {
            printf("#");
        }
        
        printf("\n");
    }
    //reverse code
    for(int i = 1;i <= num;i++)//จำนวนบรรทัด
    {
        for(int j = num;j>=1;j--)//renderฝั่งซ้าย
        {
            if(j>i)
            printf(" ");
            else if(j<=i)
            printf("#");
        }
        for (int k = 1; k < i; k++)//renderฝั่งขวา
        {
            printf("#");
        }
        
        printf("\n");
    }
    
    return 0;
}