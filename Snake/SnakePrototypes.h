#pragma once

struct TailSnake {//��������� ���������� �� ��������� ������ ������
    int snake_x;
    int snake_y;
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//����������� �������� � ������������ �������� ������

void SnakeSpeed(Direction dir, int width, int height, int& score);//����������� �������� ������ � ����������� �� ����������� ����� 
//��������� �������� ������ � ����� ������ ������ � ������ ���� 
void Setup(int& width, int& height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail);
//������� ���������� ����, ������ �� ���� ������ � ������ 
void Draw(int width, int height, int snake_x, int snake_y, int appleX, int appleY, int score, Direction dir, TailSnake tail[], int lTail);
//������� ���������� �������
void Input(Direction& dir);
//��� ������� �������� �� ������ �������� ������, ����������� ������������ � �������������� � �������
void Logic(int width, int height, int& snake_x, int& snake_y, int& appleX, int& appleY, int& score, Direction& dir, TailSnake tail[], int& lTail, bool& gameOver, bool& withFields);
void StartScreen(int& width, int& height, bool& withFilds);//������� ������ ���� 
void aboutGame(int& screenWidth, int& screenHeight, bool& withFields);//���� � ���� �� ������� ����(�������� ����)
void GameMode(bool& withFields);//����� ������ ����( ��� �����\� ������)
void SetConsoleSize();//������� �������� �� ����������� ������� ����������� ���� 
void HideCursor();//������� ���������� �� ������� ����������� ������� � ������� 
