// Extended-Uclid.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
char arr[4] = { '0', };
int multi[4] = { 0, };
int SBox[4][4] = { {9,4,10,11},{13,1,8,5}, {6,2,0,3},{12,14,15,7} };
int ReverseSBox[4][4] = { {10,5,9,11},{1,7,8,15},{6,0,2,3},{12,4,13,14} };

typedef struct bit4 {
	unsigned k5 : 5;
	unsigned k4 : 4;
}gf;

typedef struct bit16 {
	unsigned k00 : 4;
	unsigned k01 : 4;
	unsigned k10 : 4;
	unsigned k11 : 4;
}text;

int BinaryToDecimal(int in) {
	int answer = 0;
	int squareBit = 1, remainder = 0, decimalF = 0, decimalS = 0;
	while (in != 0)
	{
		remainder = in % 10;
		answer = answer + remainder * squareBit;
		squareBit = squareBit * 2;
		in = in / 10;
	}
	return answer;
}

char *uintToBinary(gf i) {
	int count = 4;
	do {
		--count;
		arr[count] = '0' + (char)(i.k4 & 1);

		i.k4 = i.k4 >> 1;
	} while (count);
	return arr;
}

gf multiply(gf f, gf s, gf p) {
	gf answer;
	answer.k4 = 0;
	int squareBit = 8;
	int bit = 0;
	int i;
	for (i = 0; i < 4; i++) {
		bit = s.k4 % 2;
		s.k4 = s.k4 >> 1;
		if (bit == 1)
			answer.k4 = answer.k4 ^ f.k4;
		if (f.k4 / squareBit == 1) {
			f.k4 = f.k4 << 1;
			f.k4 = f.k4 ^ p.k4;
			
		}
		else
			f.k4 = f.k4 << 1;
	}
	return answer;
}

int checkBit(gf in) {
	int input = 0 + in.k5;
	int answer = 4;
	int square = 16;
	while (1) {
		if (input - square < 0) {
			answer--;
			square = square / 2;
		}
		else break;
	}
	return answer;
}

text KE(text k, int i) {
	text temp;
	text tKey;
	
	tKey.k01 = k.k11;
	tKey.k11 = k.k01;
	tKey.k01 = SBox[(tKey.k01 >> 2) & 11][tKey.k01 % 4];
	tKey.k11 = SBox[(tKey.k11 >> 2) & 11][tKey.k11 % 4];

	if (i == 1) {
		temp.k01 = 8;
		tKey.k01 = tKey.k01 ^ temp.k01;
	}
	else {
		temp.k01 = 3;
		tKey.k01 = tKey.k01 ^ temp.k01;
	}
	k.k00 = k.k00 ^ tKey.k01;
	k.k10 = k.k10 ^ tKey.k11;
	k.k01 = k.k01 ^ k.k00;
	k.k11 = k.k11 ^ k.k10;
	return k;
}

text AK(text p, text k) {
	text answer;
	answer.k00 = p.k00 ^ k.k00;
	answer.k10 = p.k10 ^ k.k10;
	answer.k01 = p.k01 ^ k.k01;
	answer.k11 = p.k11 ^ k.k11;
	return answer;
}

text NS(text p) {
	text answer;
	answer.k00 = SBox[(p.k00 >> 2) & 11][(p.k00 % 4) & 11];
	answer.k10 = SBox[(p.k10 >> 2) & 11][(p.k10 % 4) & 11];
	answer.k01 = SBox[(p.k01 >> 2) & 11][(p.k01 % 4) & 11];
	answer.k11 = SBox[(p.k11 >> 2) & 11][(p.k11 % 4) & 11];
	return answer;
}

text RNS(text p) {
	text answer;
	answer.k00 = ReverseSBox[(p.k00 >> 2) & 11][(p.k00 % 4) & 11];
	answer.k10 = ReverseSBox[(p.k10 >> 2) & 11][(p.k10 % 4) & 11];
	answer.k01 = ReverseSBox[(p.k01 >> 2) & 11][(p.k01 % 4) & 11];
	answer.k11 = ReverseSBox[(p.k11 >> 2) & 11][(p.k11 % 4) & 11];
	return answer;
}

text SR(text p) {
	text answer;
	text temp;
	temp.k10 = p.k11;
	temp.k11 = p.k10;
	answer.k00 = p.k00;
	answer.k01 = p.k01;
	answer.k10 = temp.k10;
	answer.k11 = temp.k11;
	return answer;
}

