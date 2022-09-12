#include<stdio.h>
  
int main()
{
    char text[100];
    int count1 = 0;
    int count2 = 0;
    char *p;
    p=text;
    scanf("%s",text);
    while (*p!='\0')
    {
        if (*p >= 'A'&&*p <='Z')
        {
            count1++;
        }
        else if (*p >= 'a'&&*p <='z')
        {
            count2++;
        }
          
        p++;
    }
    printf("Capcount = %d\nSmallcount = %d",count1,count2);
    return 0;
}