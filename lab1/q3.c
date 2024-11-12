#include <stdio.h>

int main() 
{
    unsigned int num = 0x20785476;

    unsigned char b0 = (num & 0x000000FF);
    unsigned char b1 = (num & 0x0000FF00) >> 8;
    unsigned char b2 = (num & 0x00FF0000) >> 16;
    unsigned char b3 = (num & 0xFF000000) >> 24;

    printf("0x%02x\n", b0);
    printf("0x%02x\n", b1);
    printf("0x%02x\n", b2);
    printf("0x%02x\n", b3);

    return 0;
}
