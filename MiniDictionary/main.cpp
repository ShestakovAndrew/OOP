#include "MiniDictionary.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::string dictionaryFilePath = GetDictionaryFilePathFromArgv(argc, argv);
		Dictionary dictionary = ReadDictionaryFromFile(dictionaryFilePath);

		std::string userString;
		if (StartDialogWithUser(dictionary))
		{
			std::getline(std::cin, userString);
			CheckForSavingChanges(dictionary, dictionaryFilePath, userString);
		}
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
}