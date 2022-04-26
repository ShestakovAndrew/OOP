#include "MiniDictionary.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::string dictionaryFilePath = GetDictionaryFilePathFromArgv(argc, argv);
		Dictionary dictionary = ReadDictionaryFromFile(dictionaryFilePath);
		StartDialogWithUser(dictionary, dictionaryFilePath);
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
}