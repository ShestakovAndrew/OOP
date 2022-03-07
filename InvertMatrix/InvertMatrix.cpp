#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <windows.h>

namespace
{
	using Matrix = std::vector<std::vector<double>>;	
}

void CheckArguments(int argc);
std::ifstream GetFileStream(std::string const& filePath);
Matrix FillMatrix(std::ifstream& fileContent);
Matrix ReadMatrixFromFile(std::string const& filePath);
void PrintMatrix(Matrix const& matrix);
Matrix InvertMatrix(Matrix const& matrix);
void StartInvertMatrix(int argc, char* argv[]);
Matrix MatrixTranspose(Matrix const& matrix);
Matrix MinorByElementInMatrix(Matrix const& matrix, size_t elemRow, size_t elemCol);
double MatrixDeterminant(Matrix const& matrix);
double MinorOfElementInMatrix(Matrix const& matrix, size_t elemRow, size_t elemCol);
Matrix MatrixAlgebraicAdditions(Matrix const& matrix);
Matrix InvertMatrix(Matrix const& matrix);

void CheckArguments(int argc)
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count." << std::endl
			<< "\tUsage: findtext.exe <matrix filePath>" << std::endl
			<< "\t\t<matrix filePath> - path to file, where matrix coefficients are stored." << std::endl;
		throw std::invalid_argument("Invalid arguments count.");
	}
}
std::ifstream GetFileStream(std::string const& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for searching.");
	}
	return file;
}
Matrix FillMatrix(std::ifstream& fileContent)
{
	Matrix result;
	std::string line;
	while (std::getline(fileContent, line)) 
	{
		std::istringstream iss { line };
		std::vector<double> tempv;	
		double element;

		while (iss >> element)
		{
			tempv.push_back(element);
		}
		result.push_back(tempv);
	}
	fileContent.close();
	return result;
}
Matrix ReadMatrixFromFile(std::string const& filePath)
{
	std::ifstream fileStream = GetFileStream(filePath);
	return FillMatrix(fileStream);
}
void PrintMatrix(Matrix const& matrix)
{
	for (auto const& row : matrix)
	{
		for (auto const& element : row)
		{
			std::cout << std::fixed << std::setprecision(3) << element << "\t";
		}
		std::cout << std::endl;
	}
}
Matrix InvertMatrix(Matrix const& matrix)
{
	double determinant = MatrixDeterminant(matrix);

	if (determinant == 0)
	{
		throw std::logic_error("Inverse doesn't exist.");
	}

	Matrix matrixTranspose = MatrixTranspose(matrix);
	Matrix algebraicAdditionsMatrix = MatrixAlgebraicAdditions(matrixTranspose);
	Matrix InvertMatrix;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<double> rowMatrix;
		for (size_t j = 0; j < matrix.size(); j++)
		{
			rowMatrix.push_back(algebraicAdditionsMatrix[i][j] / determinant);
		}
		InvertMatrix.push_back(rowMatrix);
	}
	return InvertMatrix;
}
void StartInvertMatrix(int argc, char* argv[])
{
	CheckArguments(argc);
	Matrix matrix = ReadMatrixFromFile(argv[1]);
	Matrix invertMatrix = InvertMatrix(matrix);
	PrintMatrix(invertMatrix);
}
Matrix MatrixTranspose(Matrix const& matrix)
{
	Matrix result;
	for (size_t i = 0; i < matrix.size(); i++)
	{ 
		std::vector<double> rowMatrix;
		for (size_t j = 0; j < matrix.size(); j++)
		{
			rowMatrix.push_back(matrix[j][i]);
		}
		result.push_back(rowMatrix);
	}
	return result;
}
Matrix MinorByElementInMatrix(Matrix const& matrix, size_t elemRow, size_t elemCol)
{
	Matrix result;

	for (size_t row = 0; row < matrix.size(); row++)
	{
		std::vector<double> rowMatrix;
		for (size_t col = 0; col < matrix.size(); col++)
		{
			if (row != elemRow && col != elemCol)
			{
				rowMatrix.push_back(matrix[row][col]);
			}
		}
		if (!rowMatrix.empty()) result.push_back(rowMatrix);
	}
	return result;
}
double MatrixDeterminant(Matrix const& matrix)
{
	if (matrix.size() == 2)
	{
		return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	}

	double determinate = 0;
	int8_t sign = 1;

	for (size_t col = 0; col != matrix.size(); col++)
	{
		Matrix minor = MinorByElementInMatrix(matrix, 0, col);
		sign = (((0 + col) % 2) == 0) ? 1 : -1;
		determinate += sign * matrix[0][col] * MatrixDeterminant(minor);
	}

	return determinate;
}
double MinorOfElementInMatrix(Matrix const& matrix, size_t elemRow, size_t elemCol)
{
	Matrix minorMatrix = MinorByElementInMatrix(matrix, elemRow, elemCol);
	return MatrixDeterminant(minorMatrix);
}
Matrix MatrixAlgebraicAdditions(Matrix const& matrix)
{
	Matrix result;
	int8_t sign = 1;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<double> col;
		for (size_t j = 0; j < matrix.size(); j++)
		{
			sign = ((i + j) % 2 == 0) ? 1 : -1;
			col.push_back(sign * MinorOfElementInMatrix(matrix, i, j));
		}
		result.push_back(col);
	}
	return result;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		StartInvertMatrix(argc, argv);
	}
	catch (std::logic_error const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}