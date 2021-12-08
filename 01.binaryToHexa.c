// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int main()
{
	int binaryVal, hexaVal = 0;
	int squareBit = 1, remainder;

	printf("2진수 값을 입력해주세요: ");
	scanf_s("%ld", &binaryVal);
	while (binaryVal != 0)
	{
		remainder = binaryVal % 10;
		hexaVal = hexaVal + remainder * squareBit;
		squareBit = squareBit * 2;
		binaryVal = binaryVal / 10;
	}
	printf("Equivalent hexadecimal value: %X", hexaVal);
	return 0;
}