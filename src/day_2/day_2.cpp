#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../csvparser.h"

bool isSafeData(std::vector<int>& vec) {
	bool is_increasing = vec[1] > vec[0];
	for (int i = 1; i < vec.size(); i++) {
		// Does adajent data differ by at least 1 and at most 3?
		int diff = abs(vec[i - 1] - vec[i]);
		if ((diff > 3 || diff == 0) || ((vec[i] > vec[i - 1]) != is_increasing)) {
			return false;
		}
	}
	return true;
}

int countSafeData(std::vector<std::vector<int>>& safetyData) {
	/* 
		- Each vector has an unknown length
		- Find if number is incrementing or decrementing
			- Must differ by at least 1 and at most 3
			- Has to be INCREASING or DECREASING, not both
	*/
	int safe = 0;
	for (auto& vec : safetyData) {
		if (vec.size() <= 1) {
			safe++;
			continue;
		}
		bool safe_data = true;
		bool is_increasing = vec[1] > vec[0];

		if (isSafeData(vec)) {
			safe++;
		}
	}

	return safe;
}


int countSafeDataWithRemovingLevel(std::vector<std::vector<int>>& safetyData) {
	/* 
		- Each vector has an unknown length
		- Find if number is incrementing or decrementing
			- Must differ by at least 1 and at most 3
			- Has to be INCREASING OR DECREASING, not both
			- If both are untrue, check if removing a level can make it true
	*/
	int safe = 0;
	for (auto& vec : safetyData) {
		if (vec.size() <= 1) {
			safe++;
			continue;
		}
		bool safe_data = false;
		bool is_increasing = vec[1] > vec[0];

		for (int i = 0; i < vec.size(); i++) {
			std::vector<int> temp;

			for (int j = 0; j < vec.size(); j++) {
				if (j != i) temp.push_back(vec[j]);
			}

			if (isSafeData(temp)) {
				safe_data = true;
				break;
			}
		}
		if (safe_data) safe++;
	}

	return safe;
}

int main( void ) {
	std::string fileName = "inputs/day_2/safetyInput.txt";
	std::stringstream file_contents(parse_csv(fileName));

	std::string line;
	std::vector<std::vector<int>> safetyLevels;

	// Get input and sorting into a matrix of info :O
	while (std::getline(file_contents, line)) {
		std::istringstream ss(line);
		int num;
		std::vector<int> curSafetyLevel;

		while (ss >> num) {
			curSafetyLevel.push_back(num);
		}
		safetyLevels.push_back(curSafetyLevel);
	}

	int safeData = countSafeData(safetyLevels);
	int safeDataWithRemovals = countSafeDataWithRemovingLevel(safetyLevels);

	std::cout << "Total Safe lists: " << safeData << std::endl;
	std::cout << "Total Safe lists w/removals: " << safeDataWithRemovals << std::endl;
}