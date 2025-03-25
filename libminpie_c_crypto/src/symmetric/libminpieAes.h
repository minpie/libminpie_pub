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
/*
    int libminpie_Aes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
    - input: (cipher, plain, key):(unsigned char*, unsigned char*, unsigned char*)
    * cipher: destination pointer.
    * plain: source pointer.
    * key: initial key pointer.
    - output: (error code):(unsigned int)
    - do: do Aes128Encrypt() operation in AES.
    - return: always 0(success)
*/
extern int libminpie_Aes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key);
/*
    int libminpie_Aes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);
    - input: (plain, cipher, key):(unsigned char*, unsigned char*, unsigned char*)
    * plain: destination pointer.
    * cipher: source pointer.
    * key: initial key pointer.
    - output: (error code):(unsigned int)
    - do: do Aes128Decrypt() operation in AES.
    - return: always 0(success)
*/
extern int libminpie_Aes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key);

// # End code
#endif