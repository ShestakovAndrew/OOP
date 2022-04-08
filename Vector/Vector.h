#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/lexical_cast.hpp>

void SetRealNumbersTo(std::vector<double>& realNumbers);

void AddMeanPositiveNumberForAllElementsIn(std::vector<double>& realNumbers);

void PrintRealNumbers(std::vector<double>& realNumbers);