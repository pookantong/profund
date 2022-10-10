#include <stdio.h>
#include <windows.h>
#include <time.h>

#define scount 20
#define screen_x 80
#define screen_y 25

HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
HANDLE rHnd;
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
int life = 10;
int ran_col = 7;

struct star
{
	int x;
	int y;
};
struct star daw[scount];

struct Ship
{
	int x;
	int y;
};
struct Ship ship;

int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}

void clear_buffer() 
{
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 0;
		}
	}
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
		&windowSize);
}

void init_star()
{
	for (int i = 0; i < scount; i++)
	{
		daw[i].x = rand() % screen_x;
		daw[i].y = rand() % screen_y;
		for(int j = 0; j < i; j++)
		{
			if (daw[i].x == daw[j].x&& daw[i].y == daw[j].y)
			{
				i--;
			}
		}
	}
}

void star_fall()
{
	int i;
	for (i = 0; i < scount; i++) {
		if (daw[i].y >= screen_y - 1) {
			daw[i] = { (rand() % screen_x),1 };
		}
		else {
			daw[i] = { daw[i].x,daw[i].y + 1 };
		}
	}
}

void fill_star_to_buffer()
{
	for (int i = 0; i < scount; i++) {
		consoleBuffer[daw[i].x + screen_x * daw[i].y].Char.AsciiChar = '*';
		consoleBuffer[daw[i].x + screen_x * daw[i].y].Attributes = 7;
	}
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

void draw_ship() {
	consoleBuffer[ship.x + screen_x * ship.y].Char.AsciiChar = '<';
	consoleBuffer[ship.x + 1 + screen_x * ship.y].Char.AsciiChar = '-';
	consoleBuffer[ship.x + 2 + screen_x * ship.y].Char.AsciiChar = '0';
	consoleBuffer[ship.x + 3 + screen_x * ship.y].Char.AsciiChar = '-';
	consoleBuffer[ship.x + 4 + screen_x * ship.y].Char.AsciiChar = '>';
	consoleBuffer[ship.x + screen_x * ship.y].Attributes = ran_col;
	consoleBuffer[ship.x + 1 + screen_x * ship.y].Attributes = ran_col;
	consoleBuffer[ship.x + 2 + screen_x * ship.y].Attributes = ran_col;
	consoleBuffer[ship.x + 3 + screen_x * ship.y].Attributes = ran_col;
	consoleBuffer[ship.x + 4 + screen_x * ship.y].Attributes = ran_col;
}

void collision()
{
	for (int i = 0; i < scount; i++)
	{
		for (int j = 0; j < 5; j++)
			if (daw[i].x == ship.x + j && daw[i].y == ship.y)
			{
				daw[i] = { (rand() % screen_x),1 };
				life--;
				break;
			}
	}
}

int main()
{
	bool play = TRUE;
	char ch = ' ';
	srand(time(NULL));
	setConsole(screen_x, screen_y);
	init_star();
	setMode();
	while(play)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) 
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) 
			{
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) 
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) 
					{
						play = false;
					}
					if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
					{
						ran_col = rand() % 255;
					}
					
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) 
					{
						ran_col = rand() % 255;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED && posx>2 && posx < screen_x-2)
					{
						ship.x = posx-2;
						ship.y = posy;
					}
				}
			}
			delete[] eventBuffer;
		}
		star_fall();
		clear_buffer();
		collision();
		draw_ship();
		fill_star_to_buffer();
		fill_buffer_to_console();
		if (life == 0)
		{
			clear_buffer();
			fill_buffer_to_console();
			play = false;
		}
		Sleep(100);
	}
	return 0;
}
