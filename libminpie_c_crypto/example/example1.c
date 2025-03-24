/*
example1.c
- under libminpie_c_template/example

an example of making C library in ubuntu+gcc.
ver.250324.1

compile with like this:
- gcc -o example1 example1.c -L"./../output" -Wl,-rpath="./../output" -l"minpieSslaes" -lssl -lcrypto
*/
// # Start code
// ## include:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libminpieSslaes.h"


// ## main()
int main(void){
    unsigned char plain1[16] = {0, };
    unsigned char cipher1[16] = {0, };
    unsigned char key1[32] = {0, };
    

    unsigned char plain2[16] = {0, };
    unsigned char cipher2[16] = {0, };
    unsigned char key2[32] = {0, };

    memset(plain1, 0xaa, 16);
    memset(key1, 0x55, 32);
    memcpy(key2, key1, 32);


    libminpie_Sslaes_Aes256Encrypt(cipher1, plain1, key1);
    memcpy(cipher2, cipher1, 16);
    libminpie_Sslaes_Aes256Decrypt(plain2, cipher2, key2);

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
    for(int i=0; i<32; i++){
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
    for(int i=0; i<32; i++){
        printf("%02x", key2[i]);
    }
    printf("\n");
    printf("========End==============\n");

    return 0;
}
// # End code