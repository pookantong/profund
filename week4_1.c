#include <stdio.h>

int main()
{
    int count;
    scanf("%d",&count);
    for (int i = 0; i < count; i++)//จำนวนบรรทัด
    {
        for (int j = 0; j < count; j++)//จำนวนตัวในบรรทัด
        {
            printf("*");
        }
        printf("\n");
    }
    
    return 0;
}