text MC(text p, text a, gf poly) {
	text answer;
	gf temp1;
	gf temp2;
	gf temp3;
	gf temp4;

	temp1.k4 = p.k00;
	temp2.k4 = a.k00;
	temp3.k4 = p.k10;
	temp4.k4 = a.k01;
	answer.k00 = multiply(temp1, temp2, poly).k4 ^ multiply(temp3, temp4, poly).k4;

	temp1.k4 = p.k01;
	temp2.k4 = a.k00;
	temp3.k4 = p.k11;
	temp4.k4 = a.k01;
	answer.k01 = multiply(temp1, temp2, poly).k4 ^ multiply(temp4, temp3, poly).k4;

	temp1.k4 = p.k00;
	temp2.k4 = a.k10;
	temp3.k4 = p.k10;
	temp4.k4 = a.k11;
	answer.k10 = multiply(temp1, temp2, poly).k4 ^ multiply(temp3, temp4, poly).k4;

	temp1.k4 = p.k01;
	temp2.k4 = a.k10;
	temp3.k4 = p.k11;
	temp4.k4 = a.k11;
	answer.k11 = multiply(temp1, temp2, poly).k4 ^ multiply(temp3, temp4, poly).k4;

	return answer;
}

int main()
{
	text CMC;
	CMC.k00 = 1;
	CMC.k01 = 4;
	CMC.k10 = 4;
	CMC.k11 = 1;
	text RMC;
	RMC.k00 = 9;
	RMC.k01 = 2;
	RMC.k10 = 2;
	RMC.k11 = 9;
	text EncryptedKey;
	int plainText00 = 0, plainText01 = 0, plainText10 = 0, plainText11 = 0;
	int keyText00 = 0, keyText01 = 0, keyText10 = 0, keyText11 = 0;
	gf polynomial;
	polynomial.k4 = 3;
	printf("Input plainText :\t \n");
	scanf_s("%d", &plainText00);
	scanf_s("%d", &plainText10);
	scanf_s("%d", &plainText01);
	scanf_s("%d", &plainText11);

	text plain;
	plain.k00 = BinaryToDecimal(plainText00);
	plain.k01 = BinaryToDecimal(plainText01);
	plain.k10 = BinaryToDecimal(plainText10);
	plain.k11 = BinaryToDecimal(plainText11);

	printf("Input keyText :\t \n");
	scanf_s("%d", &keyText00);
	scanf_s("%d", &keyText10);
	scanf_s("%d", &keyText01);
	scanf_s("%d", &keyText11);

	text key;
	key.k00 = BinaryToDecimal(keyText00);
	key.k01 = BinaryToDecimal(keyText01);
	key.k10 = BinaryToDecimal(keyText10);
	key.k11 = BinaryToDecimal(keyText11);

	plain = AK(plain, key);
	plain = NS(plain);
	plain = SR(plain);
	plain = MC(plain, CMC, polynomial);

	text ExtendedKey1;
	ExtendedKey1 = KE(key, 1);
	plain = AK(plain, ExtendedKey1);
	plain = NS(plain);
	plain = SR(plain);

	text ExtendedKey2 = KE(ExtendedKey1, 2);
	EncryptedKey = AK(plain, ExtendedKey2);
	gf forPrint;
	forPrint.k4 = EncryptedKey.k00;
	printf("Encrypted PlainText : %s ", uintToBinary(forPrint));
	forPrint.k4 = EncryptedKey.k10;
	printf("%s ", uintToBinary(forPrint));
	forPrint.k4 = EncryptedKey.k01;
	printf("%s ", uintToBinary(forPrint));
	forPrint.k4 = EncryptedKey.k11;
	printf("%s\n", uintToBinary(forPrint));

	EncryptedKey = AK(EncryptedKey, ExtendedKey2);
	EncryptedKey = SR(EncryptedKey);
	EncryptedKey = RNS(EncryptedKey);
	EncryptedKey = AK(EncryptedKey, ExtendedKey1);
	EncryptedKey = MC(EncryptedKey, RMC, polynomial);
	EncryptedKey = SR(EncryptedKey);
	EncryptedKey = RNS(EncryptedKey);
	plain = AK(EncryptedKey, key);
	forPrint.k4 = plain.k00;
	printf("Decoded EncryptionText : %s ", uintToBinary(forPrint));
	forPrint.k4 = plain.k10;
	printf("%s ", uintToBinary(forPrint));
	forPrint.k4 = plain.k01;
	printf("%s ", uintToBinary(forPrint));
	forPrint.k4 = plain.k11;
	printf("%s\n", uintToBinary(forPrint));
}