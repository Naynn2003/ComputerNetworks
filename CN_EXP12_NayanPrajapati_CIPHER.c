// encryption :cipher

#include <stdio.h>
#include <string.h>

void encrypt(char message[], int key) {
    int i;

    for (i = 0; i < strlen(message); i++) {
        message[i] = message[i] + key;
    }
}

void decrypt(char message[], int key) {
    int i;

    for (i = 0; i < strlen(message); i++) {
        message[i] = message[i] - key;
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter a message to encrypt: ");
    gets(message);

    printf("Enter a cipher key (integer): ");
    scanf("%d", &key);

    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    decrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}

