#include "rsa.h"
#include <stdio.h>
#include <assert.h>

int main() {


    bigint p1 = bigint_from_string("61");
    bigint p2 = bigint_from_string("53");

    // Calculate the modulus
    bigint n = bigint_mul(p1, p2);
    printf("p * q: ");
    bigint_print(n);
    printf("\n");

    assert(bigint_eq(n, bigint_from_string("3233")));

    // Calculate the totient
    bigint t = totient(p1, p2);
    printf("Totient: ");
    bigint_print(t);
    printf("\n");

    assert(bigint_eq(t, bigint_from_string("780")));

    // Choose an E value that is relatively prime to (p1 - 1)(p2 - 1)
    // Choose the largest prime less than 65537
    bigint e = bigint_from_int(65537);
    if (!bigint_lt(e, t))
        e = bigint_from_int(17);
    if (!bigint_lt(e, t))
        e = bigint_from_int(5);
    if (!bigint_lt(e, t))
        e = bigint_from_int(3);
    if (!bigint_lt(e, t))
        e = bigint_from_int(2);


    printf("Public key: ");
    bigint_print(e);
    printf("\n");

    assert(bigint_eq(e, bigint_from_string("17")));

    // Calculate the private key
    bigint d = bigint_modinv(e, t);
    printf("Private key: ");
    bigint_print(d);
    printf("\n");

    assert(bigint_eq(d, bigint_from_string("413")));

    // Encrypt the message
    char *message = "Hello, World!";
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