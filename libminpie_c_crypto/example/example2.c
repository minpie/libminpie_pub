/*
example2.c
- under libminpie_c_crypto/example

an example program to test AES with my own code.
ver.250325.1

compile with like this:
- gcc -o example2 example2.c -L"./../output" -Wl,-rpath="./../output" -l"minpieAes"
- gcc -o example2 example2.c -L"./../output" -Wl,-rpath="./../output" -l"minpiecrypto" -lssl -lcrypto -lgmp
*/
// # Start code
// ## include:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libminpieAes.h"


// ## main()
int main(void){
    unsigned char plain1[16] = {0, };
    unsigned char cipher1[16] = {0, };
    unsigned char key1[16] = {0, };
    

    unsigned char plain2[16] = {0, };
    unsigned char cipher2[16] = {0, };
    unsigned char key2[16] = {0, };

    memset(plain1, 0xaa, 16);
    memset(key1, 0x55, 16);
    memcpy(key2, key1, 16);


    libminpie_Aes_Aes128Encrypt(cipher1, plain1, key1);
    memcpy(cipher2, cipher1, 16);
    libminpie_Aes_Aes128Decrypt(plain2, cipher2, key2);

    printf("========Encrypt==============\n");
    printf("plain1  : ");
    for(int i=0; i<16; i++){
        printf("%02x", plain1[i]);
    }
    printf("\n");

    printf("cipher1 : ");
    for(int i=0; i<16; i++){
        printf("%02x", cipher1[i]);
    }
    printf("\n");

    printf("key1    : ");
    for(int i=0; i<16; i++){
        printf("%02x", key1[i]);
    }
    printf("\n");
    printf("========Decrypt==============\n");
    printf("plain2  : ");
    for(int i=0; i<16; i++){
        printf("%02x", plain2[i]);
    }
    printf("\n");

    printf("cipher2 : ");
    for(int i=0; i<16; i++){
        printf("%02x", cipher2[i]);
    }
    printf("\n");

    printf("key2    : ");
    for(int i=0; i<16; i++){
        printf("%02x", key2[i]);
    }
    printf("\n");
    printf("========End==============\n");

    return 0;
}
// # End code