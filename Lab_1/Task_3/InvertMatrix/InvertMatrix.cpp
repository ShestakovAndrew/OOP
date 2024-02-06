#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <format>
#include <algorithm>

namespace
{
	using Matrix = std::vector<std::vector<double>>;	
}

void PrintMatrix(Matrix const& matrix)
{
	for (auto const& row : matrix)
	{
		for (auto const& element : row)
		{
			std::cout << std::fixed << std::setprecision(3) << element << " ";
		}
		std::cout << std::endl;
	}
}

double MatrixDeterminant(Matrix matrix)
{
	double determinant = 1.0;

	for (size_t row = 0; row < matrix.size(); row++) 
	{
		size_t pivot = row;
		for (size_t col = row + 1; col < matrix.size(); col++)
		{
			if (abs(matrix[col][row]) > abs(matrix[pivot][row]))
			{
				pivot = col;
			}
		}

		if (pivot != row)
		{
			std::swap(matrix[row], matrix[pivot]);
			determinant *= -1;
		}

		if (matrix[row][row] == 0)
		{
			return 0;
		}

		determinant *= matrix[row][row];

		for (size_t col = row + 1; col < matrix.size(); col++)
		{
			double factor = matrix[col][row] / matrix[row][row];
			for (size_t k = row + 1; k < matrix.size(); k++)
			{
				matrix[col][k] -= factor * matrix[row][k];
			}
		}
	}

	return determinant;
}

void AddMatrixExtension(Matrix& matrix, size_t order)
{
	for (size_t row = 0; row < order; row++)
	{
		for (size_t col = 0; col < order; col++)
		{
			matrix[row].push_back(col == row);
		}
	}
}

void RemoveMatrixExtension(Matrix& matrix, size_t order)
{
	for (size_t row = 0; row < order; row++)
	{
		matrix[row].erase(matrix[row].begin(), matrix[row].begin() + order);
	}
}

void BasicTransformations(Matrix& matrix, size_t order)
{
	double temp;

	for (size_t row = 0; row < order; row++)
	{
		for (size_t col = 0; col < order; col++)
		{
			if (col != row)
			{
				temp = (matrix[col][row] / matrix[row][row]);
				for (size_t k = 0; k < 2 * order; k++)
				{
					matrix[col][k] -= matrix[row][k] * temp;
				}
			}
			else
			{
				temp = matrix[row][row];
				for (size_t k = 0; k < 2 * order; k++)
				{
					matrix[row][k] /= temp;
				}
			}
		}
	}
}

void InvertMatrix(Matrix& matrix)
{
	size_t order = matrix.size();

	AddMatrixExtension(matrix, order);
	BasicTransformations(matrix, order);
	RemoveMatrixExtension(matrix, order);
}

bool IsMatrixCoefficient(char ch)
{
	return std::isdigit(ch) || (ch == '.') || (ch == '-');
}

std::vector<double> GetMatrixCoefficientsFromLine(std::string const& rowMatrix)
{
	std::vector<double> result;
	std::istringstream iss{ rowMatrix };
	std::string coefficientStr;

	while (iss >> coefficientStr)
	{
		if (!std::all_of(coefficientStr.begin(), coefficientStr.end(), IsMatrixCoefficient))
		{
			throw std::invalid_argument("Incorrect matrix coefficient input.");
		}
		result.push_back(std::stod(coefficientStr));
	}

	return result;
}

Matrix GetMatrixFromStream(std::istream& stream)
{
	Matrix result;
	std::string line;

	while (std::getline(stream, line))
	{
		result.push_back(GetMatrixCoefficientsFromLine(line));
	}

	return result;
}

std::ifstream GetFileStream(std::string const& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` matrix file.", filePath)
		);
	}
	return std::move(file);
}

void ValidateMatrix(Matrix const& matrix)
{
	if (matrix.empty())
	{
		throw std::length_error("Matrix is empty.");
	}

	if (matrix.size() == 1)
	{
		throw std::length_error("Matrix should be minimum 2x2.");
	}

	for (size_t i = 0; i != matrix.size(); i++)
	{
		if (matrix.size() != matrix[i].size())
		{
			throw std::length_error("Matrix is not square.");
		}
	}

	if (MatrixDeterminant(matrix) == 0)
	{
		throw std::invalid_argument("Inverse doesn't exist.");
	}
}

void ValidateArgumentsCount(int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: invertmatrix.exe <matrix file>\n"
			"\t<matrix filePath> - path to file, with matrix coefficients.\n\n"
			"Invalid arguments count."
		);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);

		std::ifstream fileStream = GetFileStream(argv[1]);
		Matrix matrix = GetMatrixFromStream(fileStream);

		ValidateMatrix(matrix);
		InvertMatrix(matrix);

		PrintMatrix(matrix);
	}
	catch (std::logic_error const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}