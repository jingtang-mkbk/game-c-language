#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
  int i, j;
  int x = 5, y = 10;
  int height = 20, velocity = 1;

  while (1)
  {
    x += velocity;
    system("cls");
    for (int i = 0; i < x; i++)
      printf("\n");
    for (int j = 0; j < y; j++)
      printf(" ");
    printf("o");
    printf("\n");

    if (x == height || x == 0)
      velocity = -velocity;
    Sleep(500);
  }

  return 0;
}