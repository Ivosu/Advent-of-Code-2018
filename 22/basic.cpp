#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

enum floorType {
	rocky = 0, wet = 1, narrow = 2
};

unsigned long getErosionLevel(unsigned long geologicIndex, unsigned long depth) {
	return (geologicIndex + depth)%20183;
}

floorType getFloorType(unsigned long erosionLevel) {
	return floorType(erosionLevel%3);
}

int main() {
	ifstream ifs("input.txt");
	if (!ifs)
		return 1;
	unsigned long depth;
	unsigned long x = 0, y = 0;
	ifs.ignore(6);
	ifs>>depth;
	ifs.ignore(8);
	ifs>>x;
	ifs.ignore();
	ifs>>y;
	if (!ifs) {
		return 1;
	}
	vector<vector<floorType>> floorTypes(x+1);
	vector<vector<unsigned long>> erosionLevels(x+1);
	for (size_t i = 0; i <= x; i++){
		erosionLevels[i] = vector<unsigned long>(y+1);
		floorTypes[i] = vector<floorType>(y+1);
	}
	erosionLevels[0][0] = getErosionLevel(0, depth);
	for (size_t i = 1; i <= x; i++){
		erosionLevels[i][0] = getErosionLevel(i*16807, depth);
	}
	for (size_t j = 1; j < y; j++){
		erosionLevels[0][j] = getErosionLevel(j*48271, depth);
		for (size_t i = 1; i <= x; i++) {
			erosionLevels[i][j] = getErosionLevel(erosionLevels[i-1][j]*erosionLevels[i][j-1], depth);
		}
	}
	erosionLevels[0][y] = getErosionLevel(y*48271, depth);
	for (size_t i = 1; i < x; i++){
		erosionLevels[i][y] = getErosionLevel(erosionLevels[i-1][y]*erosionLevels[i][y-1], depth);
	}
	erosionLevels[x][y] = getErosionLevel(0, depth);
	unsigned long sum = 0;
	for (size_t j = 0; j <= y; j++) {
		for (size_t i = 0; i <= x; i++) {
			sum += floorTypes[i][j] = getFloorType(erosionLevels[i][j]);
			//cout << (floorTypes[i][j] == 0 ? "." : (floorTypes[i][j] == 1 ? "=" : "|"));
		}
		//cout<<endl;
	}
	cout<<sum<<endl;
	return 0;
}