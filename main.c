#include <conio.h>
#include <windows.h>
#include <stdio.h>

void limit_FPS(int FPS);
void setup(); // Устанавливает все необходимые настройки
void print_game(); // Отображание всей игры
void event_handler(int* pl_x, int* pl_y); // Обработчик сообытий меняет координаты игрока 
int pl_x = 1, pl_y = 1;

int main (void)
{
    setup();
    while(1)
    {
        event_handler(&pl_x,&pl_y);
        print_game();
        limit_FPS(10);
    }
}

void setup(void)
{
    // Делаем курсор невидимым
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Получаем информацию о курсоре
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Устанавливаем размер курсора в 1 (невидимый курсор)
    cursorInfo.bVisible = FALSE;

    // Устанавливаем новую информацию о курсоре
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void print_green(int c);

void print_pl(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {pl_x, pl_y}; // Новая позиция курсора

    SetConsoleCursorPosition(hConsole, position);
    print_green('O');

    position.X = 0;
    position.Y = 0;

    SetConsoleCursorPosition(hConsole, position);

}

void print_game()
{
    print_pl();
}

void event_handler(int* pl_x, int* pl_y)
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'w':
                (*pl_y)--;
                break;
            case 'a':
                (*pl_x)--;
                break;
            case 's':
                (*pl_y)++;
                break;
            case 'd':
                (*pl_x)++;
                break;
        }
    }
}

void limit_FPS(int FPS_LIMIT) {
    static DWORD prevTime = 0;
    DWORD currentTime = GetTickCount();
    DWORD elapsedTime = currentTime - prevTime;
    DWORD frameTime = 1000 / FPS_LIMIT;

    if (elapsedTime < frameTime) {
        Sleep(frameTime - elapsedTime);
    }

    prevTime = GetTickCount();
}


void print_green(int c)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;

    GetConsoleScreenBufferInfo(console, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    
    putchar(c);

    SetConsoleTextAttribute(console, savedAttributes);
}