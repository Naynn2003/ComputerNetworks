#include <stdio.h>
#include <stdint.h>

// Function to perform CRC calculation
uint16_t computeCRC(uint8_t data[], int length) {
    uint16_t crc = 0xFFFF; // Initial CRC value
    uint16_t polynomial = 0x1021; // CRC polynomial

    for (int i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8; // XOR with next data byte

        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ polynomial; // Perform polynomial division
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int main() {
    uint8_t data[100]; // Array to store data
    int length;

    printf("Enter the data: ");
    scanf("%s", data);

    // Calculate the length of the input data
    length = 0;
    while (data[length] != '\0') {
        length++;
    }

    // Compute CRC
    uint16_t crc = computeCRC(data, length);

    // Append the CRC to the data
    data[length] = (crc >> 8) & 0xFF;
    data[length + 1] = crc & 0xFF;
    data[length + 2] = '\0';

    // Display the data along with the computed CRC
    printf("Transmitted Data (including CRC): %s\n", data);

    return 0;
}
