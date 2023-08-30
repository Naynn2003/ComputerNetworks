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
    uint8_t receivedData[100]; // Array to store received data and CRC
    int length;

    printf("Enter the received data (including CRC): ");
    scanf("%s", receivedData);

    // Calculate the length of the received data
    length = 0;
    while (receivedData[length] != '\0') {
        length++;
    }

    // Separate the received data and CRC
    uint8_t receivedCRC[2];
    receivedCRC[0] = receivedData[length - 2]; // Extract the first CRC byte
    receivedCRC[1] = receivedData[length - 1]; // Extract the second CRC byte

    // Calculate the length of the received data (excluding the CRC)
    int dataLength = length - 2;

    // Compute CRC for the received data
    uint16_t computedCRC = computeCRC(receivedData, dataLength);

    // Combine the received CRC bytes into a single uint16_t value
    uint16_t receivedCRCValue = (receivedCRC[0] << 8) | receivedCRC[1];

    // Validate the received CRC
    if (computedCRC == receivedCRCValue) {
        printf("Data integrity verified. No errors detected.\n");

        // Process the received data further if needed
        // ...
    } else {
        printf("Data integrity check failed. Errors detected.\n");

        // Request retransmission
        printf("Retransmit the data.\n");
    }

    return 0;
}
