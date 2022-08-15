#include <stdio.h>


int main()
{
    int num;
    printf("Enter number : ");
    scanf("%d",&num);
    printf("Factoring Result : ");
    while (num>=1)
    {
        for(int i = 2;i<=num;i++)
        {
            if (i!=num&&num%i==0)
            {
                printf("%d x ",i);
                num/=i;
                i=1;
            }
            else if (i==num)
            {
                printf("%d",i);
                num/=i;
            }
            
        }

    }
    
    


    
    
}