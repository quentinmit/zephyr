/*
 * Copyright (c) 1990 Dennis Ferguson.  All rights reserved.
 *
 * Commercial use is permitted only if products which are derived from
 * or include this software are made available for purchase and/or use
 * in Canada.  Otherwise, redistribution and use in source and binary
 * forms are permitted.
 */

/*
 * des_tables.c - precomputed tables used for the DES cipher function
 */

/*
 * Include the header file so something will complain if the
 * declarations get out of sync
 */
#include "f_tables.h"

/*
 * These tables may be declared const if you want.  Many compilers
 * don't support this, though.
 */

/*
 * The DES algorithm which uses these is intended to be fairly speedy
 * at the expense of some memory.  All the standard hacks are used.
 * The S boxes and the P permutation are precomputed into one table.
 * The E box never actually appears explicitly since it is easy to apply
 * this algorithmically as needed.  The initial permutation and final
 * (inverse initial) permutation are computed from tables designed to
 * permute one byte at a time.  This should run pretty fast on machines
 * with 32 bit words and bit field/multiple bit shift instructions which
 * are fast.
 */

/*
 * The initial permutation array.  This is used to compute both the
 * left and the right halves of the initial permutation using bytes
 * from words made from the following operations:
 *
 * ((left & 0x55555555) << 1) | (right & 0x55555555)  for left half
 * (left & 0xaaaaaaaa) | ((right & 0xaaaaaaaa) >> 1)  for right half
 *
 * The scheme is that we index into the table using each byte.  The
 * result from the high order byte is or'd with the result from the
 * next byte shifted left once is or'd with the result from the next
 * byte shifted left twice if or'd with the result from the low order
 * byte shifted left by three.  Clear?
 */

unsigned long des_IP_table[256] = {
	0x00000000, 0x00000010, 0x00000001, 0x00000011,
	0x00001000, 0x00001010, 0x00001001, 0x00001011,
	0x00000100, 0x00000110, 0x00000101, 0x00000111,
	0x00001100, 0x00001110, 0x00001101, 0x00001111,
	0x00100000, 0x00100010, 0x00100001, 0x00100011,
	0x00101000, 0x00101010, 0x00101001, 0x00101011,
	0x00100100, 0x00100110, 0x00100101, 0x00100111,
	0x00101100, 0x00101110, 0x00101101, 0x00101111,
	0x00010000, 0x00010010, 0x00010001, 0x00010011,
	0x00011000, 0x00011010, 0x00011001, 0x00011011,
	0x00010100, 0x00010110, 0x00010101, 0x00010111,
	0x00011100, 0x00011110, 0x00011101, 0x00011111,
	0x00110000, 0x00110010, 0x00110001, 0x00110011,
	0x00111000, 0x00111010, 0x00111001, 0x00111011,
	0x00110100, 0x00110110, 0x00110101, 0x00110111,
	0x00111100, 0x00111110, 0x00111101, 0x00111111,
	0x10000000, 0x10000010, 0x10000001, 0x10000011,
	0x10001000, 0x10001010, 0x10001001, 0x10001011,
	0x10000100, 0x10000110, 0x10000101, 0x10000111,
	0x10001100, 0x10001110, 0x10001101, 0x10001111,
	0x10100000, 0x10100010, 0x10100001, 0x10100011,
	0x10101000, 0x10101010, 0x10101001, 0x10101011,
	0x10100100, 0x10100110, 0x10100101, 0x10100111,
	0x10101100, 0x10101110, 0x10101101, 0x10101111,
	0x10010000, 0x10010010, 0x10010001, 0x10010011,
	0x10011000, 0x10011010, 0x10011001, 0x10011011,
	0x10010100, 0x10010110, 0x10010101, 0x10010111,
	0x10011100, 0x10011110, 0x10011101, 0x10011111,
	0x10110000, 0x10110010, 0x10110001, 0x10110011,
	0x10111000, 0x10111010, 0x10111001, 0x10111011,
	0x10110100, 0x10110110, 0x10110101, 0x10110111,
	0x10111100, 0x10111110, 0x10111101, 0x10111111,
	0x01000000, 0x01000010, 0x01000001, 0x01000011,
	0x01001000, 0x01001010, 0x01001001, 0x01001011,
	0x01000100, 0x01000110, 0x01000101, 0x01000111,
	0x01001100, 0x01001110, 0x01001101, 0x01001111,
	0x01100000, 0x01100010, 0x01100001, 0x01100011,
	0x01101000, 0x01101010, 0x01101001, 0x01101011,
	0x01100100, 0x01100110, 0x01100101, 0x01100111,
	0x01101100, 0x01101110, 0x01101101, 0x01101111,
	0x01010000, 0x01010010, 0x01010001, 0x01010011,
	0x01011000, 0x01011010, 0x01011001, 0x01011011,
	0x01010100, 0x01010110, 0x01010101, 0x01010111,
	0x01011100, 0x01011110, 0x01011101, 0x01011111,
	0x01110000, 0x01110010, 0x01110001, 0x01110011,
	0x01111000, 0x01111010, 0x01111001, 0x01111011,
	0x01110100, 0x01110110, 0x01110101, 0x01110111,
	0x01111100, 0x01111110, 0x01111101, 0x01111111,
	0x11000000, 0x11000010, 0x11000001, 0x11000011,
	0x11001000, 0x11001010, 0x11001001, 0x11001011,
	0x11000100, 0x11000110, 0x11000101, 0x11000111,
	0x11001100, 0x11001110, 0x11001101, 0x11001111,
	0x11100000, 0x11100010, 0x11100001, 0x11100011,
	0x11101000, 0x11101010, 0x11101001, 0x11101011,
	0x11100100, 0x11100110, 0x11100101, 0x11100111,
	0x11101100, 0x11101110, 0x11101101, 0x11101111,
	0x11010000, 0x11010010, 0x11010001, 0x11010011,
	0x11011000, 0x11011010, 0x11011001, 0x11011011,
	0x11010100, 0x11010110, 0x11010101, 0x11010111,
	0x11011100, 0x11011110, 0x11011101, 0x11011111,
	0x11110000, 0x11110010, 0x11110001, 0x11110011,
	0x11111000, 0x11111010, 0x11111001, 0x11111011,
	0x11110100, 0x11110110, 0x11110101, 0x11110111,
	0x11111100, 0x11111110, 0x11111101, 0x11111111
};

