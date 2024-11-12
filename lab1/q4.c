#include <stdio.h>

struct pkt {
    char c1;
    char c2[2];
    char c3;
};

int main() {
    struct pkt p;
    unsigned int num;
    unsigned char b1, b2, b3, b4;

    printf("Enter a number (0-255): ");
    scanf("%u", &num);

    b1 = (num >> 24) & 0xFF;
    b2 = (num >> 16) & 0xFF;
    b3 = (num >> 8) & 0xFF;
    b4 = num & 0xFF;

    p.c1 = b1;
    p.c2[0] = b2;
    p.c2[1] = b3;
    p.c3 = b4;

    printf("Packet content:\n");
    printf("c1: 0x%02x\n", (unsigned char)p.c1);
    printf("c2[0]: 0x%02x\n", (unsigned char)p.c2[0]);
    printf("c2[1]: 0x%02x\n", (unsigned char)p.c2[1]);
    printf("c3: 0x%02x\n", (unsigned char)p.c3);

    unsigned int r_num = 
        ((unsigned int)p.c1 << 24) |
        ((unsigned int)p.c2[0] << 16) |
        ((unsigned int)p.c2[1] << 8) |
        (unsigned int)p.c3;

    printf("Reconstructed number: %u\n", r_num);

    return 0;
}
