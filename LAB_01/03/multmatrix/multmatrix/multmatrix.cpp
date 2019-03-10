/*
multmatrix.exe выполняет перемножение двух матриц размером 3*3, коэффициенты заданы во входных файлах
Выводит результат умножения в стандартный поток вывода. Формат командной строки приложения:
multmatrix.exe <matrix file1> <matrix file2>
Коэффициенты матриц задаются в текстовых файлах в трех строках по 3 элемента.
Коэффициенты результирующей матрицы выводятся с точностью до 3 знаков после запятой.
*/

#include "pch.h"
#include "multmatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const unsigned char MATRIX_SIZE = 3; // размер матрицы

struct s_matrix
{
	double items[MATRIX_SIZE][MATRIX_SIZE];
};

struct s_matrixRow
{
	double items[MATRIX_SIZE];
};

bool CheckArgsOk(const int argc, char* argv[], ifstream& matrixFile1, ifstream& matrixFile2)
{
	if (argc != 3)
	{
		cout << "Invalid argument count\n"
			<< "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
		return false;
	}

	matrixFile1.open(argv[1]);
	if (!matrixFile1.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return false;
	}

	matrixFile2.open(argv[2]);
	if (!matrixFile1.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return false;
	}
	return true;
}

bool ParseStringToRow(istream& input, s_matrixRow& mRow)
{
	string line;
	char ch;
	unsigned char rowCnt = 0;
	double tmpDouble = 0;
	char doubleState = STR_WAIT_SIGN;
	double power = 0.1;
	bool pozitive = true;

	if (getline(input, line))
	{
		for (unsigned int i = 0; i <= line.length(); i++)
		{
			ch = line[i];
			switch (ch)
			{
			case ' ': case '\t': case 0:
				if (doubleState != STR_WAIT_SIGN)
				{
					if (rowCnt < MATRIX_SIZE)
					{
						if (pozitive) mRow.items[rowCnt++] = tmpDouble;
						else mRow.items[rowCnt++] = (-1) * tmpDouble;
						tmpDouble = 0;
						doubleState = STR_WAIT_SIGN;
						power = 0.1;
						pozitive = true;
						if (ch == 0) return true;
					}
					else return true;
				}
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				switch (doubleState)
				{
				case STR_WAIT_SIGN:
					doubleState = STR_DIGIT_BEFORE_DOT;
				case STR_DIGIT_BEFORE_DOT:
					tmpDouble = tmpDouble * 10 + (unsigned)ch - (unsigned) '0';
					break;
				case STR_DOT:
					doubleState = STR_DIGIT_AFTER_DOT;
				case STR_DIGIT_AFTER_DOT:
					tmpDouble += ((unsigned)ch - (unsigned) '0') * power;
					power /= 10;
				}				
				break;
			case '.': 
				if (doubleState == STR_DIGIT_BEFORE_DOT) doubleState = STR_DOT;
				else return false;
				break;
			case '-':
				if (doubleState == STR_WAIT_SIGN) pozitive = false;
				else return false;
				break;
			default:
				return false;
			}
		} // while (input.get(ch))
		return true;
	}
	else
	{
		return false;
	}	
}

bool ReadMatrix(istream& input, s_matrix& matrix)
{
	s_matrixRow row;
	for (unsigned char i = 0; i < MATRIX_SIZE; i++)
	{
		if (ParseStringToRow(input, row))
		{
//			cout << "Parse OK " << i << "\n"; // DEBUG
			for (unsigned char j = 0; j < MATRIX_SIZE; j++)
			{
				matrix.items[i][j] = row.items[j];
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

s_matrix Multiply(const s_matrix& mat1, const s_matrix& mat2)
{
	s_matrix matResult;
	char row, column;
	for (row = 0; row < MATRIX_SIZE; row++)
	{
		for (column = 0; column < MATRIX_SIZE; column++)
		{
			matResult.items[row][column] = mat1.items[row][column] * mat2.items[column][row];
		}		
	}
	
	return matResult;
}

void PrintMatrix(const s_matrix& matrix)
{
	char row, column;
	for (row = 0; row < MATRIX_SIZE; row++)
	{
		for (column = 0; column < MATRIX_SIZE; column++)
		{
			cout << fixed << setprecision(3) << matrix.items[row][column] << "\t";
		}
		cout << "\n";
	}	
}



int main(int argc, char* argv[])
{
	ifstream matrixFile1;
	ifstream matrixFile2;

	if (CheckArgsOk(argc, &argv[0], matrixFile1, matrixFile2))
	{
		s_matrix matrix1, matrix2, matrixMult;
		if (ReadMatrix(matrixFile1, matrix1) && ReadMatrix(matrixFile2, matrix2))
		{
			matrixMult = Multiply(matrix1, matrix2);
			PrintMatrix(matrixMult);
		}
		else
		{
			return 1;
		}		
	}
	else
	{
		return 1;
	}
}