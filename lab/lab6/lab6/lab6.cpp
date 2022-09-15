#include<stdio.h>
#include<Windows.h>
#include<conio.h>

void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void draw_ship(int x, int y)
{
    setcolor(2, 4);
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf(" <-0-> ");
}

void draw_bullet(int x, int y)
{
    setcolor(1, 0);
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("o");
}

void erase_bullet(int x, int y)
{
    setcolor(0, 0);
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf(" ");
}

void erase_ship(int x, int y)
{
    setcolor(0, 0);
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("       ");
}

void bullet_shoot(int x, int y)
{
    if (y > 0)
    {
       erase_bullet(x, y); draw_bullet(x, --y); 
    }
    else
    {
        erase_bullet(x, y);
    }
}

int main()
{
    char ch = ' ';
    int x, y;
    x = 23;
    y = 25;
    int bull_x[5];
    int bull_y[5];
    int bullet_state[5];
    int r_state = 0, l_state = 0, stop = 0;
    int i=0;
    setcursor(0);
    do
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a') 
            { 
                r_state = 0; l_state = 1; stop = 0;
            }
            if (ch == 'd') 
            {
                r_state = 1; l_state = 0; stop = 0;
            }
            if (ch == 's') 
            {
                r_state = 0; l_state = 0; stop = 1;
            }
            if (ch == ' '&& i<5)
            {
                bull_y[i] = 24;
                bull_x[i] = x + 3;
                bullet_state[i] = 1;
                i++;
            }
            else if (i == 5 && (bullet_state[0] == 0 || bullet_state[1] == 0 || bullet_state[2] == 0 || bullet_state[3] == 0 || bullet_state[4] == 0))
            {
                i = 0;
            }
            fflush(stdin);
        }

        if (l_state == 1 && x > 0)
        {
            erase_ship(x, y); draw_ship(--x, y); Sleep(20);
        }
        else if(l_state == 1 && x <= 0)
        {
            Sleep(20);
        }
        if (r_state == 1 && x < 113)
        {
            erase_ship(x, y); draw_ship(++x, y); Sleep(20);
        }
        else if (r_state == 1 && x >= 113)
        {
            Sleep(20);
        }
        if (stop == 1)
        {
            Sleep(20);
        }
        if (bullet_state[0] == 1)
        {
            bullet_shoot(bull_x[0], --bull_y[0]);
            if (bull_y[0] <= 0)
            {
                bullet_state[0] = 0;
            }
        }
        if (bullet_state[1] == 1)
        {
            bullet_shoot(bull_x[1], --bull_y[1]);
            if (bull_y[1] <= 0)
            {
                bullet_state[1] = 0;
            }
        }
        if (bullet_state[2] == 1)
        {
            bullet_shoot(bull_x[2], --bull_y[2]);
            if (bull_y[2] <= 0)
            {
                bullet_state[2] = 0;
            }
        }
        if (bullet_state[3] == 1)
        {
            bullet_shoot(bull_x[3], --bull_y[3]);
            if (bull_y[3] <= 0)
            {
                bullet_state[3] = 0;
            }
        }
        if (bullet_state[4] == 1)
        {
            bullet_shoot(bull_x[4], --bull_y[4]);
            if (bull_y[4] <= 0)
            {
                bullet_state[4] = 0;
            }
        }
    } while (ch != 'x');
    return 0;
}