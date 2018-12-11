#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>

#define SERIAL_NUMBER 5791

using namespace std;

int getPowerLevel(int x, int y) {
	int rackId = x + 10;
	int powerLevel = rackId * y + SERIAL_NUMBER;
	powerLevel *= rackId;
	powerLevel = (powerLevel % 1000) / 100;
	return powerLevel - 5;
}

int main() {
	array<array<int, 300>, 300> board;
	for (size_t x = 0; x < 300; x++){
		for (size_t y = 0; y < 300; y++){
			board[x][y] = getPowerLevel(x, y);
		}
	}
	int maxFuel = numeric_limits<int>::min();
	size_t maxX, maxY, maxSize = maxY = maxX = 0;
	for (size_t x = 0; x <300; x++){
		for (size_t y = 0; y < 300; y++){
			for (size_t squareSize = 1; squareSize < 300 - max(x, y); squareSize ++) {
				int fuelSum = 0;
				for (size_t i = 0; i < squareSize; i++)
					for (size_t j = 0; j < squareSize; j++)
						fuelSum += board[x + i][y + j];
				if (fuelSum > maxFuel) {
					maxFuel = fuelSum;
					maxX = x;
					maxY = y;
					maxSize = squareSize;
				}
			}
		}
	}
	cout<<board[maxX][maxY]<<" at "<<maxX<<","<<maxY<<","<<maxSize<<endl;
	return 0;
}