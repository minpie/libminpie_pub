/*
libminpieAes.c
- under libminpie_c_crypto/symmetric/

AES(Advanced Encryption Standard) library implemented with my own code.
ver.250325.1
-----
requirement:
- (NO REQUIREMENTS)

*/
// # Start code
// ## include:
#include "libminpieAes.h"

// ## function:
// ### 일반 함수:
unsigned int libminpie_Aes_CopyBytes(unsigned char *dst, const unsigned char *src, const unsigned int siz){
    /*
    unsigned int libminpie_Aes_CopyBytes(unsigned char *dst, const unsigned char *src, const unsigned int siz);
    - input: (dst, src, siz):(unsigned char*, const unsigned char*, const unsigned int)
    * dst: Destination pointer.
    * src: Source pointer.
    * siz: size of src and dst in Byte.
    - output: (error code):(unsigned int)
    - do: copy to (dst) from (src) as (siz) bytes.
    - return: always 0(success)
    */
    // 함수 내용:
    for(unsigned int i = 0; i<siz; i++){
        dst[i] = src[i];
    }
    // 함수 종료:
    return 0;
}
unsigned int libminpie_Aes_SizeAsBin(unsigned int n){
    /*
    unsigned int libminpie_Aes_SizeAsBin(unsigned int n);
    - input: (n):(unsigned int)
    * n: target value to measure.
    - output: (siz):(unsigned int)
    - do: count size of n as binary number.
    - return: sizeof n as binary number.
    */
    // 함수 내용:
    unsigned int count = 0;
    while (n > 0)
    {
        n = n >> 1;
        count++;
    }
    return count;
}
// ### AES 관련 함수:
unsigned char libminpie_Aes_Mul2_Gf256(const unsigned char op1){
    /*
    unsigned char libminpie_Aes_Mul2_Gf256(const unsigned char op1);
    - input: (op1):(unsigned char)
    * op1: target value
    - output: (result):(unsigned char)
    - do: Multiplacate (op1) by 2 in GF(2^8).
    - return: (result)
    */
    // 함수 내용:
    return ((op1 << 1) ^ (((op1 >> 7) & 0b1) * 0x1b));
}
unsigned char libminpie_Aes_Mul3_Gf256(const unsigned char op1){
    /*
    unsigned char libminpie_Aes_Mul3_Gf256(const unsigned char op1);
    - input: (op1):(unsigned char)
    * op1: target value
    - output: (result):(unsigned char)
    - do: Multiplacate (op1) by 3 in GF(2^8).
    - return: (result)
    */
    // 함수 내용:
    return (((op1 << 1) ^ (((op1 >> 7) & 0b1) * 0x1b)) ^ op1);
}
unsigned char libminpie_Aes_Mul_Gf256(unsigned char op1, unsigned char op2){
    /*
    unsigned char libminpie_Aes_Mul_Gf256(unsigned char op1, unsigned char op2);
    - input: (op1, op2):(unsigned char, unsigned char)
    * op1: operand 1
    * op2: operand 2
    - output: (result):(unsigned char)
    - do: Multiplacate (op1) by (op2) in GF(2^8).
    - return: (result)
    */
    // 함수 내용:
    unsigned char n = libminpie_Aes_SizeAsBin(op1);
    unsigned char result = 0;
    unsigned char a = op2;

    for (unsigned char i = 0; i < n; i++)
    {
        result = result ^ (((op1 >> i) & 0b1) * a);
        a = libminpie_Aes_Mul2_Gf256(a);
    }
    return result;
}
int libminpie_Aes_SubWord(unsigned char *wrd){
    /*
    int libminpie_Aes_SubWord(unsigned char *wrd);
    - input: (wrd):(unsigned char*)
    * wrd: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do SubWord() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[4]; // 임시 변수
    const unsigned char Sbox[16][16] = {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
    // 1. 연산:
    libminpie_Aes_CopyBytes(temp, wrd, 4);
    for (unsigned char i = 0; i < 4; i++)
    {
        wrd[i] = Sbox[(temp[i] >> 4)][(temp[i] & 0x0f)]; // Sbox 계산
    }
    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_RotWord(unsigned char *wrd){
    /*
    int libminpie_Aes_RotWord(unsigned char *wrd);
    - input: (wrd):(unsigned char*)
    * wrd: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do RotWord() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[4];

    // 1. 연산:
    libminpie_Aes_CopyBytes(temp, wrd, 4);
    wrd[0] = temp[1];
    wrd[1] = temp[2];
    wrd[2] = temp[3];
    wrd[3] = temp[0];

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_Aes128_KeyExpansion(unsigned char *roundKeys, const unsigned char *initialKey){
    /*
    int libminpie_Aes_Aes128_KeyExpansion(unsigned char *roundKeys, const unsigned char *initialKey);
    - input: (roundKeys, initialKey):(unsigned char*, unsigned char*)
    * roundKeys: destination pointer to save generated roundkeys.
    * initialKey: a pointer stores initial key.
    - output: (error code):(unsigned int)
    - do: do KeyExpansion() operation in AES-128.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp1[4];
    unsigned char temp2[4];
    const unsigned char RoundConstant[10][4] = {
        {0x01, 0, 0, 0},
        {0x02, 0, 0, 0},
        {0x04, 0, 0, 0},
        {0x08, 0, 0, 0},
        {0x10, 0, 0, 0},
        {0x20, 0, 0, 0},
        {0x40, 0, 0, 0},
        {0x80, 0, 0, 0},
        {0x1b, 0, 0, 0},
        {0x36, 0, 0, 0}};

    // 1. w0~w3:
    libminpie_Aes_CopyBytes(roundKeys, initialKey, 16);

    // 2. w4~w43:
    for (unsigned char i = 4; i < 44; i++)
    {
        libminpie_Aes_CopyBytes(temp1, &(roundKeys[(i - 1) * 4]), 4); // temp = w[i-1]
        if (!(i % 4))
        {
            // temp1 = SubWord(RotWord(temp1)):
            libminpie_Aes_RotWord(temp1);
            libminpie_Aes_SubWord(temp1);

            // temp1 = temp1 XOR RoundConstant:
            temp2[0] = temp1[0] ^ RoundConstant[(i / 4) - 1][0];
            temp2[1] = temp1[1] ^ RoundConstant[(i / 4) - 1][1];
            temp2[2] = temp1[2] ^ RoundConstant[(i / 4) - 1][2];
            temp2[3] = temp1[3] ^ RoundConstant[(i / 4) - 1][3];
            libminpie_Aes_CopyBytes(temp1, temp2, 4); // temp1 = temp2
        }
        // # w[i] = w[i-4] ^ temp1:
        roundKeys[(i * 4)] = roundKeys[((i - 4) * 4)] ^ temp1[0];
        roundKeys[(i * 4) + 1] = roundKeys[((i - 4) * 4) + 1] ^ temp1[1];
        roundKeys[(i * 4) + 2] = roundKeys[((i - 4) * 4) + 2] ^ temp1[2];
        roundKeys[(i * 4) + 3] = roundKeys[((i - 4) * 4) + 3] ^ temp1[3];
    }

    // 3. 함수 종료:
    return 0;
}
int libminpie_Aes_Aes128_AddRoundKey(unsigned char *state, const unsigned char *roundKey){
    /*
    int libminpie_Aes_Aes128_AddRoundKey(unsigned char *state, const unsigned char *roundKey);
    - input: (state, roundKey):(unsigned char*, unsigned char*)
    * state: target/destination pointer.
    * roundKey: a pointer stored round key will be used.
    - output: (error code):(unsigned int)
    - do: do AddRoundKey() operation in AES-128.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수

    // # 1. 연산:
    libminpie_Aes_CopyBytes(temp, state, 16);
    for (unsigned char i = 0; i < 4; i++)
    {
        state[i] = temp[i] ^ roundKey[(i * 4)];
        state[i + 4] = temp[i + 4] ^ roundKey[(i * 4) + 1];
        state[i + 8] = temp[i + 8] ^ roundKey[(i * 4) + 2];
        state[i + 12] = temp[i + 12] ^ roundKey[(i * 4) + 3];
    }

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_SubBytes(unsigned char *state){
    /*
    int libminpie_Aes_SubBytes(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do SubBytes() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    const unsigned char Sbox[16][16] = {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);
    for (unsigned char i = 0; i < 16; i++)
    {
        state[i] = Sbox[(temp[i] >> 4)][(temp[i] & 0x0f)]; // Sbox 계산
    }

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_InvSubBytes(unsigned char *state){
    /*
    int libminpie_Aes_InvSubBytes(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do InvSubBytes() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    const unsigned char Sbox[16][16] = {
        {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
        {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
        {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
        {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
        {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
        {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
        {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
        {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
        {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
        {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
        {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
        {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
        {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
        {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
        {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
        {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);
    for (unsigned char i = 0; i < 16; i++)
    {
        state[i] = Sbox[(temp[i] >> 4)][(temp[i] & 0x0f)]; // Sbox 계산
    }

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_ShiftRows(unsigned char *state){
    /*
    int libminpie_Aes_ShiftRows(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do ShiftRows() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);

    state[0] = temp[0];
    state[1] = temp[1];
    state[2] = temp[2];
    state[3] = temp[3];

    state[4] = temp[5];
    state[5] = temp[6];
    state[6] = temp[7];
    state[7] = temp[4];

    state[8] = temp[10];
    state[9] = temp[11];
    state[10] = temp[8];
    state[11] = temp[9];

    state[12] = temp[15];
    state[13] = temp[12];
    state[14] = temp[13];
    state[15] = temp[14];

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_InvShiftRows(unsigned char *state){
    /*
    int libminpie_Aes_InvShiftRows(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do InvShiftRows() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);

    state[0] = temp[0];
    state[1] = temp[1];
    state[2] = temp[2];
    state[3] = temp[3];

    state[4] = temp[7];
    state[5] = temp[4];
    state[6] = temp[5];
    state[7] = temp[6];

    state[8] = temp[10];
    state[9] = temp[11];
    state[10] = temp[8];
    state[11] = temp[9];

    state[12] = temp[13];
    state[13] = temp[14];
    state[14] = temp[15];
    state[15] = temp[12];

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_MixColumns(unsigned char *state){
    /*
    int libminpie_Aes_MixColumns(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do MixColumns() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);

    state[0] = (libminpie_Aes_Mul_Gf256(0x2, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[12]));
    state[4] = (libminpie_Aes_Mul_Gf256(0x1, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[12]));
    state[8] = (libminpie_Aes_Mul_Gf256(0x1, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[12]));
    state[12] = (libminpie_Aes_Mul_Gf256(0x3, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[12]));

    state[1] = (libminpie_Aes_Mul_Gf256(0x2, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[13]));
    state[5] = (libminpie_Aes_Mul_Gf256(0x1, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[13]));
    state[9] = (libminpie_Aes_Mul_Gf256(0x1, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[13]));
    state[13] = (libminpie_Aes_Mul_Gf256(0x3, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[13]));

    state[2] = (libminpie_Aes_Mul_Gf256(0x2, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[14]));
    state[6] = (libminpie_Aes_Mul_Gf256(0x1, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[14]));
    state[10] = (libminpie_Aes_Mul_Gf256(0x1, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[14]));
    state[14] = (libminpie_Aes_Mul_Gf256(0x3, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[14]));

    state[3] = (libminpie_Aes_Mul_Gf256(0x2, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[15]));
    state[7] = (libminpie_Aes_Mul_Gf256(0x1, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[15]));
    state[11] = (libminpie_Aes_Mul_Gf256(0x1, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0x3, temp[15]));
    state[15] = (libminpie_Aes_Mul_Gf256(0x3, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0x1, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0x2, temp[15]));

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_InvMixColumns(unsigned char *state){
    /*
    int libminpie_Aes_InvMixColumns(unsigned char *state);
    - input: (state):(unsigned char*)
    * state: source/destination pointer.
    - output: (error code):(unsigned int)
    - do: do InvMixColumns() operation in AES.
    - return: always 0(success)
    */
    // 0. 변수 초기화
    unsigned char temp[16]; // 임시 변수
    // 1.연산:
    libminpie_Aes_CopyBytes(temp, state, 16);

    state[0] = (libminpie_Aes_Mul_Gf256(0xe, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[12]));
    state[4] = (libminpie_Aes_Mul_Gf256(0x9, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[12]));
    state[8] = (libminpie_Aes_Mul_Gf256(0xd, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[12]));
    state[12] = (libminpie_Aes_Mul_Gf256(0xb, temp[0])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[4])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[8])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[12]));

    state[1] = (libminpie_Aes_Mul_Gf256(0xe, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[13]));
    state[5] = (libminpie_Aes_Mul_Gf256(0x9, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[13]));
    state[9] = (libminpie_Aes_Mul_Gf256(0xd, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[13]));
    state[13] = (libminpie_Aes_Mul_Gf256(0xb, temp[1])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[5])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[9])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[13]));

    state[2] = (libminpie_Aes_Mul_Gf256(0xe, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[14]));
    state[6] = (libminpie_Aes_Mul_Gf256(0x9, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[14]));
    state[10] = (libminpie_Aes_Mul_Gf256(0xd, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[14]));
    state[14] = (libminpie_Aes_Mul_Gf256(0xb, temp[2])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[6])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[10])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[14]));

    state[3] = (libminpie_Aes_Mul_Gf256(0xe, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[15]));
    state[7] = (libminpie_Aes_Mul_Gf256(0x9, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[15]));
    state[11] = (libminpie_Aes_Mul_Gf256(0xd, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0xb, temp[15]));
    state[15] = (libminpie_Aes_Mul_Gf256(0xb, temp[3])) ^ (libminpie_Aes_Mul_Gf256(0xd, temp[7])) ^ (libminpie_Aes_Mul_Gf256(0x9, temp[11])) ^ (libminpie_Aes_Mul_Gf256(0xe, temp[15]));

    // 2. 함수 종료:
    return 0;
}

