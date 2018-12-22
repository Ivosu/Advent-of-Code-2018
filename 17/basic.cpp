#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	ifstream ifs("input.txt");
	map<size_t, map<size_t, char>> board;
	char coord1, coord2;
	size_t coord1Val, coord2LVal, coord2UVal;
	size_t yMin = numeric_limits<size_t>::max(), yMax = 0;
	while(ifs) {
		ifs >> coord1;
		ifs.ignore();
		ifs >> coord1Val;
		ifs.ignore(2);
		ifs>>coord2;
		ifs.ignore();
		ifs>>coord2LVal;
		ifs.ignore(2);
		ifs>>coord2UVal;
		if (coord2 == 'y') {
			for (size_t y = coord2LVal; y <= coord2UVal; y++)
				board[coord1Val][y] = '#';
			yMax = max(yMax, coord2UVal);
			yMin = min(yMin, coord2LVal);
		} else {
			for (size_t x = coord2LVal; x <= coord2UVal; x++)
				board[x][coord1Val] = '#';
			yMax = max(yMax, coord1Val);
			yMin = max(yMin, coord1Val);
		}
	}
	deque<pair<size_t, size_t>> q;
	q.emplace_back(500, yMin - 1);
	size_t waterCount = 0;
	while(true) {
		auto currWater = q.front();
		auto xIt = board.find(currWater.first);
		if (xIt != board.end()) {
			auto yIt = board.find(currWater.second-1);
			if (yIt == board.end()){

			}
		}
	}
	return 0;
}