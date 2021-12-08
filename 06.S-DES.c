#include "pch.h"
#include <iostream>
#include <stdio.h>

char arr[20] = { '0', };
char k1Arr[10] = { '0', };
char k2Arr[10] = { '0', };
char lArr[5] = { '0', };
char rArr[5] = { '0', };
char eArr[8] = { '0', };
int s1[4][4] = { {1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2} };
int s2[4][4] = { {0,1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3} };
#define ROL(N, W, i) (((W) << (i)) | ((W) >> (N - (i))))
#define GetBit(W,n) (((W)>>(10-n)) &0x01)
#define Get8Bit(W,n) (((W)>>(8-n)) &0x01)
#define Get4Bit(W,n) (((W)>>(4-n)) &0x01)
#define ReturnBit(W,n,k) (((GetBit(W,n)) & 0x01 )<<(10-k))
#define Return8Bit(W,n,k) (((GetBit(W,n)) & 0x01 )<<(8-k))
#define Return8Bit8(W,n,k) (((Get8Bit(W,n)) & 0x01 )<<(8-k))
#define Return8Bit4(W,n,k) (((Get4Bit(W,n)) & 0x01 )<<(8-k))
#define Return4Bit(W,n,k) (((Get4Bit(W,n)) & 0x01 )<<(4-k))

#define permutation(val)\
( ReturnBit(val,3,1) | ReturnBit(val,5,2) | ReturnBit(val,2,3) | \
ReturnBit(val,7,4) | ReturnBit(val,4,5) | ReturnBit(val,10,6) | \
ReturnBit(val,1,7) | ReturnBit(val,9,8) | ReturnBit(val,8,9) | \
ReturnBit(val,6,10) )

#define keyPermutation(val)\
( Return8Bit(val,6,1) | Return8Bit(val,3,2) | Return8Bit(val,7,3) | \
Return8Bit(val,4,4) | Return8Bit(val,8,5) | Return8Bit(val,5,6) | \
Return8Bit(val,10,7) | Return8Bit(val,9,8) )

#define initialPermutation(val)\
( Return8Bit8(val,2,1) | Return8Bit8(val,6,2) | Return8Bit8(val,3,3) | \
Return8Bit8(val,1,4) | Return8Bit8(val,4,5) | Return8Bit8(val,8,6) | \
Return8Bit8(val,5,7) | Return8Bit8(val,7,8) )

#define initialPermutationR(val)\
( Return8Bit8(val,4,1) | Return8Bit8(val,1,2) | Return8Bit8(val,3,3) | \
Return8Bit8(val,5,4) | Return8Bit8(val,7,5) | Return8Bit8(val,2,6) | \
Return8Bit8(val,8,7) | Return8Bit8(val,6,8) )

#define EP(val)\
( Return8Bit4(val,4,1) | Return8Bit4(val,1,2) | Return8Bit4(val,2,3) | \
Return8Bit4(val,3,4) | Return8Bit4(val,2,5) | Return8Bit4(val,3,6) | \
Return8Bit4(val,4,7) | Return8Bit4(val,1,8) )

#define P4(val)\
( Return4Bit(val,2,1) | Return4Bit(val,4,2) | Return4Bit(val,3,3) | \
Return4Bit(val,1,4) )

typedef struct bit10 {
	unsigned k10 : 10;
	unsigned k8 : 8;
	unsigned right : 5;
	unsigned left : 5;
	unsigned pRight : 4;
	unsigned pLeft : 4;
	unsigned p4 : 4;
}key;

char *uintToBinary(key i, int cnt, int a) {
	int count = cnt;
	if (a == 1) {
		do {
			k1Arr[--count] = '0' + (char)(i.k10 & 1);
			i.k10 = i.k10 >> 1;
		} while (count);
		return k1Arr;
	}
	else if (a == 2) {
		do {
			k2Arr[--count] = '0' + (char)(i.k10 & 1);
			i.k10 = i.k10 >> 1;
		} while (count);
		return k2Arr;
	}
	else if (a == 8) {
		do {
			eArr[--count] = '0' + (char)(i.k8 & 1);
			i.k8 = i.k8 >> 1;
		} while (count);
		return eArr;
	}
	else {
		do {
			arr[--count] = '0' + (char)(i.k10 & 1);
			i.k10 = i.k10 >> 1;
		} while (count);
		return arr;
	}
}

char *uintToBinarySide(key i, int cnt, char l) {
	int count = cnt;
	char answer[5] = { '0', };
	if (l == 'l') {
		do {
			lArr[--count] = '0' + (char)(i.left & 1);
			i.left = i.left >> 1;
		} while (count);
		return lArr;
	}
	else {
		do {
			rArr[--count] = '0' + (char)(i.right & 1);
			i.right = i.right >> 1;
		} while (count);
		return rArr;
	}
}

