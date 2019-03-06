#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

unsigned char BIT(const unsigned char N) {return 1 << N;}

signed short strToByte(const char *p)
{
	signed short Byte = 0;
	while (*p != '\0')
	{
		if ((*p >= '0') && (*p <= '9'))
		{
			Byte = Byte * 10 + (unsigned)*p - (unsigned) '0';
			if (Byte > 255) return (-1);
		}
		else
			return (-1);
		p++;
	}
	return Byte;
}

unsigned char flipbyte(const unsigned char byte)
{
	unsigned char result = 0;
	for (char i = 0; i < 8; i++)
	{
		if (byte & BIT(i)) result |= BIT(7 - i);
	}
	return result;
}

bool check_args_ok(const int argc, char* argv[])
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
	if (check_args_ok(argc, &argv[0]))
	{
		signed short result = strToByte(argv[1]);
		if (result < 0)
			return 1;
		else
		{
			unsigned short byte = flipbyte(result); // &0x00FF;
			cout << byte;
			return 0;
		}
	}
	else
		return 1;
}