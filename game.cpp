#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver, walls;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score, poisonX, poisonY;
int tailX[50], tailY[50];
int nTail;
int sleepTime = 1000;
enum eDirection {STOP=0, LEFT, RIGTH, UP, DOWN};
eDirection dir;
bool ok = false;

void Menu()
{
	int w;
	do
	{
		system("cls");
		cout << "Do walls can kill the snake?\nYes - 1\nNo - 0\n";
		cout << "Write your answer here: ";
		
		cin >> w;
		if (w==0)
		{
			walls = false;
			ok = true;
		}
		else if (w == 1)
		{
			walls = true;
			ok = true;
		}
	} while (!ok);

	ok = false;
	do
	{
		system("cls");
		cout << "Choose your level\nEasy - 1\nMiddle - 2\nHard - 3\n";
		cout << "Write your answer here: ";
		cin >> w;
		switch (w)
		{
		case 1:
			sleepTime = 1000;
			ok = true;
			break;
		case 2:
			sleepTime = 500;
			ok = true;
			break;
		case 3:
			sleepTime = 0;
			ok = true;
			break;
		}
	} while (!ok);
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	poisonX = rand() % width;
	poisonY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");//clear console

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
	
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX) 
				cout << "F";
			else if (i == poisonY && j == poisonX)
				cout << "P";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
						
				if (!print)
					cout << " ";
			}
		}
		cout << endl;

	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Your score:\t" << score << endl;
	Sleep(sleepTime);
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
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGTH;
			break;
		case 'x':
			gameOver = true;
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
	case RIGTH:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (walls)
	{
		if (x<0 || x>width || y<0 || y>height)
			gameOver = true;
	}
	else
	{
		if (x >= width - 1)
			x = 0;
		else if (x < 0)
			x = width - 2;

		if (y >= height)
			y = 0;
		else if (y < 0)
			y = height - 1;
	}

	

	for ( int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		if (score % 3 == 0)
		{
			poisonX = rand() % width;
			poisonY = rand() % height;
		}
	}
	if (x == poisonX && y == poisonY)
		gameOver = true;
}

int main()
{

tryagain:

	Setup();
	Menu();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}

	system("cls");
	cout << "\tGame over\n\tYour score:\t" << score << endl;
	int r;
	ok = false;
	do
	{
		cout << "Do you want restart the game?\nYes - 1\tNo - 0" << endl;
		cin >> r;
		if (r == 1)
			goto tryagain;
		else if (r == 0)
			ok = true;

	} while (!ok);
	
	
	return 0;
}