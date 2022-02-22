#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
using FindStringCallback = function<void(size_t lineIndex, const string& line, size_t foundPos)>;

ifstream GetStreamFromFile(const char* filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		throw invalid_argument("Failed to open file for searching.");
	}
	return file;
}

bool FindStringInFile(
	const char* file,
	const string& needle,
	const FindStringCallback& callback = FindStringCallback())
{
	ifstream fileStream = GetStreamFromFile(file);
	string line;
	bool found = false;
	for (size_t lineIndex = 1; getline(fileStream, line); lineIndex++)
	{
		size_t pos = line.find(needle, 0);
		while (pos != string::npos)
		{
			found = true;
			if (callback) callback(lineIndex, line, pos);
			pos = line.find(needle, pos + 1);
		}
	}
	return found;
} 

void PrintFoundLineIndex(size_t lineIndex, string const& line, size_t foundPos)
{
	cout << "lineIndex: " << lineIndex << ";" << " foundPos: " << foundPos << ";" << " line: " << line << endl;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");

	try
	{
		if (argc != 3)
		{
			cout << "Invalid arguments count." << endl
				<< "Usage: findtext.exe <file name> <text to search>" << endl;
			return 1;
		}

		if (!FindStringInFile(argv[1] /*file*/, argv[2] /*NeedToFind*/, PrintFoundLineIndex))
		{
			cout << "Text not found." << endl;
			return 1;
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}