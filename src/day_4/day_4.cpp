#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <array>
#include "../csvparser.h"

struct Direction {
	int dx, dy;
};

const std::array<Direction, 8> DIRECTIONS = { {
	{1, 0},  // RIGHT
	{-1, 0}, // LEFT
	{0, 1},  // DOWN
	{0, -1}, // UP
	{1, 1},  // DOWNRIGHT
	{1, -1}, // UPRIGHT
	{-1, -1},// UPLEFT
	{-1, 1}  // DOWNLEFT
} };

const std::array<Direction, 4> XDIRECTIONS = { {
	{1, 1},  // DOWNRIGHT
	{1, -1}, // UPRIGHT
	{-1, -1},// UPLEFT
	{-1, 1}  // DOWNLEFT
} };

std::vector<Direction> getValidDirectionsOfIndex(int x, int y, int sizeX, int sizeY, int wordlength) {
	std::vector<Direction> dirs;

	for (const auto& dir : DIRECTIONS) {
		int newX = x + (dir.dx * (wordlength - 1));
		int newY = y + (dir.dy * (wordlength - 1));
		if (newX >= 0 && newX < sizeX && newY >= 0 && newY < sizeY) {
			dirs.push_back(dir);
		}
	}

	return dirs;
}


int checkWordCount(const std::vector<std::string>& crossword, int x, int y, std::string& word) {
	std::vector<Direction> dirs = getValidDirectionsOfIndex(x, y, crossword[y].length(), crossword.size(), word.length());
	int words = 0;
	for (const auto& dir : dirs) {
		std::string found;

		for (int i = 0; i < word.length(); i++) {
			int newX = x + (dir.dx * i);
			int newY = y + (dir.dy * i);
			found += crossword[newY][newX];
		}
		if (found == word) words++;
	}

	return words;
}

int countNumOfWordInCrossword(std::vector<std::string>& crossword, std::string& word) {
	/*
		- Crossword is same length n x n
		- Find # of XMAS in crossword
			- Look at all 8 directions
	*/

	if (crossword.size() != crossword[0].length()) return 0;

	int xmas = 0;

	for (int y = 0; y < crossword.size(); y++) {
		for (int x = 0; x < crossword[y].length(); x++) {
			xmas += checkWordCount(crossword, x, y, word);
		}
	}

	return xmas;
}

/* DAY FOUR PART 2*/
bool directionsValid(int sizeX, int sizeY, int x, int y) {
	for (const auto& dir : XDIRECTIONS) {
		int newX = x + dir.dx;
		int newY = y + dir.dy;

		if (newX >= sizeX || newX < 0 || newY >= sizeY || newY < 0) return false;
	}
	return true;
}

bool isXword(std::vector<std::string>& crossword, int x, int y, std::string& word) {
	if (crossword[y][x] != 'A') return 0;
	if (!directionsValid(crossword[y].length(), crossword.size(), x, y)) return 0;

	std::vector<Direction> found_dirs;
	int halves = 0;
	for (const Direction& dir : XDIRECTIONS) {
		std::string found;
		for (int k = -1; k <= 1; k++) {
			int newX = x + (dir.dx * k);
			int newY = y + (dir.dy * k);
			found += crossword[newY][newX];
		}
		if (found == word || found == std::string(word.rbegin(), word.rend())) {
			if (std::find_if(found_dirs.begin(), found_dirs.end(), [dir](const Direction& dir1) {
					return (dir1.dx == -dir.dx && dir1.dy == -dir.dy);
				}) == found_dirs.end()) {
				halves++;

				if (halves >= 2) return 1;
			}
			found_dirs.push_back(dir);
		}
	}
	return 0;
}

int countNumOfXWordInCrossword(std::vector<std::string>& crossword, std::string& word) {
	/* 
		- Crossword is same length n x n
		- Find MAS in an X form (ex. MAS bottom left and MAS bottom right)
	*/

	int xmas = 0;

	for (int y = 0; y < crossword.size(); y++) {
		for (int x = 0; x < crossword[y].length(); x++) {
			xmas += isXword(crossword, x, y, word);
		}
	}
	return xmas;
}


int main( void ) {
	std::string fileName = "inputs/day_4_input.txt";
	std::stringstream file_contents(parse_csv(fileName));
	std::string target = "XMAS";
	std::string x_target = "MAS";

	std::vector<std::string> crossword;
	std::string line;

	// Create crossword (matrix of chars)
	while (std::getline(file_contents, line)) {
		crossword.push_back(line);
	}

	std::vector<std::string> small_test(crossword.begin(), crossword.begin() + 20);

	int numXmas = countNumOfWordInCrossword(crossword, target);
	int numX = countNumOfXWordInCrossword(crossword, x_target);

	std::cout << "Number of XMAS in string: " << numXmas << std::endl;
	std::cout << "Number of X-MAS in string: " << numX << std::endl;

	return 0;
}