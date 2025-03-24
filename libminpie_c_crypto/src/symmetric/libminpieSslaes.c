/*
libminpieSslaes.c
- under libminpie_c_crypto/symmetric/

AES(Advanced Encryption Standard) library implemented with openssl.
ver.250324.1
-----
requirement:
- OpenSSL library

*/
// # Start code
// ## include:
#include "libminpieSslaes.h"


// ## function:
int libminpie_Sslaes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key){
    // ## AES-128 한블럭 암호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 암호화 처리:
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_EncryptUpdate(ctx, cipher, &blockSize, plain, blockSize);
    EVP_EncryptFinal_ex(ctx, cipher, &blockSize);

    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
int libminpie_Sslaes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key){
    // AES-128 한블럭 복호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 복호화 처리:
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_DecryptUpdate(ctx, plain, &blockSize, cipher, blockSize);
    EVP_DecryptFinal_ex(ctx, plain, &blockSize);
    
    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
int libminpie_Sslaes_Aes192Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key){
    // ## AES-192 한블럭 암호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 암호화 처리:
    EVP_EncryptInit_ex(ctx, EVP_aes_192_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_EncryptUpdate(ctx, cipher, &blockSize, plain, blockSize);
    EVP_EncryptFinal_ex(ctx, cipher, &blockSize);

    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
int libminpie_Sslaes_Aes192Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key){
    // AES-192 한블럭 복호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 복호화 처리:
    EVP_DecryptInit_ex(ctx, EVP_aes_192_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_DecryptUpdate(ctx, plain, &blockSize, cipher, blockSize);
    EVP_DecryptFinal_ex(ctx, plain, &blockSize);
    
    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
int libminpie_Sslaes_Aes256Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key){
    // ## AES-256 한블럭 암호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 암호화 처리:
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_EncryptUpdate(ctx, cipher, &blockSize, plain, blockSize);
    EVP_EncryptFinal_ex(ctx, cipher, &blockSize);

    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
int libminpie_Sslaes_Aes256Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key){
    // AES-256 한블럭 복호화 함수.
    // # 변수 선언:
    EVP_CIPHER_CTX *ctx;
    int blockSize = 16;

    // # 처리:
    ctx = EVP_CIPHER_CTX_new();

    // 예외처리:
    if(!ctx){
        return 1;
    }

    // # 복호화 처리:
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_DecryptUpdate(ctx, plain, &blockSize, cipher, blockSize);
    EVP_DecryptFinal_ex(ctx, plain, &blockSize);
    
    // # 종료 처리:
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
// # End code