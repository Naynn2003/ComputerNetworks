// Decryption
#include <stdio.h>
#include <string.h>

int main() {
    char message[100];
    char key;
    int i, length;

    printf("Enter an encrypted message: ");
    gets(message);

    printf("Enter the key used to encrypt the message: ");
    scanf("%c", &key);

    length = strlen(message);

    for (i = 0; i < length; i++) {
        message[i] = message[i] ^ key;
    }

    printf("\nDecrypted message: %s", message);

    return 0;
}

