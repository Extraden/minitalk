#include <stdio.h>

int main(void)
{
 int i;
 unsigned char bit;

 i = 7;
 unsigned char byte = 255;
 while (i >= 0)
  {
    bit = byte >> i & 1;
    printf("%d", bit);
    i--;
  }
}
