#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int positionX, positionY; // 飞机位置
int bulletX, bulletY;     // 子弹位置
int enemyX, enemyY;       // 敌机位置
int height, width;        // 游戏画面尺寸
int score = 0;            // 得分
int gameOver = 0;         // 游戏结束

void startup()
{
  height = 20;
  width = 30;
  positionX = height / 2;
  positionY = width / 2;
  bulletX = -2;
  bulletY = positionY;
  enemyX = 0;
  enemyY = positionY;
}

// 解决光标闪烁问题
void hideCursor()
{
  CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 清屏
void gotoxy(int x, int y)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle, pos);
}

void show()
{
  gotoxy(0, 0);
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if ((i == positionX) && (j == positionY))
        printf("*");
      else if ((i == enemyX) && (j == enemyY))
        printf("@");
      else if ((i == bulletX) && (j == bulletY))
        printf("|");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("Score: %d\n", score);
}

void updateWithoutInput()
{
  if (bulletX > -1)
    bulletX--;
  if ((bulletX == enemyX) && (bulletY == enemyY))
  {
    score++;
    enemyX = -1;
    enemyY = rand() % width;
    bulletX = -2;
  }
  if (enemyX > height)
  {
    enemyX = -1;
    enemyY = rand() % width;
  }
  if ((positionX == enemyX) && (positionY == enemyY))
    gameOver = 1;

  static int speed = 0;
  if (speed < 10)
    speed++;
  if (speed == 10)
  {
    enemyX++;
    speed = 0;
  }
}

void updateWhitInput()
{
  char input;
  if (kbhit())
  {
    input = getch();
    if (input == 'a' && positionY > 0)
      positionY--;
    if (input == 'd' && positionY < width - 1)
      positionY++;
    if (input == 'w' && positionX > 0)
      positionX--;
    if (input == 's' && positionX < height - 1)
      positionX++;
    if (input == ' ')
    {
      bulletX = positionX - 1;
      bulletY = positionY;
    }
  }
}

int main()
{
  startup();
  hideCursor();

  while (!gameOver)
  {
    show();
    updateWhitInput();
    updateWithoutInput();
  }
  system("cls");
  printf("Game Over, Score: %d\n", score);
  system("pause");

  return 0;
}