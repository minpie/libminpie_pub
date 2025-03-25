/*
example3.c
- under libminpie_c_crypto/example

an example program to test RSA with GNU GMP.
ver.250325.1

compile with like this:
- gcc -o example3 example3.c -L"./../output" -Wl,-rpath="./../output" -l"minpieGmprsa" -lgmp
- gcc -o example3 example3.c -L"./../output" -Wl,-rpath="./../output" -l"minpiecrypto" -lssl -lcrypto -lgmp
*/
// # Start code
// ## include:
#include <stdio.h>
#include <time.h>
#include "libminpieGmprsa.h"


// ## main()
int main(void){
    // start:
    mpz_t p, q, n, e, d, e_minval;
    mpz_t plain, cipher, plain2;
    mpz_inits(p, q, n, e, d, e_minval, NULL);
    mpz_inits(plain, cipher, plain2, NULL);

    // test:
    mpz_set_str(p, "9613034531358350457419158128061542790930984559499621582258315087964794045505647063849125716018034750312098666606492420191808780667421096063354219926661209", 10);
    mpz_set_str(q, "12060191957231446918276794204450896001555925054637033936061798321731482148483764659215389453209175225273226830107120695604602513887145524969000359660045617", 10);
    mpz_set_str(plain, "1907081826081826002619041819", 10);


    // for time check:
    double startClock = (double)clock();

    // get n, e, d
    mpz_mul(n, p, q); // n = p = q;
    mpz_set_ui(e_minval, 65536);
    libminpie_Gmprsa_PublicKeyGenerationWithMinValue(e, p, q, e_minval);
    //libminpie_Gmprsa_PublicKeyGeneration(e, p, q);
    libminpie_Gmprsa_PrivateKeyGeneration(d, e, p, q);

    gmp_printf("Public Key (n, e)=(%Zd, %Zd)\n", n, e);
    gmp_printf("Private Key (d)=(%Zd)\n", d);

    libminpie_Gmprsa_RsaEncrypt(cipher, plain, n, e);
    libminpie_Gmprsa_RsaDecrypt(plain2, cipher, n, d);

    // for time check:
    double endClock = (double)clock();

    // print:
    gmp_printf("Encryption: P=%Zd, C=%Zd\n", plain, cipher);
    gmp_printf("Decryption: C=%Zd, P=%Zd\n", cipher, plain2);
    printf("used time: %.04lf Sec\n", ((endClock - startClock) / CLOCKS_PER_SEC));

    // end:
    mpz_clears(p, q, n, e, d, e_minval, NULL);
    mpz_clears(plain, cipher, plain2, NULL);
    return 0;
}
// # End code