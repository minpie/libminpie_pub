<h1>libminpie_c_crypto </h1>
minpie의 libminpie_c_crypto 라이브러리 입니다.<br>

```
Disclaimer: This is my experimental library. Do not use serious/important program. it just for my studying.
면책조항: 이 패키지는 저의 실험적인 라이브러리 입니다. 절대로 중요한 용도로 사용하지 마십시오. 단지 공부용으로 만들었습니다.
```<br>

<hr>
<h2>Installation</h2>
following commands is based on Ubuntu Linux environment.<br>

<h4>0. Prepare requirements.</h4>
My development environment are using below programs/whatever.<br>
If you using other environment, may not compiled or need some modify.<br>

```
Ubuntu 20.04 LTS x86-64 architecture
GCC 9.4.0
OpenSSL 1.1.1f
```<br>
comment 1: Other linux version may works.<br>
comment 2: OpenSSL is can be easily installed by ($ sudo apt-get install libssl-dev), but will be not latest version.<br>

<h4>1. Clone this repo.</h4>
```
git clone https://github.com/minpie/libminpie_pub.git
cd libminpie_pub/libminpie_c_crypto
```
clone this repo with git command(or whatever you want) on a directory where you want.<br>
and move to the downloaded directory.<br>

<h4>2. Build this library.</h4>
```
chmod +x build.sh
./build.sh
```<br>
The file build.sh will compile my source codes to .so library file.<br>
If you need, you can modify build.sh to change something(e.g. GCC version)<br>

<h4>3. Set correct path to access this library(OPTIONAL)</h4>
will add this section later.<br>
for now, you can use like Usage section. or do it yourself.<br>

<h4>Usage</h4>
you can use my library with like below compile command:
```
gcc -o [output name] [your source code name].c -L"./../output" -Wl,-rpath="./../output" -l"minpieSslaes" -lssl -lcrypto
```<br>

<h2>Example program use guide</h2>
1. write example c source code.<br>
following source code is named "example1.c"<br>
```
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
```<br>
save this any directory(in this example, will be called "./example1.c")<br>

2. get libminpieSslaes.h<br>
find libminpieSslaes.h file in my repository and place to same directory to example1.c<br>

3. compile it<br>
use below compile command:<br>
```
gcc -o example1 example1.c -L"./../output" -Wl,-rpath="./../output" -l"minpieSslaes" -lssl -lcrypto
```<br>
notice 1: the option: -L"./../output" is MUST edited to correct path where have libminpieSslaes.so<br>
notice 2: the option: -Wl,-rpath="./../output" is MUST edited to correct path where have libminpieSslaes.so<br>
notice 3: in this example, I assume you already installed OpenSSL and you can use with GCC compiler. if not, sorry.<br>

4. Run<br>
if no output showed, that may means no error. so you can run the program like this:<br>
```
./example1
```<br>

5. Result<br>
result will be like this:<br>
```
========Encrypt==============
plain1  : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
cipher1 : 34882238f2930783c7b7b12dc3b58bea
key1    : 5555555555555555555555555555555555555555555555555555555555555555
========Decrypt==============
plain2  : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
cipher2 : 34882238f2930783c7b7b12dc3b58bea
key2    : 5555555555555555555555555555555555555555555555555555555555555555
========End==============
```<br>
### That's All, for now!</h3>
<hr>