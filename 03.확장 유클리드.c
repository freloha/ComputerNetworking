// Extended-Uclid.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int r[100] = { '0', };
int q[100] = { '0', }; // q, x, y starts from index -1
int x[100] = { '0', }; // which means add + 2 in index.
int y[100] = { '0', };
int qc = 2;
int xc = 2;
int yc = 2;

int hasRemain(int bigger, int smaller) {
	int remain = bigger % smaller;
	int que = bigger / smaller;
	if (remain == 0) {
		yc--;
		xc--;
		qc--;
		return smaller;
	}
	else {
		q[qc] = que;
		x[xc] = x[xc - 2] - q[xc] * x[xc - 1];
		y[yc] = y[yc - 2] - q[yc] * y[yc - 1];
		printf("%d, %d, %d \n", q[qc], x[xc], y[yc]);
		yc++;
		xc++;
		qc++;
		hasRemain(smaller, remain);
	}
}

int main()
{
	int first, second, remain = 1;
	printf("Input first number : ");
	scanf_s("%d", &first);
	printf("\n");
	printf("Input second number : ");
	scanf_s("%d", &second);
	printf("\n");

	int bigger, smaller;
	if (first > second) {
		bigger = first;
		smaller = second;
	}
	else {
		bigger = second;
		smaller = first;
	}

	x[0] = 1;
	x[1] = 0;
	y[0] = 0;
	y[1] = 1;

	int i;
	for (i = 0; i < 2; i++) {
		printf("%d, %d \n", x[i], y[i]);
	}
	int answer = hasRemain(bigger, smaller);
	printf("GCD of %d and %d is %d.\n", first, second, answer);
	if (y[yc] < 0)
		y[yc] = bigger + y[yc];
	printf("Inverse element of multiple : %d. \n", y[yc]);
	return 0;
}