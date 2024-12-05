#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../csvparser.h"


int totalDistBtwnLists (std::vector<int>& list_1, std::vector<int>& list_2) {
	/*
		- Both lists are of length n
		- Find smallest number in both lists, then compare distance
		- Sum up distances
	*/

	if (list_1.size() != list_2.size()) {
		std::cerr << "Lists must be of same length" << std::endl;
		return -1;
	}

	int dist = 0;

	std::sort(list_1.begin(), list_1.end());
	std::sort(list_2.begin(), list_2.end());

	for (int i = 0; i < list_1.size(); i++) {
		std::pair<int, int> result = std::minmax(list_1[i], list_2[i]);
		dist += result.second - result.first;
	}
	return dist;
}

int totalSimilarityBtwnLists(std::vector<int>& list_1, std::vector<int>& list_2) {
	/*
		- Both lists are of length n
		- Take # of appearances of left num for all of right num (how many times 4 is in list_2
		- Sum up similarities
	*/

	if (list_1.size() != list_2.size()) {
		std::cerr << "Lists must be of same length" << std::endl;
	}

	int similarity = 0;
	std::unordered_map<int, int> freq;

	for (int num : list_2) {
		freq[num]++;
	}

	for (int num : list_1) {
		similarity += num * freq[num];
	}

	return similarity;
}

int main ( void ) {
	std::string fileName = "inputs/day_1/distInput.txt"; 
	std::stringstream file_contents(parse_csv(fileName));

	std::string line;
	std::vector<int> num1, num2;

	// getting input (all list numbers) and sorting into respective vector.
	while (std::getline(file_contents, line)) {
		std::istringstream ss(line);
		int num;
		bool isNum1 = true;

		while (ss >> num) {
			if (isNum1) {
				num1.push_back(num);
			}
			else {
				num2.push_back(num);
			}
			isNum1 = !isNum1;
		}
	}

	int dist = totalDistBtwnLists(num1, num2);
	int sim = totalSimilarityBtwnLists(num1, num2);

	std::cout << "Total Distance between lists is " << dist << std::endl;
	std::cout << "Total Similarity between lists is " << sim << std::endl;

	return 0;
}