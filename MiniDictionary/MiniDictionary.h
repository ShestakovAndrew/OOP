#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>

using WordTranslations = std::vector<std::string>;
using Dictionary = std::map<std::string, WordTranslations>;
static const std::string EXIT = "...";

void ArgumentsCountCheck(int argc);
std::string GetDictionaryFilePathFromArgv(int argc, char* argv[]);
bool IsEnglishWord(std::string const& word);
Dictionary ReadDictionaryFromFile(std::string const& filePath);
void StartDialogWithUser(Dictionary& dictionary, std::string const& dictionaryFilePath);
bool PrintFoundedTranslations(Dictionary const& dictionary, std::string const& lowerCaseString);
WordTranslations GetWordTranslations(Dictionary const& dictionary, std::string lowerCaseString);
WordTranslations GetRussianTranslation(Dictionary const& dictionary, std::string const& lowerCaseString);
WordTranslations GetEnglishTranslation(Dictionary const& dictionary, const std::string& lowerCaseString);
bool TranslationSaved(Dictionary& dictionary, std::string& userString);
void AddTranslationInDictionary(std::string userString, std::string userTranslation, Dictionary& dictionary);
void SaveChangesIfAllowed(Dictionary& dictionary, std::string const& dictionaryFileName);
bool Save—hangesToDictionaryFile(Dictionary const& dictionary, std::string const& fileName);