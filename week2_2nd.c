#include <stdio.h>
int main()
{
    int num;
    printf("INPUT YOUR NUMBER : ");
    scanf("%d",&num);
    for(int i = 1;i <= num;i++)//จำนวนบรรทัด
    {
        for (int j = num; j > i; j--)//เว้นเป็นรูปสามเหลี่ยมเฉียงลง
        {
            printf(" ");
        }
        for (int k = 1; k < i*2; k++)//แสดงผลเพิ่มทีละ2ต่อบรรทัด
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}