/*
 * The final permutation array.  Like the IP array, used
 * to compute both the left and right results from the bytes
 * of words computed from:
 *
 * ((left & 0x0f0f0f0f) << 4) | (right & 0x0f0f0f0f)  for left result
 * (left & 0xf0f0f0f0) | ((right & 0xf0f0f0f0) >> 4)  for right result
 *
 * The result from the high order byte is shifted left 6 bits and
 * or'd with the result from the next byte shifted left 4 bits, which
 * is or'd with the result from the next byte shifted left 2 bits,
 * which is or'd with the result from the low byte.
 */
unsigned long des_FP_table[256] = {
	0x00000000, 0x02000000, 0x00020000, 0x02020000,
	0x00000200, 0x02000200, 0x00020200, 0x02020200,
	0x00000002, 0x02000002, 0x00020002, 0x02020002,
	0x00000202, 0x02000202, 0x00020202, 0x02020202,
	0x01000000, 0x03000000, 0x01020000, 0x03020000,
	0x01000200, 0x03000200, 0x01020200, 0x03020200,
	0x01000002, 0x03000002, 0x01020002, 0x03020002,
	0x01000202, 0x03000202, 0x01020202, 0x03020202,
	0x00010000, 0x02010000, 0x00030000, 0x02030000,
	0x00010200, 0x02010200, 0x00030200, 0x02030200,
	0x00010002, 0x02010002, 0x00030002, 0x02030002,
	0x00010202, 0x02010202, 0x00030202, 0x02030202,
	0x01010000, 0x03010000, 0x01030000, 0x03030000,
	0x01010200, 0x03010200, 0x01030200, 0x03030200,
	0x01010002, 0x03010002, 0x01030002, 0x03030002,
	0x01010202, 0x03010202, 0x01030202, 0x03030202,
	0x00000100, 0x02000100, 0x00020100, 0x02020100,
	0x00000300, 0x02000300, 0x00020300, 0x02020300,
	0x00000102, 0x02000102, 0x00020102, 0x02020102,
	0x00000302, 0x02000302, 0x00020302, 0x02020302,
	0x01000100, 0x03000100, 0x01020100, 0x03020100,
	0x01000300, 0x03000300, 0x01020300, 0x03020300,
	0x01000102, 0x03000102, 0x01020102, 0x03020102,
	0x01000302, 0x03000302, 0x01020302, 0x03020302,
	0x00010100, 0x02010100, 0x00030100, 0x02030100,
	0x00010300, 0x02010300, 0x00030300, 0x02030300,
	0x00010102, 0x02010102, 0x00030102, 0x02030102,
	0x00010302, 0x02010302, 0x00030302, 0x02030302,
	0x01010100, 0x03010100, 0x01030100, 0x03030100,
	0x01010300, 0x03010300, 0x01030300, 0x03030300,
	0x01010102, 0x03010102, 0x01030102, 0x03030102,
	0x01010302, 0x03010302, 0x01030302, 0x03030302,
	0x00000001, 0x02000001, 0x00020001, 0x02020001,
	0x00000201, 0x02000201, 0x00020201, 0x02020201,
	0x00000003, 0x02000003, 0x00020003, 0x02020003,
	0x00000203, 0x02000203, 0x00020203, 0x02020203,
	0x01000001, 0x03000001, 0x01020001, 0x03020001,
	0x01000201, 0x03000201, 0x01020201, 0x03020201,
	0x01000003, 0x03000003, 0x01020003, 0x03020003,
	0x01000203, 0x03000203, 0x01020203, 0x03020203,
	0x00010001, 0x02010001, 0x00030001, 0x02030001,
	0x00010201, 0x02010201, 0x00030201, 0x02030201,
	0x00010003, 0x02010003, 0x00030003, 0x02030003,
	0x00010203, 0x02010203, 0x00030203, 0x02030203,
	0x01010001, 0x03010001, 0x01030001, 0x03030001,
	0x01010201, 0x03010201, 0x01030201, 0x03030201,
	0x01010003, 0x03010003, 0x01030003, 0x03030003,
	0x01010203, 0x03010203, 0x01030203, 0x03030203,
	0x00000101, 0x02000101, 0x00020101, 0x02020101,
	0x00000301, 0x02000301, 0x00020301, 0x02020301,
	0x00000103, 0x02000103, 0x00020103, 0x02020103,
	0x00000303, 0x02000303, 0x00020303, 0x02020303,
	0x01000101, 0x03000101, 0x01020101, 0x03020101,
	0x01000301, 0x03000301, 0x01020301, 0x03020301,
	0x01000103, 0x03000103, 0x01020103, 0x03020103,
	0x01000303, 0x03000303, 0x01020303, 0x03020303,
	0x00010101, 0x02010101, 0x00030101, 0x02030101,
	0x00010301, 0x02010301, 0x00030301, 0x02030301,
	0x00010103, 0x02010103, 0x00030103, 0x02030103,
	0x00010303, 0x02010303, 0x00030303, 0x02030303,
	0x01010101, 0x03010101, 0x01030101, 0x03030101,
	0x01010301, 0x03010301, 0x01030301, 0x03030301,
	0x01010103, 0x03010103, 0x01030103, 0x03030103,
	0x01010303, 0x03010303, 0x01030303, 0x03030303
};


