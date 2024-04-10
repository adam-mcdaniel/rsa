#include "rsa.h"
#include <stdio.h>
#include <assert.h>

void test1();
void test2();

int main() {
    test1();
    test2();
    printf("Tests passed\n");
    return 0;
}

void test1() {
    bigint p1 = bigint_from_string("61");
    bigint p2 = bigint_from_string("53");
    bigint n, t, e, d;

    generate_key_pair(p1, p2, &n, &t, &e, &d);
    printf("Public key: ");
    bigint_print(e);

    printf("\nPrivate key: ");
    bigint_print(d);
    printf("\n");
}

void test2() {
    bigint p1 = bigint_from_string("61");
    bigint p2 = bigint_from_string("53");
    bigint n, t, e, d;

    generate_key_pair(p1, p2, &n, &t, &e, &d);
    printf("Public key: ");
    bigint_print(e);

    printf("\nPrivate key: ");
    bigint_print(d);

    char message[] = "Hello, world!";
    bigint *encrypted = encrypt_text(message, e, n);
    char *decrypted = decrypt_text(encrypted, strlen(message), d, n);

    printf("\nEncrypted: ");
    for (int i = 0; i < strlen(message); i++) {
        bigint_print(encrypted[i]);
        printf(" ");
    }

    printf("\nDecrypted: %s\n", decrypted);

}