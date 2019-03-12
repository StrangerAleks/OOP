/* flipbyte.exe - измененяет порядок следования двоичных битов в 8 - битовом целом числе(байте),
заданном в десятичном представлении, на противоположный.
«Перевернутый» байт выводится в output также в десятичном представлении с завершающим символом перевода строки \n.
Формат командной строки приложения : flipbyte.exe <входной байт>
Некорректные входные данные(например, передача строки, не являющейся десятичным числом, или числа, 
выходящего за пределы 0 - 255) должно выводиться соответствующе сообщение об ошибке.
*/

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

unsigned char Bit(const unsigned char n) { return 1 << n; }

signed short StrToByte(const char *p)
{
	signed short byte = 0;
	while (*p != '\0')
	{
		if ((*p >= '0') && (*p <= '9'))
		{
			byte = byte * 10 + (unsigned)*p - (unsigned) '0';
			if (byte > 255) return (-1);
		}
		else
			return (-1);
		p++;
	}
	return byte;
}

unsigned char FlipByte(const unsigned char byte)
{
	unsigned char result = 0;
	for (char i = 0; i < 8; i++)
	{
		if (byte & Bit(i)) result |= Bit(7 - i);
	}
	return result;
}

bool CheckArgsOk(const int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid argument count\n"
			<< "Usage: flipbyte <string>\n";
		return false;
	}
	else
		return true;
}

int main(int argc, char* argv[])
{
	if (CheckArgsOk(argc, &argv[0]))
	{
		signed short result = StrToByte(argv[1]);
		if (result < 0) 
		{
			cout << "Invalid argument. Permit only digit, value from 0 to 255\n";
			return 1;
		}
		else
		{
			unsigned short byte = FlipByte(result); // &0x00FF;
			cout << byte << "\n";
			return 0;
		}
	}
	else
		return 1;
}