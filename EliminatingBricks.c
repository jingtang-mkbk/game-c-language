#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int height, width;        // 游戏画面大小
int ballX, ballY;         // 小球的坐标
int ballVx, ballVy;       // 小球的速度
int positionX, positionY; // 挡板的中心坐标
int radius;               // 挡板的半径
int left, right;          // 挡板的左右位置
int ballNumber;           // 反弹小球的次数
int blockX, blockY;       // 砖块的位置
int score;                // 消除砖块的个数

// 清屏
void gotoxy(int x, int y)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle, pos);
}

// 解决光标闪烁问题
void hideCursor()
{
  CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void startup()
{
  height = 13;
  width = 17;
  ballX = 0;
  ballY = width / 2;
  ballVx = 1;
  ballVy = 1;
  radius = 6;
  positionX = height;
  positionY = width / 2;
  left = positionY - radius;
  right = positionY + radius;
  ballNumber = 0;
  blockX = 0;
  blockY = 9;
  score = 0;
}

void show()
{
  gotoxy(0, 0);
  for (int i = 0; i <= height + 1; i++)
  {
    for (int j = 0; j <= width; j++)
    {
      if ((i == ballX) && (j == ballY))
        printf("0");
      else if (j == width)
        printf("|");
      else if (i == height + 1)
        printf("-");
      else if ((i == height) && (j > left) && j < right)
        printf("*");
      else if ((i == blockX) && (j == blockY))
        printf("B");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("Score: %d\n", score);
  printf("Rebound ball count: %d\n", ballNumber);
}

void updateWithoutInput()
{
  if (ballX == height - 1)
  {
    if ((ballY >= left) && (ballY <= right))
    {
      ballNumber++;
      // printf("\a");
    }
    else
    {
      printf("Game Over\n");
      system("pause");
      exit(0);
    }
  }
  if ((ballX == blockX) && (ballY == blockY))
  {
    score++;
    blockY = rand() % width;
  }

  ballX += ballVx;
  ballY += ballVy;

  if ((ballX == 0) || (ballX == height - 1))
    ballVx = -ballVx;
  if ((ballY == 0) || (ballY == width - 1))
    ballVy = -ballVy;
  Sleep(50);
}

void updateWithInput()
{
  char input;
  if (kbhit())
  {
    input = getch();
    if (input == 'a')
    {
      positionY--;
      left = positionY - radius;
      right = positionY + radius;
    }
    else if (input == 'd')
    {
      positionY++;
      left = positionY - radius;
      right = positionY + radius;
    }
  }
}

int main()
{
  startup();
  hideCursor();

  while (1)
  {
    show();
    updateWithInput();
    updateWithoutInput();
  }

  return 0;
}