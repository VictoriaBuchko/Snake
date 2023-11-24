#pragma once

struct TailSnake {//—труктура отвечающа€ за кординаты хвоста змейки
    int snake_x;
    int snake_y;
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//ќбъединение св€заное с направлением движени€ змейки

void SnakeSpeed(Direction dir, int width, int height, int& score);//определение скорости змейки в зовисимости от заработаных очков 
//√енираци€ кординат €блока и спаун головы змейки в начале игры 
void Setup(int& width, int& height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail);
//‘ункци€ прорисовки пол€, вывода на поле €блока и змейки 
void Draw(int width, int height, int snake_x, int snake_y, int appleX, int appleY, int score, Direction dir, TailSnake tail[], int lTail);
//‘ункци€ управлени€ змейкой
void Input(Direction& dir);
//Ёта функци€ отвечает за логику движени€ змейки, обнаружение столкновений и взаимодействие с €блоком
void Logic(int width, int height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail, bool& gameOver, bool& withFields);
void StartScreen(int& width, int& height, bool& withFilds);//‘ункци€ вывода меню 
void aboutGame(int& screenWidth, int& screenHeight, bool& withFields);//¬ход в один из пунктов мен€(описание игры)
void GameMode(bool& withFields);//выбор режима игры( без полей\с пол€ми)
void SetConsoleSize();//‘ункци€ отвечает за определение размера консольного окна 
void HideCursor();//‘ункци€ отвечающа€ за скрытие мелькающего курсора в консоли 
