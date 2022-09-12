#include<stdio.h>
#include<string.h>
  
int main()
{
    char text[100];
    int count1 = 0;
    int count2 = 0;
    scanf("%s",text);
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i]>=65&&text[i]<=90)
        {
            count1++;
        }
        if (text[i]>=97&&text[i]<=122)
        {
            count2++;
        }
    }
    
    printf("Capcount = %d\nSmallcount = %d",count1,count2);
    return 0;
}