#include<stdio.h>
#include<Windows.h>
#include<conio.h>

void draw_ship(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
    GetStdHandle(STD_OUTPUT_HANDLE) , c);
    printf(" <-0-> ");
}

void erase_ship(int x,int y)
{
   COORD c = { x, y };
    SetConsoleCursorPosition(
    GetStdHandle(STD_OUTPUT_HANDLE) , c);
    printf("       ");
}

int main()
{
    char ch=' ';
    int x=38,y=20;
    do
    {
        if (_kbhit())
        {
            ch=_getch();
            if(ch=='a'&&x>0) {erase_ship(x,y);draw_ship(--x,y);}
            if(ch=='d'&&x<120) {erase_ship(x,y);draw_ship(++x,y);}
            if(ch=='s'&&y<30) {erase_ship(x,y);draw_ship(x,++y);}
            fflush(stdin);
        }
        Sleep(10);
    } while (ch!='x');
    return 0;
}