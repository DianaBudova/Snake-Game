#include <stdio.h> 
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>

#pragma region Prototype Functions
void Draw();
void Input();
void UpdateSnake();
void UpdateFruit();
#pragma endregion

#pragma region Variables
bool gameRunning = 0;
int boardWidth;
int boardHeight;
int snakeX;
int snakeY;
int fruitX;
int fruitY;
int gameScore = 0;
int tailX[100], tailY[100];
int tailLength;
char snakeDirection;
const short speed = 100;
#pragma endregion

void main()
{
	printf("\tSETTINGS\n");
	printf("Enter width >> ");
	scanf_s("%d", &boardWidth);
	printf("Enter height >> ");
	scanf_s("%d", &boardHeight);
	if (boardWidth < 1 || boardWidth > 100)
	{
		printf("Board width can be from 1 to 100 pixels!");
		return;
	}
	if (boardHeight < 1 || boardHeight > 100)
	{
		printf("Board height can be from 1 to 100 pixels!");
		return;
	}
	system("cls");
	snakeX = boardWidth / 2;
	snakeY = boardHeight / 2;
	fruitX = rand() % boardWidth;
	fruitY = rand() % boardHeight;
	while (!gameRunning)
	{
		system("cls");
		Draw();
		Input();
		UpdateSnake();
		UpdateFruit();
		Sleep(speed);
	}
}

void Draw()
{
	for (int i = 0; i < boardWidth + 2; i++)
		printf("#");
	printf("\n");
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (j == 0)
				printf("#");
			if (i == snakeY && j == snakeX)
				printf("1");
			else if (i == fruitY && j == fruitX)
				printf("*");
			else
			{
				bool flag = false;
				for (int k = 0; k < tailLength; k++)
					if (tailX[k] == j && tailY[k] == i)
					{
						printf("O");
						flag = true;
					}
				if (!flag)
					printf(" ");
			}
			if (j == boardWidth - 1)
				printf("#");
		}
		printf("\n");
	}
	for (int i = 0; i < boardWidth + 2; i++)
		printf("#");
	printf("\n");
	printf("Score: %i", gameScore);
}

void Input()
{
	if (_kbhit())
	{
		char letter = _getch();
		if (letter == 'w' ||
			letter == 'a' ||
			letter == 's' ||
			letter == 'd')
			snakeDirection = letter;
	}
}

void UpdateSnake()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < tailLength; i++)
	{
		tailX[i] = tailX[i] ^ prevX;
		prevX = tailX[i] ^ prevX;
		tailX[i] = tailX[i] ^ prevX;
		tailY[i] = tailY[i] ^ prevY;
		prevY = tailY[i] ^ prevY;
		tailY[i] = tailY[i] ^ prevY;
	}
	if (snakeDirection == 'w')
		snakeY--;
	else if (snakeDirection == 'a')
		snakeX--;
	else if (snakeDirection == 's')
		snakeY++;
	else if (snakeDirection == 'd')
		snakeX++;
	if (snakeX > boardWidth - 1 || snakeX < 0 || snakeY > boardHeight - 1 || snakeY < 0)
		gameRunning = true;
	else
		gameRunning = false;
	if (snakeX >= boardWidth)
		snakeX = 0;
	else if (snakeX < 0)
		snakeX = boardWidth - 1;
	if (snakeY >= boardHeight)
		snakeY = 0;
	else if (snakeY < 0)
		snakeY = boardHeight - 1;
	for (int i = 0; i < tailLength; i++)
		if (tailX[i] == snakeX && tailY[i] == snakeY)
			gameRunning = true;
}

void UpdateFruit()
{
	if (fruitX == snakeX && fruitY == snakeY)
	{
		fruitX = rand() % boardWidth;
		fruitY = rand() % boardHeight;
		gameScore += 10;
		tailLength++;
	}
}