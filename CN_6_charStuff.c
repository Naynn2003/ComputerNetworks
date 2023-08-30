#include <stdio.h>
#include <string.h>

#define MAX_DATA_SIZE 100

// Define flag character used for framing
#define FLAG 0x7E

// Function to frame data with flag characters
void frameData(char *data, int dataSize, char *framedData, int *framedDataSize)
{
   int i, j;
   *framedDataSize = 0;

   // Add opening flag character to framed data
   framedData[(*framedDataSize)++] = FLAG;

   // Add data to framed data
   for (i = 0; i < dataSize; i++)
   {
      // If the data byte is equal to the flag character, stuff it with an escape character
      if (data[i] == FLAG)
      {
         framedData[(*framedDataSize)++] = 0x7D;           // Escape character
         framedData[(*framedDataSize)++] = data[i] ^ 0x20; // XOR with 0x20
      }
      // If the data byte is equal to the escape character, stuff it with another escape character
      else if (data[i] == 0x7D)
      {
         framedData[(*framedDataSize)++] = 0x7D;           // Escape character
         framedData[(*framedDataSize)++] = data[i] ^ 0x20; // XOR with 0x20
      }
      // Otherwise, add the data byte to framed data as-is
      else
      {
         framedData[(*framedDataSize)++] = data[i];
      }
   }

   // Add closing flag character to framed data
   framedData[(*framedDataSize)++] = FLAG;
}

// Function to unframe data and remove stuffing
void unframeData(char *framedData, int framedDataSize, char *unframedData, int *unframedDataSize)
{
   int i, j;
   *unframedDataSize = 0;

   // Process data between opening and closing flag characters
   for (i = 0; i < framedDataSize; i++)
   {
      // If the current byte is an escape character
      if (framedData[i] == 0x7D)
      {
         // XOR the next byte with 0x20 to remove stuffing
         unframedData[(*unframedDataSize)++] = framedData[i + 1] ^ 0x20;
         i++; // Skip the escape character
      }
      // Otherwise, add the byte to unframed data
      else
      {
         unframedData[(*unframedDataSize)++] = framedData[i];
      }
   }

   // Null-terminate the unframed data
   unframedData[*unframedDataSize] = '\0';
}

int main()
{
   char framedData[MAX_DATA_SIZE * 2]; // Allocate space for worst-case framing scenario
   int framedDataSize;

   // Get the framed data as input
   printf("Enter data frame: ");
   fgets(framedData, MAX_DATA_SIZE * 2, stdin);
   framedData[strcspn(framedData, "\n")] = 0; // Remove trailing newline character from input

   framedDataSize = strlen(framedData);

   // Print the framed data
   printf("\n\n\n\n\n");

   printf("Sender Side : \n");
   printf("Framed data: ");
   for (int i = 0; i < framedDataSize; i++)
   {
      printf("%02X ", (unsigned char)framedData[i]);
   }
   printf("\n\n\n\n\n");
   printf("Receiver Side : \n");

   // Create variables for unframed data
   char unframedData[MAX_DATA_SIZE];
   int unframedDataSize;

   // Unframe the data and remove stuffing
   unframeData(framedData, framedDataSize, unframedData, &unframedDataSize);

   // Print the original input from framed data
   printf("Original data: %s\n", unframedData);
   printf("\n\n\n\n\n");

   return 0;
}