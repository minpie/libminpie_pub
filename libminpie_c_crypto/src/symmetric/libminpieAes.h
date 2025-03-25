#ifndef _libminpieAes_h
#define _libminpieAes_h
/*
libminpieAes.h
- under libminpie_c_crypto/symmetric/

AES(Advanced Encryption Standard) library implemented with my own code.
ver.250325.1
-----
requirement:
- (NO REQUIREMENTS)

*/
// # Start code
// ## include:


// ## function prototype:
extern int libminpie_Aes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
extern int libminpie_Aes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);

// # End code
#endif