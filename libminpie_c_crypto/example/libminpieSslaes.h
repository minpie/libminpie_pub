#ifndef _libminpieSslaes_h
#define _libminpieSslaes_h
/*
libminpieSslaes.h
- under libminpie_c_crypto/symmetric/

AES(Advanced Encryption Standard) library implemented with openssl.
ver.250324.1
-----
requirement:
- OpenSSL library

*/
// # Start code
// ## include:
#include <openssl/evp.h>


// ## function prototype:
extern int libminpie_Sslaes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
extern int libminpie_Sslaes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);
extern int libminpie_Sslaes_Aes192Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
extern int libminpie_Sslaes_Aes192Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);
extern int libminpie_Sslaes_Aes256Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
extern int libminpie_Sslaes_Aes256Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);


// # End code
#endif