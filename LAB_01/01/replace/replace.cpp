/* Программа replace.exe делает замену всех вхождений подстроки в текстовом файле на другую строку, 
и записывает результат в выходной файл (отличный от входного).
Формат командной строки: replace.exe <input file> <output file> <search string> <replace string>
Программа корректно должна обрабатывать ситуацию, когда длина искомой строки равна нулю. 
В этом случае замены символов производиться не должно. 
Также корректно должна обрабатываться ситуация с многократным вхождением искомой строки
в строку-заменитель (например, замена строки «ма» на «мама» не должна приводить к зацикливанию).
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool CheckArgsOk(const int argc, char* argv[], ifstream& inputFile, ofstream& outputFile)
{
	if (argc != 5)
	{
		cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
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

string ReplaceString(const string& subject,
	const string& searchString, const string& replacementString)
{
	size_t pos = 0;
	string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(istream& input, ostream& output,
	const string& searchString, const string& replacementString)
{
	string line;

	while (getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	ifstream inputFile;
	ofstream outputFile;

	if (CheckArgsOk(argc, &argv[0], inputFile, outputFile))
	{
		string search = argv[3];
		string replace = argv[4];
		if (search != replace) CopyFileWithReplace(inputFile, outputFile, search, replace);

		if (!outputFile.flush())
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