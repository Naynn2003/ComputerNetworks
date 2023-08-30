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

// Function to insert parity bits at correct positions
void insertParityBits(int *data, int dataBits, int parityBits)
{
    int i, j, k;
    j = k = 0;

    // Positioning the parity bits
    for (i = 1; i <= dataBits + parityBits; i++)
    {
        if (i == (1 << j))
        {
            j++;
        }
        else
        {
            data[k++] = -1;
        }
    }
}

// Function to calculate the parity bits
void calculateParity(int *data, int dataBits, int parityBits)
{
    int i, j, parity;

    // Calculating the parity bits
    for (i = 0; i < parityBits; i++)
    {
        parity = 0;
        for (j = (1 << i); j <= dataBits + parityBits; j++)
        {
            if (j & (1 << i))
            {
                if (data[j - 1] == 1)
                {
                    parity = !parity;
                }
            }
        }
        data[(1 << i) - 1] = parity;
    }
}

// Function to display the Hamming code
void displayHammingCode(int *data, int dataBits, int parityBits)
{
    printf("Hamming Code: ");
    for (int i = 0; i < dataBits + parityBits; i++)
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

    int *data = (int *)malloc((dataBits + parityBits) * sizeof(int));

    printf("Enter the data bits (one bit at a time):\n");
    for (int i = 0; i < dataBits; i++)
    {
        scanf("%d", &data[i]);
    }

    // Insert the parity bits at correct positions
    insertParityBits(data, dataBits, parityBits);

    // Calculate the parity bits
    calculateParity(data, dataBits, parityBits);

    // Display the Hamming code
    displayHammingCode(data, dataBits, parityBits);

    free(data);

    return 0;
}
