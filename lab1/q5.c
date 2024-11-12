#include <stdio.h>
#include <stdint.h>

u_int32_t reverse(u_int32_t value) {
    u_int32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

int main() {
    int a = 1;
    printf("%p\n\n", &a);

    char* ptr = (char*) &a;
    char byte = *ptr;

    printf("%d\n", byte);
    printf("%p\n", ptr);

    if (byte == 0) {
        printf("BIG ENDIAN\n");
    } else {
        printf("LITTLE ENDIAN\n");
    }

    u_int32_t value = 0x12345678;
    printf("Original: 0x%x\n", value);
    u_int32_t reversedValue = reverse(value);
    printf("Reversed: 0x%x\n", reversedValue);

    return 0;
}
