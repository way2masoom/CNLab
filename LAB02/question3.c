#include <stdio.h>
#include <stdint.h>

int main() {
    // Declare the number and the character variables to store each byte
    uint32_t number;
    unsigned char byte1, byte2, byte3, byte4;

    // Prompt the user to enter a number
    printf("Enter a number: ");
    scanf("%u", &number);

    // Extract each byte from the number
    byte1 = (number & 0xFF);           // Extract the first byte
    byte2 = (number >> 8) & 0xFF;      // Extract the second byte
    byte3 = (number >> 16) & 0xFF;     // Extract the third byte
    byte4 = (number >> 24) & 0xFF;     // Extract the fourth byte

    // Print the content of each byte
    printf("Byte 1: %u\n", byte1);
    printf("Byte 2: %u\n", byte2);
    printf("Byte 3: %u\n", byte3);
    printf("Byte 4: %u\n", byte4);

    return 0;
}