key EPIPFunction(key IP, key keys) {
	key EPIP;
	EPIP.k8 = EP(IP.pRight);
	EPIP.k8 = EPIP.k8 ^ keys.k8;
	EPIP.pLeft = EPIP.k8 / 16;
	EPIP.pRight = EPIP.k8 | 0000;
	int row, column = 0;
	row = (EPIP.pLeft / 8) * 2 + EPIP.pLeft % 2;
	column = ((EPIP.pLeft / 4) % 2) * 2 + ((EPIP.pLeft / 2) % 2);
	int leftInt = s1[row][column];
	row = (EPIP.pRight / 8) * 2 + EPIP.pRight % 2;
	column = ((EPIP.pRight / 4) % 2) * 2 + ((EPIP.pRight / 2) % 2);
	int rightInt = s2[row][column];
	EPIP.p4 = leftInt * 4 + rightInt;
	EPIP.p4 = P4(EPIP.p4);
	return EPIP;
}

int main(void)
{
	key initKey;
	key permutate;
	key key1;
	key key2;

	initKey.k10 = 0x282;
	printf("----------<Given Status>----------------------------------------------------------------\n");
	printf("Initial Key : %s \n", uintToBinary(initKey, 10, 0));

	permutate.k10 = permutation(initKey.k10);
	printf("Permutated k10 : %s \n", uintToBinary(permutate, 10, 0));

	permutate.left = permutate.k10 / 32;
	permutate.right = permutate.k10 | 00000;

	permutate.left = ROL(5, permutate.left, 1);
	permutate.right = ROL(5, permutate.right, 1);
	printf("left Shift 1 : %s, right Shift 1 : %s\n", uintToBinarySide(permutate, 5, 'l'), uintToBinarySide(permutate, 5, 'r'));

	permutate.k10 = (permutate.left * 32) + permutate.right;
	key1.k8 = keyPermutation(permutate.k10);
	printf("key1 : %s \n", uintToBinary(key1, 8, 8));

	permutate.left = ROL(5, permutate.left, 2);
	permutate.right = ROL(5, permutate.right, 2);
	printf("left Shift 2 : %s, right Shift 2 : %s\n", uintToBinarySide(permutate, 5, 'l'), uintToBinarySide(permutate, 5, 'r'));

	permutate.k10 = (permutate.left * 32) + permutate.right;
	key2.k8 = keyPermutation(permutate.k10);
	printf("key2 : %s \n", uintToBinary(key2, 8, 8));
	printf("---------<Input Plaintext from user>----------------------------------------------------\n");
	int binaryVal = 0;
	scanf_s("%d", &binaryVal);
	printf("---------<Plaintext to Ciphertext>------------------------------------------------------\n");
	int squareBit = 1, remainder, decimal = 0;
	while (binaryVal != 0)
	{
		remainder = binaryVal % 10;
		decimal = decimal + remainder * squareBit;
		squareBit = squareBit * 2;
		binaryVal = binaryVal / 10;
	}

	key plainText;
	plainText.k8 = decimal;
	plainText.pLeft = plainText.k8 / 16;
	plainText.pRight = plainText.k8 | 0000;

	key IP;
	IP.k8 = initialPermutation(plainText.k8);
	IP.pLeft = IP.k8 / 16;
	IP.pRight = IP.k8 | 0000;

	key EPIP1 = EPIPFunction(IP, key1);
	key SW;
	SW.pRight = EPIP1.p4 ^ IP.pLeft;
	SW.pLeft = IP.pRight;
	SW.k8 = SW.pLeft * 16 + SW.pRight;
	printf("SW's PlainText : %s \n", uintToBinary(SW, 8, 8));


	key EPIP2 = EPIPFunction(SW, key2);
	key EncryptedText;
	EncryptedText.pRight = SW.pRight;
	EncryptedText.pLeft = EPIP2.p4 ^ SW.pLeft;
	EncryptedText.k8 = EncryptedText.pLeft * 16 + EncryptedText.pRight;
	printf("before IP-reverse function : %s \n", uintToBinary(EncryptedText, 8, 8));

	key ciphertext;
	ciphertext.k8 = initialPermutationR(EncryptedText.k8);
	printf("EncryptedText : %s\n", uintToBinary(ciphertext, 8, 8));
	printf("---------<Ciphertext to Plaintext>------------------------------------------------------\n");
	
	ciphertext.k8 = initialPermutation(ciphertext.k8);
	ciphertext.pLeft = ciphertext.k8 / 16;
	ciphertext.pRight = ciphertext.k8 | 0000;
	key EPIP3 = EPIPFunction(ciphertext, key2);
	key SW3;
	SW3.pRight = EPIP3.p4 ^ ciphertext.pLeft;
	SW3.pLeft = ciphertext.pRight;
	SW3.k8 = SW3.pLeft * 16 + SW3.pRight;
	printf("SW's Ciphertext : %s \n", uintToBinary(SW3, 8, 8));


	key EPIP4 = EPIPFunction(SW3, key1);
	key decryptedText;
	decryptedText.pRight = SW3.pRight;
	decryptedText.pLeft = EPIP4.p4 ^ SW3.pLeft;
	decryptedText.k8 = decryptedText.pLeft * 16 + decryptedText.pRight;
	printf("before IP-reverse function : %s \n", uintToBinary(decryptedText, 8, 8));

	key original;
	original.k8 = initialPermutationR(decryptedText.k8);
	printf("originalText : %s\n\n\n", uintToBinary(original, 8, 8));

	return 0;
}