#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


inline std::string parse_csv(std::string fileName) {
	std::ifstream file(fileName);

	if (!file.is_open()) {
		char errMsg[100];
		strerror_s(errMsg, sizeof(errMsg), errno);
		std::cerr << "Cannot open file " << fileName << ": " << errMsg << std::endl;
		return "";
	}

	std::string line;
	std::string file_contents;
	while (std::getline(file, line)) {
		file_contents += line;
		file_contents.push_back('\n');
	}

	file.close();
	return file_contents;
}