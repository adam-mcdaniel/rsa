# rsa

This repository implements the RSA algorithm in C, with arbitarily large integers. The implementation uses [a custom bigint library](https://github.com/adam-mcdaniel/bigint) to handle large key sizes.

The library is header-only, and can be included in any C project.

It has support for generating keys and encrypting/decrypting messages.

## Usage

To use the library, first include it in your C file.

```c
#include "rsa.h"
```

Then, generate a public/private key pair using the `generate_key_pair` function.

```c
int main() {
    bigint p1 = bigint_from_string("61");
    bigint p2 = bigint_from_string("53");
    bigint n, t, e, d;

    generate_key_pair(p1, p2, &n, &t, &e, &d);
    printf("Public key: ");
    bigint_print(e);

    printf("\nPrivate key: ");
    bigint_print(d);

    return 0;
}
```

Then, use the `encrypt_text` and `decrypt_text` functions to encrypt and decrypt messages.

```c
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

    return 0;
}
```

## Building

To build your program with the RSA library, simply add it to your include path, [along with the bigint header file](https://github.com/adam-mcdaniel/bigint), and link against the C standard library.

```bash
gcc -I path/to/rsa -I path/to/bigint main.c -o main
```

### CMake

To build with CMake, you can use a `CMakeLists.txt` file like the following:

```cmake
cmake_minimum_required(VERSION 3.0)

# Create a new project
project(HelloWorld)

# Add an executable
add_executable(HelloWorld main.c)

include_directories(path/to/rsa)
```

Alternatively, you can use `FetchContent` to download the RSA and Bigint repositories and include them in your project.

```cmake
# Import the library from the git repo
include(FetchContent)

FetchContent_Declare(
  rsa
  GIT_REPOSITORY https://github.com/adam-mcdaniel/rsa
  GIT_TAG        main
)

FetchContent_MakeAvailable(rsa)

# Include the header only library
include_directories(${rsa_SOURCE_DIR})

# Do the same for the bigint project
FetchContent_Declare(
  bigint
  GIT_REPOSITORY https://github.com/adam-mcdaniel/bigint
  GIT_TAG        main
)

FetchContent_MakeAvailable(bigint)

# Include the header only library
include_directories(${bigint_SOURCE_DIR})
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.