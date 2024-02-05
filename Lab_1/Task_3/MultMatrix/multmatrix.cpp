#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <iomanip>
#include <algorithm>

namespace
{
	using Matrix = std::vector<std::vector<double>>;

	const int MATRIX_SIZE = 3;
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

Matrix GetMatrixFromStream(std::ifstream& fileStream)
{
	Matrix result;
	std::string line;

	while (std::getline(fileStream, line))
	{
		result.push_back(GetMatrixCoefficientsFromLine(line));
	}

	fileStream.close();
	return result;
}

void ValidateArgumentsCounts(int argc)
{
	if (argc != 3)
	{
		throw std::invalid_argument(
			"Usage: multmatrix.exe <matrix file 1> <matrix file 2>\n"
			"\t<matrix file 1> - first path to file, with matrix coefficients.\n"
			"\t<matrix file 2> - second path to file, with matrix coefficients.\n\n"
			"Invalid arguments count."
		);
	}
}

Matrix MultiMatrix(Matrix const& firstMatrix, Matrix const& secondMatrix)
{
	Matrix result(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE));

	for (uint8_t i = 0; i < MATRIX_SIZE; ++i)
	{
		for (uint8_t j = 0; j < MATRIX_SIZE; ++j)
		{
			double sum = 0;
			for (uint8_t k = 0; k < MATRIX_SIZE; ++k)
			{
				sum += firstMatrix[i][k] * secondMatrix[k][j];
			}
			result[i][j] = sum;
		}
	}

	return result;
}

Matrix ValidateMatrix(Matrix const& matrix)
{
	if (matrix.empty())
	{
		throw std::length_error("Matrix is empty.");
	}

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		if ((matrix.size() != MATRIX_SIZE) || (matrix[i].size() != MATRIX_SIZE))
		{
			throw std::length_error("Matrix should be 3x3.");
		}
	}

	return matrix;
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCounts(argc);

		std::ifstream firstFileStream = GetFileStream(argv[1]);
		std::ifstream secondFileStream = GetFileStream(argv[2]);

		Matrix firstMatrix = ValidateMatrix(GetMatrixFromStream(firstFileStream));
		Matrix secondMatrix = ValidateMatrix(GetMatrixFromStream(secondFileStream));

		PrintMatrix(MultiMatrix(firstMatrix, secondMatrix));
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}

	return 0;
}