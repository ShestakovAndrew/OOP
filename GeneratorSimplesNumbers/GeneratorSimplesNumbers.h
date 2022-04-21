#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

std::set<size_t> GeneratePrimeNumbersSet(int upperBound);

int GetUpperBound(int argc, const char* argv[]);

void CheckArguments(int argc, const char* argv[]);

void DisplayPrimeNumbers(std::set<size_t> const& primeNumbers);