/*
 * The SP table is actually the S boxes and the P permutation
 * table combined.  This table is actually reordered from the
 * spec, to match the order of key application we follow.
 */
unsigned long des_SP_table[8][64] = {
	0x00100000, 0x02100001, 0x02000401, 0x00000000,	/* 7 */
	0x00000400, 0x02000401, 0x00100401, 0x02100400,
	0x02100401, 0x00100000, 0x00000000, 0x02000001,
	0x00000001, 0x02000000, 0x02100001, 0x00000401,
	0x02000400, 0x00100401, 0x00100001, 0x02000400,
	0x02000001, 0x02100000, 0x02100400, 0x00100001,
	0x02100000, 0x00000400, 0x00000401, 0x02100401,
	0x00100400, 0x00000001, 0x02000000, 0x00100400,
	0x02000000, 0x00100400, 0x00100000, 0x02000401,
	0x02000401, 0x02100001, 0x02100001, 0x00000001,
	0x00100001, 0x02000000, 0x02000400, 0x00100000,
	0x02100400, 0x00000401, 0x00100401, 0x02100400,
	0x00000401, 0x02000001, 0x02100401, 0x02100000,
	0x00100400, 0x00000000, 0x00000001, 0x02100401,
	0x00000000, 0x00100401, 0x02100000, 0x00000400,
	0x02000001, 0x02000400, 0x00000400, 0x00100001,

	0x00808200, 0x00000000, 0x00008000, 0x00808202,	/* 1 */
	0x00808002, 0x00008202, 0x00000002, 0x00008000,
	0x00000200, 0x00808200, 0x00808202, 0x00000200,
	0x00800202, 0x00808002, 0x00800000, 0x00000002,
	0x00000202, 0x00800200, 0x00800200, 0x00008200,
	0x00008200, 0x00808000, 0x00808000, 0x00800202,
	0x00008002, 0x00800002, 0x00800002, 0x00008002,
	0x00000000, 0x00000202, 0x00008202, 0x00800000,
	0x00008000, 0x00808202, 0x00000002, 0x00808000,
	0x00808200, 0x00800000, 0x00800000, 0x00000200,
	0x00808002, 0x00008000, 0x00008200, 0x00800002,
	0x00000200, 0x00000002, 0x00800202, 0x00008202,
	0x00808202, 0x00008002, 0x00808000, 0x00800202,
	0x00800002, 0x00000202, 0x00008202, 0x00808200,
	0x00000202, 0x00800200, 0x00800200, 0x00000000,
	0x00008002, 0x00008200, 0x00000000, 0x00808002,

	0x00000104, 0x04010100, 0x00000000, 0x04010004,	/* 3 */
	0x04000100, 0x00000000, 0x00010104, 0x04000100,
	0x00010004, 0x04000004, 0x04000004, 0x00010000,
	0x04010104, 0x00010004, 0x04010000, 0x00000104,
	0x04000000, 0x00000004, 0x04010100, 0x00000100,
	0x00010100, 0x04010000, 0x04010004, 0x00010104,
	0x04000104, 0x00010100, 0x00010000, 0x04000104,
	0x00000004, 0x04010104, 0x00000100, 0x04000000,
	0x04010100, 0x04000000, 0x00010004, 0x00000104,
	0x00010000, 0x04010100, 0x04000100, 0x00000000,
	0x00000100, 0x00010004, 0x04010104, 0x04000100,
	0x04000004, 0x00000100, 0x00000000, 0x04010004,
	0x04000104, 0x00010000, 0x04000000, 0x04010104,
	0x00000004, 0x00010104, 0x00010100, 0x04000004,
	0x04010000, 0x04000104, 0x00000104, 0x04010000,
	0x00010104, 0x00000004, 0x04010004, 0x00010100,

	0x00000080, 0x01040080, 0x01040000, 0x21000080,	/* 5 */
	0x00040000, 0x00000080, 0x20000000, 0x01040000,
	0x20040080, 0x00040000, 0x01000080, 0x20040080,
	0x21000080, 0x21040000, 0x00040080, 0x20000000,
	0x01000000, 0x20040000, 0x20040000, 0x00000000,
	0x20000080, 0x21040080, 0x21040080, 0x01000080,
	0x21040000, 0x20000080, 0x00000000, 0x21000000,
	0x01040080, 0x01000000, 0x21000000, 0x00040080,
	0x00040000, 0x21000080, 0x00000080, 0x01000000,
	0x20000000, 0x01040000, 0x21000080, 0x20040080,
	0x01000080, 0x20000000, 0x21040000, 0x01040080,
	0x20040080, 0x00000080, 0x01000000, 0x21040000,
	0x21040080, 0x00040080, 0x21000000, 0x21040080,
	0x01040000, 0x00000000, 0x20040000, 0x21000000,
	0x00040080, 0x01000080, 0x20000080, 0x00040000,
	0x00000000, 0x20040000, 0x01040080, 0x20000080,

	0x80401000, 0x80001040, 0x80001040, 0x00000040,	/* 4 */
	0x00401040, 0x80400040, 0x80400000, 0x80001000,
	0x00000000, 0x00401000, 0x00401000, 0x80401040,
	0x80000040, 0x00000000, 0x00400040, 0x80400000,
	0x80000000, 0x00001000, 0x00400000, 0x80401000,
	0x00000040, 0x00400000, 0x80001000, 0x00001040,
	0x80400040, 0x80000000, 0x00001040, 0x00400040,
	0x00001000, 0x00401040, 0x80401040, 0x80000040,
	0x00400040, 0x80400000, 0x00401000, 0x80401040,
	0x80000040, 0x00000000, 0x00000000, 0x00401000,
	0x00001040, 0x00400040, 0x80400040, 0x80000000,
	0x80401000, 0x80001040, 0x80001040, 0x00000040,
	0x80401040, 0x80000040, 0x80000000, 0x00001000,
	0x80400000, 0x80001000, 0x00401040, 0x80400040,
	0x80001000, 0x00001040, 0x00400000, 0x80401000,
	0x00000040, 0x00400000, 0x00001000, 0x00401040,

	0x10000008, 0x10200000, 0x00002000, 0x10202008,	/* 6 */
	0x10200000, 0x00000008, 0x10202008, 0x00200000,
	0x10002000, 0x00202008, 0x00200000, 0x10000008,
	0x00200008, 0x10002000, 0x10000000, 0x00002008,
	0x00000000, 0x00200008, 0x10002008, 0x00002000,
	0x00202000, 0x10002008, 0x00000008, 0x10200008,
	0x10200008, 0x00000000, 0x00202008, 0x10202000,
	0x00002008, 0x00202000, 0x10202000, 0x10000000,
	0x10002000, 0x00000008, 0x10200008, 0x00202000,
	0x10202008, 0x00200000, 0x00002008, 0x10000008,
	0x00200000, 0x10002000, 0x10000000, 0x00002008,
	0x10000008, 0x10202008, 0x00202000, 0x10200000,
	0x00202008, 0x10202000, 0x00000000, 0x10200008,
	0x00000008, 0x00002000, 0x10200000, 0x00202008,
	0x00002000, 0x00200008, 0x10002008, 0x00000000,
	0x10202000, 0x10000000, 0x00200008, 0x10002008,

	0x08000820, 0x00000800, 0x00020000, 0x08020820,	/* 8 */
	0x08000000, 0x08000820, 0x00000020, 0x08000000,
	0x00020020, 0x08020000, 0x08020820, 0x00020800,
	0x08020800, 0x00020820, 0x00000800, 0x00000020,
	0x08020000, 0x08000020, 0x08000800, 0x00000820,
	0x00020800, 0x00020020, 0x08020020, 0x08020800,
	0x00000820, 0x00000000, 0x00000000, 0x08020020,
	0x08000020, 0x08000800, 0x00020820, 0x00020000,
	0x00020820, 0x00020000, 0x08020800, 0x00000800,
	0x00000020, 0x08020020, 0x00000800, 0x00020820,
	0x08000800, 0x00000020, 0x08000020, 0x08020000,
	0x08020020, 0x08000000, 0x00020000, 0x08000820,
	0x00000000, 0x08020820, 0x00020020, 0x08000020,
	0x08020000, 0x08000800, 0x08000820, 0x00000000,
	0x08020820, 0x00020800, 0x00020800, 0x00000820,
	0x00000820, 0x00020020, 0x08000000, 0x08020800,

	0x40084010, 0x40004000, 0x00004000, 0x00084010,	/* 2 */
	0x00080000, 0x00000010, 0x40080010, 0x40004010,
	0x40000010, 0x40084010, 0x40084000, 0x40000000,
	0x40004000, 0x00080000, 0x00000010, 0x40080010,
	0x00084000, 0x00080010, 0x40004010, 0x00000000,
	0x40000000, 0x00004000, 0x00084010, 0x40080000,
	0x00080010, 0x40000010, 0x00000000, 0x00084000,
	0x00004010, 0x40084000, 0x40080000, 0x00004010,
	0x00000000, 0x00084010, 0x40080010, 0x00080000,
	0x40004010, 0x40080000, 0x40084000, 0x00004000,
	0x40080000, 0x40004000, 0x00000010, 0x40084010,
	0x00084010, 0x00000010, 0x00004000, 0x40000000,
	0x00004010, 0x40084000, 0x00080000, 0x40000010,
	0x00080010, 0x40004010, 0x40000010, 0x00080010,
	0x00084000, 0x00000000, 0x40004000, 0x00004010,
	0x40000000, 0x40080010, 0x40084010, 0x00084000
};
