#include <stdio.h>


int main()
{
    int num1,num2,greater_num;
    printf("Enter first number : ");
    scanf("%d",&num1);
    printf("Enter second number : ");
    scanf("%d",&num2);
    printf("Greatest common divisor = ");
    if (num1>num2)
    {
        greater_num=num1;
    }
    else if (num2>num1)
    {
        greater_num=num2;
    }
    for (int i = greater_num; i > 1; i--)
    {
        if (num1%i==0&&num2%i==0)
        {
            printf("%d",i);
            return 0;
        }
    }
    
    
}