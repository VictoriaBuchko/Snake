#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "SnakePrototypes.h"
using namespace std;


int main()
{
    //Опредиление основных параметров 
    int width, height, snake_x, snake_y, appleX, appleY, score;
    Direction dir;
    TailSnake tail[1000];
    int lTail, speed = 0;
    bool gameOver = false;
    bool withFields = false;


    SetConsoleSize();//Вызов функции отвечающую за размер консоли 
    StartScreen(width, height, withFields);//Вызов меню 
    Setup(width, height, snake_x, snake_y, appleX, appleY, score, dir, tail, lTail);//Определение дополнительных параметров игры( яблоко и голова змейки)

    while (!gameOver)//Цикл отвечающий за работу программы до тех пор пока не будет выполнен один из пунктов проигрыша 
    {
        HideCursor();                                                                                         //прячем курсор 
        Draw(width, height, snake_x, snake_y, appleX, appleY, score, dir, tail, lTail);                       //прорисовка всего на поле 
        SnakeSpeed(dir, width, height, score);                                                                 //скорость змейки 
        Input(dir);                                                                                           //определение напровления змейки
        Logic(width, height, snake_x, snake_y, appleX, appleY, score, dir, tail, lTail, gameOver, withFields);//механизм роботы змейки
        Sleep(speed);                                                                                         //задержка
    }

    return 0;
}

//Функция скрытия консоли 
void HideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}


//Функция  определяющая размер консоли 
void SetConsoleSize() {
    system("mode con cols=51 lines=31");
    MoveWindow(GetConsoleWindow(), 50, 50, 650, 470, true);
}


//Функция определяющаяя спорость змейки 
void SnakeSpeed(Direction dir, int width, int height, int& score)
{
    if (score <= 3)//при счете 3 очка
    {
        if (dir == LEFT || dir == RIGHT)
            Sleep(60);
        if (dir == UP || dir == DOWN)
            Sleep(70);
    }
    else if (score > 3 && score <= 6)//при счете от 3-6 очков 
    {
        if (dir == LEFT || dir == RIGHT)
            Sleep(50);
        if (dir == UP || dir == DOWN)
            Sleep(70);
    }
    else if (score >= 7)//при счете от 7 очков 
    {
        if (dir == LEFT || dir == RIGHT)
            Sleep(40);
        if (dir == UP || dir == DOWN)
            Sleep(70);
    }

}


//Функция генерирующая яблоко и определяющая размещение гооловы змейки в начале игры 
void Setup(int& width, int& height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail)
{
    srand(time(NULL));
    snake_x = width / 2;      //кординаты головы змейки 
    snake_y = height / 2;     //кординаты головы змейки 
    appleX = rand() % width;  //кординаты яблока
    appleY = rand() % height; //кординаты яблока
    score = 0;                //счетчик количество очков
    dir = STOP;               //в начале змейка стоит 
    lTail = 0;                //в начале игры длинна хвоста змейки 
}

