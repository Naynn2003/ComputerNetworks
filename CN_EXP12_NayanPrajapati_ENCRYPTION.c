// normal encryption
#include <stdio.h>
#include <string.h>

int main() {
    char message[100];
    char key;
    int i, length;

    printf("Enter a message to encrypt: ");
    gets(message);

    printf("Enter a key: ");
    scanf("%c", &key);

    length = strlen(message);

    for (i = 0; i < length; i++) {
        message[i] = message[i] ^ key;
    }

    printf("\nEncrypted message: %s", message);

    return 0;
}

