#include <stdio.h>

int main()
{
    int result=0;
    int sum=0;
    int amount;
    scanf("%d",&amount);
    int num[amount][amount];

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            scanf("%d",num[i][j]);
        }
        
    }

    for (int i = 0; i < amount; i++)
    {
        result += num[0][i];
    }
    
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            sum += num[i][j]; 
        }
        if (sum != result)
        {
            printf("NO");
            return 0;
        }
        sum=0;
    }
    
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            sum += num[j][i]; 
        }
        if (sum != result)
        {
            printf("NO");
            return 0;
        }
        sum=0;
    }
    
    for (int i = 0; i < amount; i++)
    {
        sum += num[i][i];
    }
    if (sum != result)
        {
            printf("NO");
            return 0;
        }
    sum=0;

    for (int i = 0; i < amount; i++)
    {
        sum += num[i][amount-1-i];
    }
    if (sum != result)
        {
            printf("NO");
            return 0;
        }

    printf("YES");
    return 0;
}