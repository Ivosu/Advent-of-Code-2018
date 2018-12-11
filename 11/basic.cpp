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
	int maxX, maxY = maxX = 0;
	for (size_t x = 0; x <298; x++){
		for (size_t y = 0; y < 298; y++){
			int fuelSum = 0;
			for (size_t i = 0; i < 3; i++)
				for (size_t j = 0; j < 3; j++)
					fuelSum += board[x+i][y+j];
			if (fuelSum > maxFuel){
				maxFuel = fuelSum;
				maxX = x;
				maxY = y;
			}
		}
	}
	cout<<board[maxX][maxY]<<" at "<<maxX<<","<<maxY<<endl;
	return 0;
}