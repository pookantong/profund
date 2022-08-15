#include <stdio.h>
int main()
{
    int num;
    printf("INPUT YOUR NUMBER : ");
    scanf("%d",&num);
    for(int i = 1;i <= num;i++)
    {
        for(int j = num;j>=1;j--)
        {
            if(j>i)
            printf(" ");
            else if(j<=i)
            printf("#");
        }
        for (int k = 1; k < i; k++)
        {
            printf("#");
        }
        
        printf("\n");
    }

    
    return 0;
}