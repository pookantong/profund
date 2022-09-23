#include <stdio.h>

int main()
{
    int result=0;
    int sum=0;
    int amount;
    scanf("%d",&amount);
    int versum[amount];
    int num[amount*amount];

    for (int i = 0; i < amount*amount; i++)
    {
        scanf("%d",&num[i]);
    }

    for (int i = 0; i < amount; i++)
    {
        versum[i]=0;
    }

    for (int i = 0; i < amount; i++)
    {
        result += num[i];
    }

    for (int i = 0;i < amount*amount;i++)
    {
        sum += num[i];
        if ((i+1)%amount==0)
        {
            if (sum != result)
            {
                printf("NO");
                return 0;
            }
            sum = 0;
        }
    }
    
    for (int i = 0;i < amount*amount;i++)
    {
        if ((i+1)%amount!=0)
        {
            versum[((i+1)%amount)-1]+=num[i];
        }
        else
        {
            versum[amount-1]+=num[i];
        }
    }

    for (int i = 0; i < amount; i++)
    {
        if (versum[i] != result)
        {
            printf("NO");
            return 0;
        }
    }
    
    for (int i = 0; i < amount*amount; i+=amount+1)
    {
        sum += num[i];
    }
    if (sum != result)
    {
        printf("NO");
        return 0;
    }
    sum = 0;

    for (int i = amount-1; i < amount*amount; i+=amount-1)
    {
        if (i<amount*amount-1)
        {
            sum += num[i];
        }
    }
    printf("%d %d",sum,result);
    if (sum != result)
    {
        printf("NO");
        return 0;
    }

    printf("YES");

    return 0;
}