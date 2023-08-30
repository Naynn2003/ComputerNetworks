#include <stdio.h>
#include <stdlib.h>

// Function to calculate the number of parity bits required
int calculateParityBits(int dataBits)
{
    int r = 0;
    while ((1 << r) < dataBits + r + 1)
    {
        r++;
    }
    return r;
}

// Function to check for errors and determine the error bit position
int checkForErrors(int *receivedData, int dataBits, int parityBits)
{
    int errorBit = 0;
    int i, j, parity;

    // Check for errors and determine the error bit position
    for (i = 0; i < parityBits; i++)
    {
        parity = 0;
        for (j = (1 << i); j <= dataBits + parityBits; j++)
        {
            if (j & (1 << i))
            {
                if (receivedData[j - 1] == 1)
                {
                    parity = !parity;
                }
            }
        }
        if (receivedData[(1 << i) - 1] != parity)
        {
            errorBit += (1 << i);
        }
    }

    return errorBit;
}

// Function to correct the error bit if errorBit is non-zero
void correctError(int *receivedData, int errorBit)
{
    if (errorBit != 0)
    {
        printf("Error detected at position: %d\n", errorBit);

        // Flip the error bit
        receivedData[errorBit - 1] = !receivedData[errorBit - 1];
    }
    else
    {
        printf("No error detected.\n");
    }
}

// Function to extract the data bits from the received Hamming code
void extractDataBits(int *receivedData, int *data, int dataBits, int parityBits)
{
    int i, j, k;
    j = k = 0;

    // Remove the parity bits and extract the data bits
    for (i = 1; i <= dataBits + parityBits; i++)
    {
        if (i == (1 << j))
        {
            j++;
        }
        else
        {
            data[k++] = receivedData[i - 1];
        }
    }
}

// Function to display the received data bits
void displayReceivedData(int *data, int dataBits)
{
    printf("Received Data: ");
    for (int i = 0; i < dataBits; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main()
{
    int dataBits, parityBits;

    printf("Enter the number of data bits: ");
    scanf("%d", &dataBits);

    // Calculate the number of parity bits required
    parityBits = calculateParityBits(dataBits);

    int *receivedData = (int *)malloc((dataBits + parityBits) * sizeof(int));

    printf("Enter the received Hamming code (one bit at a time):\n");
    for (int i = 0; i < dataBits + parityBits; i++)
    {
        scanf("%d", &receivedData[i]);
    }

    // Check for errors and determine the error bit position
    int errorBit = checkForErrors(receivedData, dataBits, parityBits);

    // Correct the error bit if errorBit is non-zero
    correctError(receivedData, errorBit);

    int *data = (int *)malloc(dataBits * sizeof(int));

    // Extract the data bits from the received Hamming code
    extractDataBits(receivedData, data, dataBits, parityBits);

    // Display the received data bits
    displayReceivedData(data, dataBits);

    free(receivedData);
    free(data);

    return 0;
}
