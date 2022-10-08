#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include <thread>

#include <windows.h>
#define screen_x 80
#define screen_y 25
HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };

int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    return 0;
}


void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

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
    gotoxy(x, y);
    printf(" <-0-> ");
}

void draw_bullet(int x, int y)
{
    setcolor(1, 0);
    gotoxy(x, y);
    printf("o");
}

void erase_bullet(int x, int y)
{
    setcolor(0, 0);
    gotoxy(x, y);
    printf(" ");
}

void erase_ship(int x, int y)
{
    setcolor(0, 0);
    gotoxy(x, y);
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

void draw_star(int x, int y)
{
    setcolor(3, 0);
    gotoxy(x, y);
    printf("*");
}

void draw_point()
{
    setcolor(3, 0);
    gotoxy(67, 0);
    printf(" ");
}

int Random1()
{
    int lower1 = 10;
    int upper1 = 70;
    int num = (rand() % (upper1 - lower1 + 1)) + lower1;
    return num;
}

int Random2()
{
    int lower2 = 2;
    int upper2 = 5;
    int num = (rand() % (upper2 - lower2 + 1)) + lower2;
    return num;
}

char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (
        !ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

        return '\0';
    else
        return buf[0];
}

int main()
{
    setConsole(screen_x, screen_y);
    srand(time(0));
    for (int i = 0; i < 20; i++)
    {
        draw_star(Random1(), Random2());
    }
    char ch = ' ';
    int j = 0;
    int x, y;
    x = 37;
    y = 20;
    int bull_x[5];
    int bull_y[5];
    int bullet_state[5];
    int r_state = 0, l_state = 0, stop = 0;
    int i = 0;
    int point = 0;
    setcursor(0);
    do
    {
        draw_ship(x, y);
        draw_point();
        printf("Points = %d", point);
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
            if (ch == ' ' && i < 5)
            {
                bull_y[i] = 19;
                bull_x[i] = x + 3;
                bullet_state[i] = 1;
                i++;
            }
            else if (i <= 5 && bullet_state[i - 1] == 0)
            {
                i = 0;
            }
            fflush(stdin);
        }

        if (l_state == 1 && x > 0)
        {
            erase_ship(x, y); draw_ship(--x, y);
        }
        else if (l_state == 1 && x <= 0)
        {

        }
        if (r_state == 1 && x < 73)
        {
            erase_ship(x, y); draw_ship(++x, y);
        }
        else if (r_state == 1 && x >= 73)
        {

        }
        if (stop == 1)
        {

        }
        for (j = 0; j < i; j++)
        {
            if (cursor(bull_x[j], bull_y[j] - 1) == '*')
            {
                erase_bullet(bull_x[j], bull_y[j]);
                erase_bullet(bull_x[j], bull_y[j] - 1);
                bullet_state[j] = 0;
                draw_star(Random1(), Random2());
                bull_x[j] = 0;
                bull_y[j] = 0;
                point++;
                draw_point();
                printf("Points = %d", point);
                std::thread q(Beep, 1000, 500);
                q.detach();
            }
            if (bullet_state[j] == 1)
            {
                bullet_shoot(bull_x[j], bull_y[j]--);
                if (bull_y[j] < 0)
                {
                    bullet_state[j] = 0;
                    erase_bullet(bull_x[j], bull_y[j]);

                }
            }
        }
        Sleep(20);
    } while (ch != 'x');
    return 0;
}