int libminpie_Aes_ConvInputToState(unsigned char *state, const unsigned char *input){
    /*
    int libminpie_Aes_ConvInputToState(unsigned char *state, const unsigned char *input);
    - input: (state, input):(unsigned char*, const unsigned char*)
    * state: destination pointer.
    * input: source pointer.
    - output: (error code):(unsigned int)
    - do: do ConvInputToState() operation in AES.
    - return: always 0(success)
    */
    // 1.연산:
    state[0] = input[0];
    state[1] = input[4];
    state[2] = input[8];
    state[3] = input[12];

    state[4] = input[1];
    state[5] = input[5];
    state[6] = input[9];
    state[7] = input[13];

    state[8] = input[2];
    state[9] = input[6];
    state[10] = input[10];
    state[11] = input[14];

    state[12] = input[3];
    state[13] = input[7];
    state[14] = input[11];
    state[15] = input[15];

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_ConvStateToOutput(unsigned char *output, const unsigned char *state){
    /*
    int libminpie_Aes_ConvStateToOutput(unsigned char *state, const unsigned char *input);
    - input: (output, state):(unsigned char*, const unsigned char*)
    * output: destination pointer.
    * state: source pointer.
    - output: (error code):(unsigned int)
    - do: do ConvStateToOutput() operation in AES.
    - return: always 0(success)
    */
    // 1.연산:
    output[0] = state[0];
    output[4] = state[1];
    output[8] = state[2];
    output[12] = state[3];

    output[1] = state[4];
    output[5] = state[5];
    output[9] = state[6];
    output[13] = state[7];

    output[2] = state[8];
    output[6] = state[9];
    output[10] = state[10];
    output[14] = state[11];

    output[3] = state[12];
    output[7] = state[13];
    output[11] = state[14];
    output[15] = state[15];

    // 2. 함수 종료:
    return 0;
}
int libminpie_Aes_Aes128Encrypt(unsigned char *cipher, unsigned char * plain, unsigned char * key){
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
    // 0. 변수 초기화
    unsigned char state[16];     // 내부 state
    unsigned char roundKey[176]; // roundkey

    // 1. Key Expansion
    libminpie_Aes_Aes128_KeyExpansion(roundKey, key); // key expansion

    // 2. Input To State
    libminpie_Aes_ConvInputToState(state, plain); // plain to state

    // 3. Rounds
    libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[0]));
    for (unsigned char rnd = 1; rnd < 10; rnd++)
    {
        // SubBytes
        libminpie_Aes_SubBytes(state);

        // ShiftRows
        libminpie_Aes_ShiftRows(state);

        // MixColumns
        libminpie_Aes_MixColumns(state);

        // AddRoundKey
        libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[(rnd * 16)]));
    }
    // SubBytes
    libminpie_Aes_SubBytes(state);

    // ShiftRows
    libminpie_Aes_ShiftRows(state);

    // AddRoundKey
    libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[160]));

    // 4. State To Output
    libminpie_Aes_ConvStateToOutput(cipher, state); // state to cipher

    // 5. 함수 종료:
    return 0;
}
int libminpie_Aes_Aes128Decrypt(unsigned char *plain, unsigned char * cipher, unsigned char * key){
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
    // 0. 변수 초기화
    unsigned char state[16];     // 내부 state
    unsigned char roundKey[176]; // roundkey

    // 1. Key Expansion
    libminpie_Aes_Aes128_KeyExpansion(roundKey, key); // key expansion

    // 2. Input To State
    libminpie_Aes_ConvInputToState(state, cipher); // plain to state

    // 3. Rounds
    libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[160]));
    for (unsigned char rnd = 9; rnd > 0; rnd--)
    {
        // InvShiftRows
        libminpie_Aes_InvShiftRows(state);

        // InvSubBytes
        libminpie_Aes_InvSubBytes(state);

        // AddRoundKey
        libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[(rnd * 16)]));

        // InvMixColumns
        libminpie_Aes_InvMixColumns(state);
    }
    // InvShiftRows
    libminpie_Aes_InvShiftRows(state);

    // InvSubBytes
    libminpie_Aes_InvSubBytes(state);

    // AddRoundKey
    libminpie_Aes_Aes128_AddRoundKey(state, &(roundKey[(0)]));

    // 4. State To Output
    libminpie_Aes_ConvStateToOutput(plain, state); // state to cipher

    // 5. 함수 종료:
    return 0;
}
// # End code