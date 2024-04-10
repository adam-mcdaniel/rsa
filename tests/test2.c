#include "rsa.h"
#include <stdio.h>
#include <assert.h>

int main() {
    bigint p1 = bigint_from_string("61");
    bigint p2 = bigint_from_string("53");
    bigint n, t, e, d;

    generate_key_pair(p1, p2, &n, &t, &e, &d);

    assert(bigint_eq(n, bigint_from_string("3233")));
    assert(bigint_eq(t, bigint_from_string("780")));
    assert(bigint_eq(e, bigint_from_string("17")));
    assert(bigint_eq(d, bigint_from_string("413")));

    // Encrypt the message
    char *message = "Hello, Test Two!";
    printf("Message (text):   ");
    for (int i = 0; i < strlen(message); i++) {
        printf("%c", message[i]);
    }
    printf("\n");

    printf("Message:          ");
    for (int i = 0; i < strlen(message); i++) {
        bigint n = bigint_from_int(message[i]);
        bigint_print(n);
        printf(" ");
        bigint_delete(n);
    }
    printf("\n");


    printf("Encrypted (text): ");
    bigint *encrypted = encrypt_text(message, e, n);
    for (int i = 0; i < strlen(message); i++) {
        printf("%c", (char)bigint_to_int(encrypted[i]));
    }
    printf("\n");
    printf("Encrypted:        ");
    for (int i = 0; i < strlen(message); i++) {
        bigint_print(encrypted[i]);
        printf(" ");
    }
    printf("\n");


    // Decrypt the message
    printf("Decrypted (text): ");
    char *decrypted = decrypt_text(encrypted, strlen(message), d, n);
    printf("%s\n", decrypted);
    printf("Decrypted:        ");
    for (int i = 0; i < strlen(message); i++) {
        bigint n = bigint_from_int(decrypted[i]);
        bigint_print(n);
        printf(" ");
        bigint_delete(n);
    }
    printf("\n");

    assert(strcmp(decrypted, message) == 0);
    
    printf("All tests passed!\n");
    return 0;
}