//Вывод поля, змейки, яблока в консоль 
void Draw(int width, int height, int snake_x, int snake_y, int appleX, int appleY, int score, Direction dir, TailSnake tail[], int lTail)
{
    system("cls");//Очищение консоли 

    for (int i = 0; i < width + 2; i++)//Вывод верхней границы поля 
        cout << (char)196;             //работа с юникодом для вывода значка
    cout << "      Score: " << score;  //Вывод количества очков 
    cout << endl;

    for (int i = 0; i < height; i++)    //внешний цикл отвечающий за вывод 
    {
        for (int j = 0; j < width; j++) //внутрений цикл отвечающий за вывод 
        {
            if (j == 0)                 //вывод боковой стороны поля 
                cout << (char)179;

            if (i == snake_y && j == snake_x)//Вывод головы змейки + использование окраса(ескейп последовательность)
                cout << "\x1b[33mO\x1b[0m";
            else if (i == appleY && j == appleX)//Вывод яблока + использование окраса(ескейп последовательность)
                cout << "\x1b[31m*\x1b[0m";
            else
            {
                bool print = false;
                for (int k = 0; k < lTail; k++)//проверка на длину змейки 
                {
                    if (tail[k].snake_x == j && tail[k].snake_y == i)//Вывод хвоста змейки + использование окраса(ескейп последовательность)
                    {
                        // Используйте разные цвета для разных позиций хвоста
                        int tailColor = (k % 6) + 91;  // 91-96 - коды цветов для текста (ANSI Escape Codes)
                        cout << "\x1b[" << tailColor << "mo\x1b[0m";
                        print = true;
                    }
                }

                if (!print)
                    cout << ' ';
            }

            if (j == width - 1) //вывод боковой стороны поля 
                cout << (char)179;
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//вывод нижней границы поля 
        cout << (char)196;
}

//Функция считывающая нажатие клавиш( определение направление змейки)
void Input(Direction& dir)
{
    if (_kbhit())
    {
        char keyPressed = _getch();//записываем в переменную результаты нажатия клавиши

        switch (keyPressed)
        {
        case 'a':
        case 'A':
        case 75:
            if (dir != RIGHT)  //Проверка, чтобы не двигаться влево, если уже идет вправо
                dir = LEFT;
            break;
        case 'd':
        case 'D':
        case 77:
            if (dir != LEFT)  //Проверка, чтобы не двигаться вправо, если уже идет влево
                dir = RIGHT;
            break;
        case 'W':
        case 'w':
        case 72:
            if (dir != DOWN)  //Проверка, чтобы не двигаться вверх, если уже идет вниз
                dir = UP;
            break;
        case 's':
        case 'S':
        case 80:
            if (dir != UP)  //Проверка, чтобы не двигаться вниз, если уже идет вверх
                dir = DOWN;
            break;
        }
    }
}

//Эта функция отвечает за логику движения змейки, обнаружение столкновений и взаимодействие с яблоком
void Logic(int width, int height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail, bool& gameOver, bool& withFields) {

    //сохраняем предыдущую позицию головы змейки в переменной prev
    TailSnake prev = tail[0];
    tail[0] = { snake_x, snake_y };

    //смещаем все элементы хвоста на одну позицию вперед, начиная со второго элемента
    for (int i = 1; i < lTail; i++)
    {
        TailSnake temp = tail[i];
        tail[i] = prev;
        prev = temp;
    }

    //исходя из текущего направления движения, обновляем координаты головы змейки
    switch (dir) {
    case LEFT:
        snake_x--;
        break;
    case RIGHT:
        snake_x++;
        break;
    case UP:
        snake_y--;
        break;
    case DOWN:
        snake_y++;
        break;
    }


    //если игра происходит без полей, проверяем на столкновение с границами игрового поля
    if (withFields == false)
    {
        if (snake_x <= 0 || snake_x >= width || snake_y <= 0 || snake_y >= height)
            gameOver = true;

        //проверка на столкновение с собственным хвостом
        for (int i = 0; i < lTail; i++)
            if (tail[i].snake_x == snake_x && tail[i].snake_y == snake_y)
                gameOver = true;
    }
    else if (withFields == true)//если игра происходит с полями, обрабатываем переход через границы поля
    {
        if (snake_x < 0)
            snake_x = width - 1;
        else if (snake_x >= width)
            snake_x = 0;

        if (snake_y < 0)
            snake_y = height - 1;
        else if (snake_y >= height)
            snake_y = 0;

        //проверка на столкновение с собственным хвостом
        for (int i = 0; i < lTail; i++) {
            if (tail[i].snake_x == snake_x && tail[i].snake_y == snake_y) {
                gameOver = true;
            }
        }
    }

    //если голова змейки достигла позиции яблока, увеличиваем длину хвоста и обновляем счет
    if (snake_x == appleX && snake_y == appleY)
    {
        lTail++;
        score += 1;
        appleX = rand() % width;    //новая генирация яблока
        appleY = rand() % height;   //новая генирация яблока
    }
}

//Вывод меню 
void StartScreen(int& width, int& height, bool& withFields)
{
    int screenWidth = 0, screenHeight = 0;

    bool start = false;

    while (!start)
    {
        system("cls");//Очищение консоли 

        // Вывод заголовка и меню на стартовом экране
        cout << endl;
        cout << "\x1b[32m________________________________________________________________________________\n";
        cout << endl;
        cout << "                            G A M E   M E N U                                  \n";
        cout << "________________________________________________________________________________\x1b[0m\n";
        cout << endl;
        cout << "                               PRESS THE KEY                                   \n";
        cout << endl;
        cout << "                          [1] - START GAME                                 \n";
        cout << endl;
        cout << "                          [2] - ABOUT GAME                                 \n";
        cout << endl;
        cout << "                             [3] - QUIT                                       \n";
        char choice = _getch();//считывание нажатие клавиши 

        switch (choice)
        {
        case '1':         //при выборе 1 пункта меню переходим к выбору режимов игры
            system("cls");//Очищение консоли 
            char size;

            cout << "\x1b[32m________________________________________________________________________________\n";
            cout << endl;
            cout << "                          C H O I C E   S I Z E                                  \n";
            cout << "________________________________________________________________________________\x1b[0m\n";
            cout << endl;
            cout << "                           [1] - SMALL                                   \n";
            cout << endl;
            cout << "                           [2] - MEDIUM                               \n";
            cout << endl;
            cout << "                           [3] - LARGE                                 \n";

            while (true) {//безконечный цикл пока пользователь не введет нужное значение 

                size = _getch();
                if (size == '1' || size == '2' || size == '3') {
                    break;
                }
            }
            switch (size) {//выбор размера поля 
            case '1':      //маленькое 
                width = 40;
                height = 20;
                break;
            case '2':      //срелнее
                width = 50;
                height = 20;
                break;
            case '3':      //большое 
                width = 70;
                height = 20;
                break;
            }

            GameMode(withFields);//запрос про режим игры 
            start = true;
            break;
        case '2'://при выборе 2 пункта меню 
            aboutGame(screenWidth, screenHeight, withFields);
            break;
        case '3':
            exit(0);// при выборе 3 пункта меню ( выход из игры)
        default:
            break;
        }
    }
}

//Выбор режима игры( с полями или без полей)
void GameMode(bool& withFields)
{
    system("cls");//очищение консоли 
    char mode;

    //вывод визуала 
    cout << "\x1b[32m________________________________________________________________________________\n";
    cout << endl;
    cout << "                    C H O I C E   A   G A M E   M O D E                                  \n";
    cout << "________________________________________________________________________________\x1b[0m\n";
    cout << endl;
    cout << "                           [1] - WITH FIELDS                                   \n";
    cout << endl;
    cout << "                         [2] - WITHOUT FIELDS                               \n";
    cout << endl;

    while (true) {//считывание нажатия 

        mode = _getch();
        if (mode == '1' || mode == '2') {
            break;
        }
    }
    switch (mode) {//определение режима игры в зависимости от выбора пользователя 
    case '1':
        withFields = false;//без полей 
        break;
    case '2':
        withFields = true;//с полями
        break;
    }
}

//При выборе 2 пункта меню - Функция расказывает про что игра
void aboutGame(int& screenWidth, int& screenHeight, bool& withFields)
{
    system("cls");//Очистка консоли 
    cout << "\x1b[33m________________________________________________________________________________\n";
    cout << endl;
    cout << "                            A B O U T   G A M E                                  \n";
    cout << "________________________________________________________________________________\x1b[0m\n";
    cout << endl;
    cout << "                            Welcome to 'Snake'!\n";
    cout << "      - At the beginning of the game, the snake consists of one link\n";
    cout << "     - If the snake's head bumps into an obstacle (the snake stumbles on\n";
    cout << "   itself or on the border of the field), the game is lost\n";
    cout << endl;
    cout << "   - At each moment of time, there is food on the playing field, occupying\n";
    cout << "   one cell of the field\n";
    cout << endl;
    cout << "   - When the snake eats fruit, it grows by one link, and a new portion of food\n";
    cout << "   automatically appears in an arbitrary space\n";
    cout << endl;
    cout << "   - When the snake eats fruit, the score is increased by 1 point\n\n";
    cout << endl;
    cout << "               \x1b[33mTO CONTROL THE SNAKE, YOU CAN USE THE KEYS:\x1b[0m\n\n";
    cout << "                        '\x1b[33m^\x1b[0m' or '\x1b[33mW\x1b[0m' to go UP\n";
    cout << "                        '\x1b[33m<\x1b[0m' or '\x1b[33mA\x1b[0m' to go LEFT\n";
    cout << "                        '\x1b[33m>\x1b[0m' or '\x1b[33mD\x1b[0m' to go RIGHT\n";
    cout << "                        '\x1b[33mv\x1b[0m' or '\x1b[33mS\x1b[0m' to go DOWN\n";
    cout << endl;
    cout << "                         PRESS [\x1b[33m0\x1b[0m] TO GO BACK  ";

    char backMenu = '0';
    if (backMenu == _getch())// при нажатии на 0 возврат в меню
    {
        StartScreen(screenWidth, screenHeight, withFields);
    }
}
