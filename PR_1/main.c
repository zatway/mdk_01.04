#include <stdio.h>
extern int x;
void func1(void);

int y = 20;
int z = 30;

void func2()
{
    printf("func2: y=%d \n", y);
}

void func3()
{
    func1();
    printf("func3: x=%d \t y=%d \n", x, y);
}