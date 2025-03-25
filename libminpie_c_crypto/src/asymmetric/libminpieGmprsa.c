/*
libminpieGmprsa.c
- under libminpie_c_crypto/asymmetric/

RSA asymmetric crypto library implemented with GMP.
ver.250325.1
-----
requirement:
- GNU GMP library

*/
// # Start code
// ## include:
#include "libminpieGmprsa.h"


// ## function:
// ### RSA 관련 함수:
int libminpie_Gmprsa_FastModuloExponentiation(mpz_t result, mpz_t a, mpz_t x, mpz_t n){
    /*
    int libminpie_Gmprsa_FastModuloExponentiation(mpz_t result, mpz_t a, mpz_t x, mpz_t n);
    - input: (result, a, x, n):(mpz_t, mpz_t, mpz_t, mpz_t)
    * result: a (mpz_t) type struct to store the result.
    * a: a (mpz_t) type struct to get a value in formula (a^x mod n).
    * x: a (mpz_t) type struct to get x value in formula (a^x mod n).
    * n: a (mpz_t) type struct to get n value in formula (a^x mod n).
    - output: (error code):(unsigned int)
    - do: do (a^x mod n) and store the value to result.
    - return: always 0(success)
    */
    //
    mp_bitcnt_t bits_x, i;
    mpz_t tmp_a, y;
    mpz_inits(tmp_a, y, NULL);
    mpz_set(tmp_a, a);
    mpz_set_ui(y, 1); // y = 1
    i = 0;
    bits_x = mpz_sizeinbase(x, 2);

    while (bits_x > i)
    {
        if (mpz_tstbit(x, i))
        {
            // x의 i번째 비트가 1이면:
            mpz_mul(y, tmp_a, y); // y = tmp_a * y
            mpz_mod(y, y, n);     // y = y mod n
        }
        mpz_mul(tmp_a, tmp_a, tmp_a); // tmp_a = tmp_a * tmp_a
        mpz_mod(tmp_a, tmp_a, n);     // tmp_a = tmp_a mod n
        i = (mp_bitcnt_t)(i + 1);     // i++
    }

    mpz_set(result, y);
    mpz_clears(tmp_a, y, NULL);
    return 0;
}
int libminpie_Gmprsa_GetGcd(mpz_t result, mpz_t a, mpz_t b){
    /*
    int libminpie_Gmprsa_GetGcd(mpz_t result, mpz_t a, mpz_t b);
    - input: (result, a, b):(mpz_t, mpz_t, mpz_t)
    * result: a (mpz_t) type struct to store the result.
    * a: a (mpz_t) type struct to get a value in formula GCD(a, b).
    * b: a (mpz_t) type struct to get b value in formula GCD(a, b).
    - output: (error code):(unsigned int)
    - do: do GCD(a, b) and store the value to result.
    - return: always 0(success)
    */
    // 유클리드 알고리즘 사용
    mpz_t r, r1, r2, q, tmp1;
    mpz_inits(r, r1, r2, q, tmp1, NULL);
    mpz_set(r1, a);
    mpz_set(r2, b);
    while (mpz_cmp_si(r2, 0) > 0)
    {
        mpz_fdiv_q(q, r1, r2); // q = r1 / r2
        mpz_mul(tmp1, q, r2);  // tmp1 = q * r2
        mpz_sub(r, r1, tmp1);  // r = r1 - tmp1 = r1 - (q * r2)
        mpz_set(r1, r2);       // r1 = r2
        mpz_set(r2, r);        // r2 = r
    }

    mpz_set(result, r1); // result = r1
    mpz_clears(r, r1, r2, q, tmp1, NULL);
    return 0;
}
int libminpie_Gmprsa_GetModularMultiplicativeInverse(mpz_t a_1, mpz_t n, mpz_t a){
    /*
    int libminpie_Gmprsa_GetModularMultiplicativeInverse(mpz_t a_1, mpz_t n, mpz_t a);
    - input: (a_1, n, a):(mpz_t, mpz_t, mpz_t)
    * a_1: a (mpz_t) type struct to store the result.
    * n: a (mpz_t) type struct to get n value in formula a_1 = (a^-1 mod n).
    * a: a (mpz_t) type struct to get a value in formula a_1 = (a^-1 mod n).
    - output: (error code):(unsigned int)
    - do: do (a^-1 mod n)  and store the value to a_1.
    - return: always 0(success)
    */
    // 확장 유클리드 알고리즘 사용
    mpz_t q, r1, r2, r, t, t1, t2, tmp1, tmp2;
    mpz_inits(q, r1, r2, r, t, t1, t2, tmp1, tmp2, NULL);
    mpz_set(r1, n);    // r1 = n;
    mpz_set(r2, a);    // r2 = a
    mpz_set_si(t1, 0); // t1 = 0
    mpz_set_si(t2, 1); // t2 = 1

    while (mpz_cmp_si(r2, 0))
    {
        mpz_fdiv_q(q, r1, r2); // q = r1 / r2
        mpz_mul(tmp1, q, r2);  // tmp1 = q * r2
        mpz_sub(r, r1, tmp1);  // r = r1 - tmp1 = r1 - (q * r2)
        mpz_set(r1, r2);       // r1 = r2
        mpz_set(r2, r);        // r2 = r

        mpz_mul(tmp2, q, t2); // tmp2 = q * t2
        mpz_sub(t, t1, tmp2); // t = t1 - tmp2 = t1 - (q * t2)
        mpz_set(t1, t2);      // t1 = t2
        mpz_set(t2, t);       // t2 = t
    }
    mpz_set(a_1, t1);
    if (mpz_sgn(a_1) < 0)
    {
        mpz_add(a_1, n, a_1);
    }
    mpz_clears(q, r1, r2, r, t, t1, t2, tmp1, tmp2, NULL);
    return 0;
}
int libminpie_Gmprsa_PublicKeyGeneration(mpz_t e, mpz_t p, mpz_t q){
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
    //
    mpz_t n, phi_n;
    mpz_t i;
    mpz_t tmp1, tmp2;
    mpz_inits(n, phi_n, NULL);
    mpz_inits(i, NULL);
    mpz_set_si(i, 2);
    mpz_inits(tmp1, tmp2, NULL);

    // get n , phi(n)
    mpz_mul(n, p, q);           // n = p * q;
    mpz_sub_ui(tmp1, p, 1);     // tmp1 = p - 1
    mpz_sub_ui(tmp2, q, 1);     // tmp2 = q - 1
    mpz_mul(phi_n, tmp1, tmp2); // phi_n = tmp1 * tmp2 = (p - 1) * (q - 1)

    // get e
    mpz_set_si(tmp1, 0);
    mpz_set_si(tmp2, 0);
    while (mpz_cmp(phi_n, i))
    {
        // loop 조건: i < phi_n
        libminpie_Gmprsa_GetGcd(tmp1, phi_n, i); // tmp1 = gcd(phi_n, i)
        if (!mpz_cmp_si(tmp1, 1))
        {
            // gcd(phi_n, i) == 1
            mpz_set(e, i); // e = i
            break;
        }
        mpz_add_ui(i, i, 1); // i++
    }

    // end:
    mpz_clears(n, phi_n, NULL);
    mpz_clears(i, NULL);
    mpz_clears(tmp1, tmp2, NULL);
    return 0;
}
int libminpie_Gmprsa_PublicKeyGenerationWithMinValue(mpz_t e, mpz_t p, mpz_t q, mpz_t minval){
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
    //
    mpz_t n, phi_n;
    mpz_t i;
    mpz_t tmp1, tmp2;
    mpz_inits(n, phi_n, NULL);
    mpz_inits(i, NULL);
    mpz_set_si(i, 2);
    mpz_inits(tmp1, tmp2, NULL);

    // get n , phi(n)
    mpz_mul(n, p, q);           // n = p * q;
    mpz_sub_ui(tmp1, p, 1);     // tmp1 = p - 1
    mpz_sub_ui(tmp2, q, 1);     // tmp2 = q - 1
    mpz_mul(phi_n, tmp1, tmp2); // phi_n = tmp1 * tmp2 = (p - 1) * (q - 1)


    // set i:
    if(mpz_cmp_ui(minval, 2) > 0){
        mpz_set(i, minval);
    }

    // get e
    mpz_set_si(tmp1, 0);
    mpz_set_si(tmp2, 0);
    while (mpz_cmp(phi_n, i))
    {
        // loop 조건: i < phi_n
        libminpie_Gmprsa_GetGcd(tmp1, phi_n, i); // tmp1 = gcd(phi_n, i)
        if (!mpz_cmp_si(tmp1, 1))
        {
            // gcd(phi_n, i) == 1
            mpz_set(e, i); // e = i
            break;
        }
        mpz_add_ui(i, i, 1); // i++
    }

    // end:
    mpz_clears(n, phi_n, NULL);
    mpz_clears(i, NULL);
    mpz_clears(tmp1, tmp2, NULL);
    return 0;
}
int libminpie_Gmprsa_PrivateKeyGeneration(mpz_t d, mpz_t e, mpz_t p, mpz_t q){
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
    //
    mpz_t n, phi_n;
    mpz_t i;
    mpz_t tmp1, tmp2;
    mpz_inits(n, phi_n, NULL);
    mpz_inits(i, NULL);
    mpz_set_si(i, 2);
    mpz_inits(tmp1, tmp2, NULL);

    // get n , phi(n)
    mpz_mul(n, p, q);           // n = p * q;
    mpz_sub_ui(tmp1, p, 1);     // tmp1 = p - 1
    mpz_sub_ui(tmp2, q, 1);     // tmp2 = q - 1
    mpz_mul(phi_n, tmp1, tmp2); // phi_n = tmp1 * tmp2 = (p - 1) * (q - 1)

    // get d
    libminpie_Gmprsa_GetModularMultiplicativeInverse(d, phi_n, e);

    // end:
    mpz_clears(n, phi_n, NULL);
    mpz_clears(i, NULL);
    mpz_clears(tmp1, tmp2, NULL);
    return 0;
}
int libminpie_Gmprsa_RsaEncrypt(mpz_t cipher, mpz_t plain, mpz_t n, mpz_t e){
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
    //
    libminpie_Gmprsa_FastModuloExponentiation(cipher, plain, e, n);
    return 0;
}
int libminpie_Gmprsa_RsaDecrypt(mpz_t plain, mpz_t cipher, mpz_t n, mpz_t d){
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
    //
    libminpie_Gmprsa_FastModuloExponentiation(plain, cipher, d, n);
    return 0;
}
// # End code