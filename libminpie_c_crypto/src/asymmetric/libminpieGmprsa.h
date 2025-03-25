#ifndef _libminpieGmprsa_h
#define _libminpieGmprsa_h
/*
libminpieGmprsa.h
- under libminpie_c_crypto/asymmetric/

RSA asymmetric crypto library implemented with GMP.
ver.250325.1
-----
requirement:
- GNU GMP library

*/
// # Start code
// ## include:
#include <gmp.h>


// ## function prototype:
/*
    int libminpie_Gmprsa_PublicKeyGeneration(mpz_t e, mpz_t p, mpz_t q);
    - input: (e, p, q):(mpz_t, mpz_t, mpz_t, mpz_t)
    * e: a (mpz_t) type struct to store the publickey e.
    * p: a (mpz_t) type struct to get p value in modulo n = (p*q)
    * q: a (mpz_t) type struct to get q value in modulo n = (p*q)
    - output: (error code):(unsigned int)
    - do: do RSA PublicKeyGeneration and store the value to e.
    - return: always 0(success)
*/
extern int libminpie_Gmprsa_PublicKeyGeneration(mpz_t e, mpz_t p, mpz_t q);
/*
    int libminpie_Gmprsa_PublicKeyGenerationWithMinValue(mpz_t e, mpz_t p, mpz_t q, mpz_t minval);
    - input: (e, p, q, minval):(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t)
    * e: a (mpz_t) type struct to store the publickey e.
    * p: a (mpz_t) type struct to get p value in modulo n = (p*q)
    * q: a (mpz_t) type struct to get q value in modulo n = (p*q)
    * minval: a (mpz_t) type struct to limit to e that should over than this value.
    - output: (error code):(unsigned int)
    - do: do RSA PublicKeyGeneration and store the value to e.
    - return: always 0(success)
*/
extern int libminpie_Gmprsa_PublicKeyGenerationWithMinValue(mpz_t e, mpz_t p, mpz_t q, mpz_t minval);
/*
    int libminpie_Gmprsa_PrivateKeyGeneration(mpz_t d, mpz_t e, mpz_t p, mpz_t q);
    - input: (e, d, p, q):(mpz_t, mpz_t, mpz_t, mpz_t)
    * d: a (mpz_t) type struct to store the privatekey d.
    * e: a (mpz_t) type struct to get q the publickey e.
    * p: a (mpz_t) type struct to get p value in modulo n = (p*q)
    * q: a (mpz_t) type struct to get q value in modulo n = (p*q)
    - output: (error code):(unsigned int)
    - do: do RSA PrivateKeyGeneration and store the value to d.
    - return: always 0(success)
*/
extern int libminpie_Gmprsa_PrivateKeyGeneration(mpz_t d, mpz_t e, mpz_t p, mpz_t q);
/*
    int libminpie_Gmprsa_RsaEncrypt(mpz_t cipher, mpz_t plain, mpz_t n, mpz_t e);
    - input: (cipher, plain, n, e):(mpz_t, mpz_t, mpz_t, mpz_t)
    * cipher: a (mpz_t) type struct to store the result.
    * plain: a (mpz_t) type struct to encrypt.
    * n: a (mpz_t) type struct that mean modulo n.
    * e: a (mpz_t) type struct that mean publickey e.
    - output: (error code):(unsigned int)
    - do: do RSA Encryption and store the value to cipher.
    - return: always 0(success)
*/
extern int libminpie_Gmprsa_RsaEncrypt(mpz_t cipher, mpz_t plain, mpz_t n, mpz_t e);
/*
    int libminpie_Gmprsa_RsaDecrypt(mpz_t plain, mpz_t cipher, mpz_t n, mpz_t d);
    - input: (plain, cipher, n, d):(mpz_t, mpz_t, mpz_t, mpz_t)
    * plain: a (mpz_t) type struct to store the result.
    * cipher: a (mpz_t) type struct to decrypt.
    * n: a (mpz_t) type struct that mean modulo n.
    * d: a (mpz_t) type struct that mean privatekey d.
    - output: (error code):(unsigned int)
    - do: do RSA Decryption and store the value to plain.
    - return: always 0(success)
*/
extern int libminpie_Gmprsa_RsaDecrypt(mpz_t plain, mpz_t cipher, mpz_t n, mpz_t d);
// # End code
#endif