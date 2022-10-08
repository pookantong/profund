#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#define screen_x 80
#define screen_y 25
HANDLE wHnd;
HANDLE rHnd;
int hp = 10;
DWORD fdwMode;
INPUT_RECORD eventBuffer[2000];
int color = 7;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
typedef struct STAR
{
    int x;
    int y;
} star;
typedef struct BULLET
{
    int x;
    int y;
} bullet;
typedef struct SHIP
{
    int x;
    int y;
} ship;

void    gotoxy(short int x, short int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
        ENABLE_MOUSE_INPUT;
    SetConsoleMode(rHnd, fdwMode);
    return 0;
}

int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    return 0;
}

//EXAMPLE 
void fill_data_to_buffer()
{
    for (int y = 0; y < screen_y; ++y)
    {
        for (int x = 0; x < screen_x; ++x)
        {
            consoleBuffer[x + screen_x * y].Char.AsciiChar = 65 + (rand() % 25);
            consoleBuffer[x + screen_x * y].Attributes = rand() % 255;
        }
    }
}

void    setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpcursor;
    lpcursor.bVisible = visible;
    lpcursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpcursor);
}

void drawship(ship destine)
{
    consoleBuffer[destine.x + screen_x * destine.y].Char.AsciiChar = '0';
    consoleBuffer[(destine.x - 1) + screen_x * destine.y].Char.AsciiChar = '-';
    consoleBuffer[(destine.x + 1) + screen_x * destine.y].Char.AsciiChar = '-';
    consoleBuffer[(destine.x - 2) + screen_x * destine.y].Char.AsciiChar = '<';
    consoleBuffer[(destine.x + 2) + screen_x * destine.y].Char.AsciiChar = '>';
    consoleBuffer[destine.x + screen_x * destine.y].Attributes = color;
    consoleBuffer[(destine.x - 1) + screen_x * destine.y].Attributes = color;
    consoleBuffer[(destine.x + 1) + screen_x * destine.y].Attributes = color;
    consoleBuffer[(destine.x - 2) + screen_x * destine.y].Attributes = color;
    consoleBuffer[(destine.x + 2) + screen_x * destine.y].Attributes = color;
}

void drawbullet(bullet death)
{
    consoleBuffer[death.x + screen_x * death.y].Char.AsciiChar = '^';
    consoleBuffer[death.x + screen_x * death.y].Attributes = 4;
}

void drawstar(star t)
{
    /*if (consoleBuffer[(t.x + screen_x * t.y)].Char.AsciiChar != ' ')
    {
        hp -= 1;
        do
        {
            t.x = rand() % 80;
            t.y = 1;
        }
        while (consoleBuffer[t.x + (screen_x * t.y)].Char.AsciiChar == '*');
    }*/
    consoleBuffer[(t.x + screen_x * t.y)].Char.AsciiChar = '*';
    consoleBuffer[(t.x + screen_x * t.y)].Attributes = 6;
}

void eraseship(ship destine)
{
    consoleBuffer[destine.x + screen_x * destine.y].Char.AsciiChar = ' ';
    consoleBuffer[(destine.x - 1) + screen_x * destine.y].Char.AsciiChar = ' ';
    consoleBuffer[(destine.x + 1) + screen_x * destine.y].Char.AsciiChar = ' ';
    consoleBuffer[(destine.x - 2) + screen_x * destine.y].Char.AsciiChar = ' ';
    consoleBuffer[(destine.x + 2) + screen_x * destine.y].Char.AsciiChar = ' ';
    consoleBuffer[destine.x + screen_x * destine.y].Attributes = 0;
    consoleBuffer[(destine.x - 1) + screen_x * destine.y].Attributes = 0;
    consoleBuffer[(destine.x + 1) + screen_x * destine.y].Attributes = 0;
    consoleBuffer[(destine.x - 2) + screen_x * destine.y].Attributes = 0;
    consoleBuffer[(destine.x + 2) + screen_x * destine.y].Attributes = 0;
}

void erasebullet(bullet death)
{
    consoleBuffer[death.x + screen_x * death.y].Char.AsciiChar = ' ';
    consoleBuffer[death.x + screen_x * death.y].Attributes = 0;
}

void erasestar(star t)
{
    consoleBuffer[t.x + (screen_x * t.y)].Char.AsciiChar = ' ';
    consoleBuffer[t.x + (screen_x * t.y)].Attributes = 0;
}

void fill_buffer_to_console()
{
    WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}

int main()
{
    star t[80];
    //char ch = ' ';
    ship destine;
    bullet death[5];
    DWORD numEvents = 0;
    DWORD numEventsRead = 0;
    bool play = true;
    int i;
    int flag = 0;

    setConsole(screen_x, screen_y);
    setMode();
    setcursor(0);
    srand(time(NULL));
    i = 0;
    destine.x = 40;
    destine.y = 10;
    while (i < 20)
    {
        do
        {
            t[i].x = rand() % 80;
            t[i].y = rand() % 25;
        } while (consoleBuffer[t[i].x + screen_x * t[i].y].Char.AsciiChar == '*');
        drawstar(t[i]);
        i++;
    }
    while (play)
    {
        drawship(destine);
        GetNumberOfConsoleInputEvents(rHnd, &numEvents);
        fill_buffer_to_console();
        gotoxy(40, 10);
        printf("HP = %d", hp);
        i = 0;
        while (i < 20)
        {
            erasestar(t[i]);
            if (t[i].y == 24)
            {
                do
                {
                    t[i].x = rand() % 80;
                    t[i].y = 1;
                } while (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '*');
                drawstar(t[i]);
            }
            else if (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '-'
                || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '<'
                || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '>'
                || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '0')
            {
                hp -= 1;
                do
                {
                    t[i].x = rand() % 80;
                    t[i].y = 1;
                } while (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '*');
                drawstar(t[i]);
            }
            else
            {
                t[i].y++;
                if (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '-'
                    || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '<'
                    || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '>'
                    || consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '0')
                    //if (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar != ' ' && consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar != '*')
                {
                    hp -= 1;
                    do
                    {
                        t[i].x = rand() % 80;
                        t[i].y = 1;
                    } while (consoleBuffer[t[i].x + (screen_x * t[i].y)].Char.AsciiChar == '*');
                }
                drawstar(t[i]);
            }
            i++;
        }
        if (numEvents != 0)
        {
            //INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
            for (DWORD i = 0; i < numEventsRead; ++i)
            {
                if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
                {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                        play = false;
                    if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
                        color = rand() % 10;
                    //KEYPRESS                                                             
                }
                else if (eventBuffer[i].EventType == MOUSE_EVENT)
                {
                    int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
                    int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                    if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        //LEFTCLICK                
                    }
                    else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
                    {
                        //RIGHTCLICK
                    }
                    else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
                    {
                        if (posx >= 0 && posx <= 79 && posy >= 0 && posy <= 24)
                        {
                            eraseship(destine);
                            destine.x = posx;
                            destine.y = posy;
                        }
                    }
                }
            }
            //delete [] eventBuffer;
        }
        Sleep(70);
    }
    return 0;
}