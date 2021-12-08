// Extended-Uclid.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char arr[5] = { '0', };
int multi[4] = { 0, };
int x[100] = { 0, };
int y[100] = { 0, };
int q[100] = { 0, };
int qc = 2;
int xc = 2;
int yc = 2;

typedef struct bit4 {
	unsigned k5 : 5;
	unsigned k4 : 4;
}gf;

char *uintToBinary(gf i) {
	int count = 4;
	do {
		arr[--count] = '0' + (char)(i.k4 & 1);
		i.k4 = i.k4 >> 1;
	} while (count);
	return arr;
}

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
	while (true) {
		if (input - square < 0) {
			answer--;
			square = square / 2;
		}
		else break;
	}
	return answer;
}

gf hasRemain(gf bigger, gf smaller) {
	if (smaller.k5 == 1) {
		yc--;
		xc--;
		qc--;
		smaller.k4 = y[yc];
		return smaller;
	}
	gf origin = smaller;
	gf answer;
	answer.k5 = 0;
	gf poly;
	poly.k4 = 3;
	gf remain;
	gf que;
	remain.k5 = 0;
	que.k5 = 0;
	int qBit = 0;
	int qValue = 1;

	int check2 = checkBit(smaller);
	while (qBit >= 0) {
		int check1 = checkBit(bigger);
		qBit = check1 - check2;
		smaller.k5 = smaller.k5 << qBit;
		bigger.k5 = bigger.k5 ^ smaller.k5;
		que.k5 += (int)pow(2, qBit);
		que.k4 = que.k5;
		smaller.k5 = smaller.k5 >> qBit;		
	}
	remain.k5 = bigger.k5;
	gf xIn;
	xIn.k4 = x[xc - 1];
	gf yIn;
	yIn.k4 = y[yc - 1];
	q[qc] = que.k5;
	x[xc] = x[xc - 2] ^ multiply(xIn, que, poly).k4;
	y[yc] = y[yc - 2] ^ multiply(yIn, que, poly).k4;
	yc++;
	xc++;
	qc++;
	answer = hasRemain(origin, remain);
	return answer;
}

int main()
{
	int first = 0, second = 0;
	printf("Input first number :\t ");
	scanf_s("%d", &first);
	getchar();

	x[0] = 1;
	x[1] = 0;
	y[0] = 0;
	y[1] = 1;

	printf("Input second number :\t ");
	scanf_s("%d", &second);
	getchar();

	gf firstGF;
	gf secondGF;
	gf polynomial;
	polynomial.k5 = BinaryToDecimal(10011);
	polynomial.k4 = BinaryToDecimal(11);
	printf("poly : %s \n", uintToBinary(polynomial));
	gf plusMinus;
	firstGF.k4 = BinaryToDecimal(first);
	secondGF.k4 = BinaryToDecimal(second);
	printf("%s \n", uintToBinary(secondGF));

	plusMinus.k4 = firstGF.k4 ^ secondGF.k4;

	secondGF.k5 = secondGF.k4;

	printf("+ : %s \n", uintToBinary(plusMinus));
	printf("- : %s \n", uintToBinary(plusMinus));
	printf("* : %s \n", uintToBinary(multiply(firstGF, secondGF, polynomial)));

	gf inverseElement;
	inverseElement = hasRemain(polynomial, secondGF);
	printf("/ : %s \n", uintToBinary(multiply(firstGF, inverseElement, polynomial)));
}