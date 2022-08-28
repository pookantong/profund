#include <stdio.h>
int main()
{
    long sum=0;
    int count=0;
    for (int i = 1; i < 1000000; i++)
    {
        sum+=i;
        for (int j = 1; j <= sum; j++)
        {
            if (sum%j==0)
            {
                count++;
            }
            if (count==500)
            {
                printf("%ld",sum);
            }
        }
        count=0;
        
    }
    
    return 0;
}