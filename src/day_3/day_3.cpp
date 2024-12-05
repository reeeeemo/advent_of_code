#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include "../csvparser.h"

int getTotalMultiplied(std::string fileData) {
	std::regex pattern("mul\\((\\d+),(\\d+)\\)");
	int value = 0;

	auto begin = std::sregex_iterator(fileData.begin(), fileData.end(), pattern);
	auto end = std::sregex_iterator();

	for (std::sregex_iterator i = begin; i != end; ++i) {
		std::smatch match = *i;

		value += (std::stoi(match[1]) * std::stoi(match[2]));
	}

	return value;
}

int getTotalMultipliedConditional(std::string fileData) {
	std::regex pattern("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");
	int value = 0;

	auto begin = std::sregex_iterator(fileData.begin(), fileData.end(), pattern);
	auto end = std::sregex_iterator();

	bool doMul = true;

	for (std::sregex_iterator i = begin; i != end; ++i) {
		std::smatch match = *i;
		
		if (match.str() == "do()") {
			doMul = true;
			continue;
		}
		if (match.str() == "don't()") {
			doMul = false;
			continue;
		}

		if (doMul) {
			value += (std::stoi(match[1]) * std::stoi(match[2]));
		}
	}

	return value;
}

int main(void) {
	std::string fileName = "inputs/day_3_input.txt";
	std::string data = parse_csv(fileName);

	int totalMulti = getTotalMultiplied(data);
	int totalMultiConditional = getTotalMultipliedConditional(data);

	std::cout << "Total Multiplied Number: " << totalMulti << std::endl;
	std::cout << "Total Multipled Number w/Conditional Args: " << totalMultiConditional << std::endl;

	return 0;
}