#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <string>

using namespace std;
using FindStringCallback = function<void(int lineIndex, const string& line, size_t foundPos)>;

bool FindStringInStream(
	istream& fileContent,
	const string& needle,
	const FindStringCallback& callback = FindStringCallback())
{
	//зависает функция 
	string line;
	bool found = false;
	for (int lineIndex = 1; getline(fileContent, line); ++lineIndex)
	{
		size_t pos;
		while ((pos = line.find(needle)) != string::npos)
		{
			found = true;
			if (callback) callback(lineIndex, line, pos);
		}
	}
	return found;
}

void PrintFoundLineIndex(int lineIndex, string const& line, size_t foundPos)
{
	cout << "lineIndex: " << lineIndex << "; Line: " << line << "; foundPos: "<< foundPos << ";" << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count." << endl
			 << "Usage: findtext.exe <file name> <text to search>" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.is_open())
	{
		cout << "Failed to open " << argv[1] << " for searching." << endl;
		return 1;
	}
	//можно сразу передать файл
	stringstream buffer;
	buffer << file.rdbuf();

	file.close();

	if (!FindStringInStream(buffer, argv[2], PrintFoundLineIndex))
	{
		cout << "Text not found." << endl;
		return 1;
	}

	buffer.clear();
	buffer.seekg(0, ios_base::beg);

	return 0;
}