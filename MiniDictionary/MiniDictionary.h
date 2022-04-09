#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>

#include <boost/algorithm/string.hpp>

namespace
{
	using Dictionary = std::multimap<std::string, std::string>;
	static const std::string EXIT = "...";
}

void ArgumentsCountCheck(int argc);

std::string GetDictionaryFilePathFromArgv(int argc, char* argv[]);

Dictionary ReadDictionaryFromFile(std::string const& filePath);

bool StartDialogWithUser(Dictionary& dictionary);

void FindWordInDictionary(Dictionary& dictionary, std::string const& userString, std::string& userTranslation, bool& isDictionaryChanged);

bool CheckUserTranslation(Dictionary& dictionary, std::string const& userString, std::string const& userTranslation);

void CheckForSavingChanges(Dictionary& dictionary, std::string const& dictionaryFileName, std::string& userString);

void OverwriteDictionaryFile(std::string const& fileName, Dictionary const& dictionary);