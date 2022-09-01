#include <stdio.h>

int main()
{
    int count,count1;
    scanf("%d",&count);
    count1=count*count;//จำนวนครั้งที่ต้องการกว้าง*สูง
    for (int i = 1; i <= count1; i++)
    {
        printf("*");
        if (i%count==0)
        {
            printf("\n");//เว้นบรรทัดเมื่อครบจำนวนใน1บรรทัดแล้ว
        }
    }
    
}