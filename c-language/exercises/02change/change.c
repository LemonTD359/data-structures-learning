#include <stdio.h>
int main(void)
{
    int price  =  0;
    
    printf("please inter price!\n");

    scanf("%d",&price);
    int change = 100 - price;

    printf("you last:%d\n",change);
    return 0;
}