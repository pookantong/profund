#include<stdio.h>
#include<math.h>

int main()
{
    int num;
    int result;
    scanf("%d",&num);
    result = (num*(num-1))/2;
    printf("%d",result);
    return 0;
}