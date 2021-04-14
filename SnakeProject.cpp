//Snake Game Project
//By Sara Murray, Cynthia Gonzalez, Harith Ilangachcharige, and Qumber Zaidi
/*
Change it to lose if wall is touched {done}
Change color of snake {done}
Record length of snake{done}
High score{}
Display "Game Over" (clear system, display instead, ?Change font?){done}
Intro(Press x to start){done}
*/
#include <iostream>
#include <conio.h>
#include <windows.h>
#include<stdlib.h>
using namespace std;
bool gameOver = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int snakeLength = 1;
int highScore = 0;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN, END };
eDirecton dir;
void Setup()
{
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	snakeLength = 1;
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++) {

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

				cout << "*";
			}
			if (i == y && j == x) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);


				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "*";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "*";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			dir = END;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case END:
		gameOver = true;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	if (x >= width) 
		gameOver = true; else if (x < 0) x = width - 1;
	if (y >= height)
		gameOver = true; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		snakeLength++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
void endGame()
{
	system("cls");
	int i = 0;
	for (i; i < 100; i++)
	{
		cout << "Game Over! Game Over! Game Over! Game Over! Game Over! Game Over! Game Over! Game Over! Game Over! Game Over!" << endl;
	}
	if (highScore < score)
		highScore = score;
	cout << "Score: " << score << endl;
	cout << "High Score: " << highScore << endl;
	cout << "Snake Length: " << snakeLength << endl;
	for (int i = 1; i < nTail; i++) {
		tailX[i] = -1;
		tailY[i] = -1;
	}
	nTail = 0;
}
int main()
{
	bool playAgain = true;
	int again;
	char start;
	while (playAgain == true)
	{
		cout << "Welcome to Snake Game! Press x to start." << endl;
		cin >> start;
		if (start != 'x')
		{
			gameOver = true;
		}
		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
			//Sleep(10); //sleep(10);
		}
		endGame();
		do
		{
			cout << "Would you like to play again? (Enter 0 for no, 1 for yes)" << endl;
			cin >> again;
			if (again != 0 && again != 1)
			{
				cout << "Invalid input. ";
			}
			else if (again == 0)
			{
				playAgain = false;
			}
			else
			{
				gameOver = false;

			}
		} while (again != 0 && again != 1);
	}
	return 0;
}