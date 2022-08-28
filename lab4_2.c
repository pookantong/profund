#include <stdio.h>

int main()
{
    int count,count1;
    scanf("%d",&count);
    count1=count*count;
    for (int i = 1; i <= count1; i++)
    {
        printf("*");
        if (i%count==0)
        {
            printf("\n");
        }
    }
    
}