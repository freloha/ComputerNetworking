#include "pch.h"
#include <iostream>
#include <stdio.h>

char arr[20] = { '0', };
char rArr[10] = { '0', };
char rArray[10] = { '0', };
char lArr[10] = { '0', };
#define ROL(N,W,i) (((W)<<(i)) | ((W)>>(N-(i))))
#define GetBit(W,n) (((W)>>(10-n)) &0x01)
#define ReturnBit(W,n,k) (((GetBit(W,n)) & 0x01 )<<(10-k))
#define permutation(val)\
( ReturnBit(val,3,1) | ReturnBit(val,5,2) | ReturnBit(val,2,3) | \
ReturnBit(val,7,4) | ReturnBit(val,4,5) | ReturnBit(val,10,6) | \
ReturnBit(val,1,7) | ReturnBit(val,9,8) | ReturnBit(val,8,9) | \
ReturnBit(val,6,10) )

typedef struct bit10 {
	unsigned k10 : 10;
	unsigned right : 5;
	unsigned left : 5;
}key;

typedef struct bit5 {
	unsigned k5 : 5;
}desperate;

char *uintToBinary(key i, int cnt) {
	int count = cnt;
	do {
		arr[--count] = '0' + (char)(i.k10 & 1);
		i.k10 = i.k10 >> 1;
	} while (count);
	return arr;
}

void *divideBy5(key i, int cnt) {
	int count = cnt / 2;
	do {
		lArr[--count] = '0' + (char)(i.k10 & 1);
		i.k10 = i.k10 >> 1;
	} while (count);
	count = cnt / 2;
	do {
		rArr[--count] = '0' + (char)(i.k10 & 1);
		i.k10 = i.k10 >> 1;
	} while (count);
	return 0;
}

void *moveBit(int cnt) {

	char lArray[5] = { '0', };
	int counter = 0;
	for(counter = 0; counter < cnt; counter++) {
		int j;
		rArray[4] = rArr[0];
		lArray[4] = lArr[0];
		for (j = 0; j < 4; j++) {
			rArray[j] = rArr[j + 1];
			lArray[j] = lArr[j + 1];
		}
		int i;
		for (i = 0; i < 5; i++) {
			rArr[i] = rArray[i];
			lArr[i] = lArray[i];
		}
	}
	return 0;
}

int main(void)
{
	key initKey;
	key permutate;

	initKey.k10 = 0x282;
	printf("p10 : %s \n", uintToBinary(initKey, 10));
	permutate.k10 = permutation(initKey.k10);
	printf("p10 : %s \n", uintToBinary(permutate, 10));
	divideBy5(permutate, 10);
	printf("p10's right : %s / left : %s\n", rArr, lArr);
	moveBit(2);
	printf("p10's right : %s / left : %s", rArr, lArr);
	return 0;
}