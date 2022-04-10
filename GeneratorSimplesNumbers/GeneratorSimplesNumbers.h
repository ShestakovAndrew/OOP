#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

std::set<uint64_t> GeneratePrimeNumbersSet(size_t const& upperBound);

uint64_t GetUpperBound(int argc, const char* argv[]);

void CheckArguments(int argc, const char* argv[]);

void DisplayPrimeNumbers(std::set<uint64_t> const& primeNumbers);