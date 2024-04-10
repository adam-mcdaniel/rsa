#include "rsa.h"
#include "bigint.h"

int main() {
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