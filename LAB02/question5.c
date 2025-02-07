#include <stdio.h>
#include <stdint.h>

// Function to check the endianness of the machine
void check_endianness() {
    unsigned int test = 1;
    char *byte = (char *)&test;

    if (byte[0] == 1) {
        printf("The machine is Little Endian.\n");
    } else {
        printf("The machine is Big Endian.\n");
    }
}

// Function to print the content of each byte of a number
void print_bytes(uint32_t number) {
    unsigned char *byte = (unsigned char *)&number;
    printf("Byte content: ");
    for (int i = 0; i < sizeof(uint32_t); i++) {
        printf("%02X ", byte[i]);
    }
    printf("\n");
}

// Function to convert the endianness of a number
uint32_t convert_endianness(uint32_t number) {
    uint32_t b0, b1, b2, b3;
    b0 = (number & 0x000000FF) << 24;
    b1 = (number & 0x0000FF00) << 8;
    b2 = (number & 0x00FF0000) >> 8;
    b3 = (number & 0xFF000000) >> 24;
    return (b0 | b1 | b2 | b3);
}

int main() {
    // Check the endianness of the host machine
    check_endianness();

    // Enter a number
    uint32_t number;
    printf("Enter a number: ");
    scanf("%u", &number);

    // Print the content of each byte of the number
    printf("Original number in hex: %08X\n", number);
    printf("Original number in bytes:\n");
    print_bytes(number);

    // Convert the endianness of the number
    uint32_t converted_number = convert_endianness(number);
    printf("Converted number in hex: %08X\n", converted_number);
    printf("Converted number in bytes:\n");
    print_bytes(converted_number);

    return 0;
}
