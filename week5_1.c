#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    int count=0;
    scanf("%s",str);
    for (int i = 0; i < strlen(str); i++)
    {
        while (str[i]<58&&str[i]>47)//ถ้าเป็นตัวเลข
        {
            count*=10;
            count+=str[i]-48;//แปลงค่าจากcharกลายเป็นint
            i++;//เพิ่ม i เพื่อหาว่าตัวต่อไปเป็นเลขหรือไม่
        }
        for (int j = 0; j < count; j++)//print เฉพาะตัวที่ติดกับเลขเท่าน้ัน
        {
            printf("%c",str[i]);
        }
        if (!(str[i]<58&&str[i]>47)&&!(str[i-1]<58&&str[i-1]>47))//ไม่ใช่เลขและตัวข้างหน้าไม่ใช่เลข
        {
            printf("%c",str[i]);
        }
        count=0;
    }
    return 0;
}

