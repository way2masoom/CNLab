#include <stdio.h>
#include <stdint.h>

// Define the pkt structure
struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

// Function to print the content of the pkt structure
void print_pkt(struct pkt packet) {
    printf("ch1: %d\n", packet.ch1);
    printf("ch2[0]: %d\n", packet.ch2[0]);
    printf("ch2[1]: %d\n", packet.ch2[1]);
    printf("ch3: %d\n", packet.ch3);
}

// Function to aggregate the members of the pkt structure to form the original number
uint32_t aggregate_pkt(struct pkt packet) {
    uint32_t number = 0;
    number |= (uint32_t)(packet.ch1 & 0xFF);
    number |= (uint32_t)(packet.ch2[0] & 0xFF) << 8;
    number |= (uint32_t)(packet.ch2[1] & 0xFF) << 16;
    number |= (uint32_t)(packet.ch3 & 0xFF) << 24;
    return number;
}

int main() {
    uint32_t number;
    struct pkt packet;

    // Prompt the user to enter a number
    printf("Enter a number: ");
    scanf("%u", &number);

    // Store the number in the pkt structure
    packet.ch1 = (number & 0xFF);
    packet.ch2[0] = (number >> 8) & 0xFF;
    packet.ch2[1] = (number >> 16) & 0xFF;
    packet.ch3 = (number >> 24) & 0xFF;

    // Print the content of each member of the structure
    printf("\nContent of pkt structure:\n");
    print_pkt(packet);

    // Aggregate the members to form the original number and print it
    uint32_t aggregated_number = aggregate_pkt(packet);
    printf("\nAggregated number: %u\n", aggregated_number);

    return 0;
}
