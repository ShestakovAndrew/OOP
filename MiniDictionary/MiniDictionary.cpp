#include "MiniDictionary.h"

void ArgumentsCountCheck(int argc)
{
	if (argc > 2)
	{
		std::cout << "Usage: MiniDictionary.exe <Dictionary file>" << std::endl
			<< "\t<Dictionary file> - <optional> file path to dictionary." << std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}
std::string GetDictionaryFilePathFromArgv(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);

	return (argc == 1) ? "DefaultDictionary.txt" : argv[1];
}
bool IsEnglishWord(std::string const& word)
{
	for (const char& symbol : word)
	{
		if ((symbol >= 'A' and symbol <= 'Z') or
			(symbol >= 'a' and symbol <= 'z'))
		{
			return true;
		}
	}
	return false;
}
WordTranslations Split(std::string& translations, std::string const& separator)
{
	WordTranslations wordTranslations;
	std::string translation;
	size_t endFind;

	while ((endFind = translations.find(separator)) != std::string::npos)
	{
		translation = translations.substr(0, endFind);
		translations.erase(0, endFind + separator.length());
		wordTranslations.push_back(translation);
	}
	wordTranslations.push_back(translations);

	return wordTranslations;
}
Dictionary ReadDictionaryFromFile(std::string const& filePath)
{
	std::ifstream dictionaryFile(filePath);
	Dictionary dictionary;

	if (!dictionaryFile.is_open()) return dictionary;

	std::string key, value, fileLine;

	while (std::getline(dictionaryFile, fileLine))
	{
		size_t lenEnWord = fileLine.find(':');
		std::string enWord = fileLine.substr(0, lenEnWord);
		fileLine.erase(0, lenEnWord + 2);
		dictionary[enWord] = Split(fileLine, ", ");
	}

	return dictionary;
}
void StartDialogWithUser(Dictionary& dictionary, std::string const& dictionaryFilePath)
{
	std::string userString;
	bool isDictionaryChanged = false;

	std::cout << "Введите слово для перевода. Для выхода введите: '...'" << std::endl;

	while (std::getline(std::cin, userString))
	{
		if (userString == EXIT) break;

		if (!PrintFoundedTranslations(dictionary, userString) and TranslationSaved(dictionary, userString))
		{
			isDictionaryChanged = true;
		}
	}

	if (isDictionaryChanged)
	{
		SaveChangesIfAllowed(dictionary, dictionaryFilePath);
	}
}
bool PrintFoundedTranslations(Dictionary const& dictionary, std::string const& userString)
{
	WordTranslations wordTranslations = GetWordTranslations(dictionary, userString);

	if (wordTranslations.empty()) return false;

	for (auto it = wordTranslations.begin(); it != wordTranslations.end(); it++)
	{
		std::cout << *it;
		if (it != wordTranslations.end() - 1) std::cout << ", ";
	}

	std::cout << std::endl;
	return true;
}
WordTranslations GetWordTranslations(Dictionary const& dictionary, std::string userString)
{
	boost::algorithm::to_lower(userString, std::locale{ "Russian" });

	return IsEnglishWord(userString) ? GetRussianTranslation(dictionary, userString)
		: GetEnglishTranslation(dictionary, userString);
}
WordTranslations GetRussianTranslation(Dictionary const& dictionary, std::string const& lowerCaseString)
{
	if (auto it = dictionary.find(lowerCaseString); it != dictionary.end())
	{
		return it->second;
	}
	return WordTranslations();
}
WordTranslations GetEnglishTranslation(Dictionary const& dictionary, const std::string& lowerCaseString)
{
	for (const auto& [word, wordsTranslation] : dictionary)
	{
		for (const auto& wordTranslation : wordsTranslation)
		{
			if (wordTranslation == lowerCaseString)
			{
				return { word };
			}
		}
	}

	return WordTranslations();
}
bool TranslationSaved(Dictionary& dictionary, std::string& userString)
{
	std::string userTranslation;
	std::cout << "Неизвестное слово '" << userString << "'. Введите перевод или пустую строку для отказа." << std::endl;
	std::getline(std::cin, userTranslation);

	if (userTranslation.empty())
	{
		std::cout << "Слово '" << userString << "' проигнорировано." << std::endl;
		return false;
	}
	
	AddTranslationInDictionary(userString, userTranslation, dictionary);
	std::cout << "Слово '" << userString << "' сохранено в словаре как '" << userTranslation << "'." << std::endl;
	return true;
}
void AddTranslationInDictionary(std::string userString, std::string userTranslation, Dictionary& dictionary)
{
	if (!IsEnglishWord(userString))
	{
		std::swap(userString, userTranslation);
	}
	boost::algorithm::to_lower(userString, std::locale{ "Russian" });
	dictionary[userString].push_back(userTranslation);
}
void SaveChangesIfAllowed(Dictionary& dictionary, std::string const& dictionaryFileName)
{
	std::string userString;
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;

	std::getline(std::cin, userString);

	if ((userString == "y" or userString == "Y") and SaveСhangesToDictionaryFile(dictionary, dictionaryFileName))
	{
		std::cout << "Изменения сохранены. До свидания";
	}
	else
	{
		std::cout << "Изменения не были сохранены. До свидания.";
	}
}
bool SaveСhangesToDictionaryFile(Dictionary const& dictionary, std::string const& fileName)
{
	std::ofstream dictionaryFile(fileName);

	if (!dictionaryFile.is_open())
	{
		std::cout << "Файл для сохранения словаря не был открыт." << std::endl;
		return false;
	}

	for (auto const& [word, translation] : dictionary)
	{
		dictionaryFile << word << ": ";
		for (auto it = translation.begin(); it != translation.end(); it++)
		{
			dictionaryFile << *it;
			if (it != translation.end() - 1)
			{
				dictionaryFile << ", ";
			}
		}
		dictionaryFile << std::endl;
	}

	return true;
}