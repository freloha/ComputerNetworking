// ConsoleApplication1.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int main()
{
	int binaryVal, hexaVal = 0;
	int squareBit = 1, remainder;

	printf("2���� ���� �Է����ּ���: ");
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