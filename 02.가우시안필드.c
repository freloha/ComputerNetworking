// Extended-Uclid.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


int reverse[7] = { '0', };


int main()
{
	int first, second, remain = 1;
	char operation = '0';
	printf("Input first number : ");
	scanf_s("%d", &first);
	getchar();
	printf("Input second number : ");
	scanf_s("%d", &second);
	getchar();
	printf("Which operation do you want? : 1 : +,2 : -,3 : * ,4 : / \n");
	scanf_s("%c", &operation);
	printf("\n");

	int i;
	int j;
	int rev = 0;
	for (i = 1; i < 7; i++) {
		for (j = 1; j < 7; j++) {
			rev = (i * j) % 7;
			if (rev == 1) {
				reverse[i] = j;
				break;
			}
		}
	}

	int problem = 0;
	if (operation == '+') {
		problem = (first + second) % 7;
		printf("(%d + %d)mod7 is %d.\n", first, second, problem);
	}
	else if (operation == '-') {
		problem = (first + (7 - second)) % 7;
		printf("(%d - %d)mod7 is %d.\n", first, second, problem);
	}

	else if (operation == '*') {
		problem = (first * second) % 7;
		printf("(%d * %d)mod7 is %d.\n", first, second, problem);
	}
	else {
		problem = (first * reverse[second]) % 7;
		printf("(%d / %d)mod7 is %d.\n", first, second, problem);
	}
	return 0;
}