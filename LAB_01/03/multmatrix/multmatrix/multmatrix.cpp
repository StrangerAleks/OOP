#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

bool check_args_ok(const int argc, char* argv[], ifstream& inputFile, ofstream& outputFile)
{
	if (argc != 3)
	{
		cout << "Invalid argument count\n"
			<< "Usage: multmatrix.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return false;
	}

	inputFile.open(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return false;
	}

	outputFile.open(argv[2]);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return false;
	}
	return true;

}

int main(int argc, char* argv[])
{
	ifstream inputFile;
	ofstream outputFile;

	if (check_args_ok(argc, &argv[0], inputFile, outputFile))
	{
		string search = argv[3];
		string replace = argv[4];
		if (search != replace) CopyFileWithReplace(inputFile, outputFile, search, replace);

		if (!outputFile.flush()) // Если не удалось сбросить данные на диск
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}
		else
			return 0;
	}
	else
		return 1;
}