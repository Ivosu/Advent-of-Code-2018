#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>

#define DESIRED_GENERATION 50000000000

using namespace std;

int main() {
	ifstream ifs("input.txt");
	size_t rowLength;
	map<ssize_t, bool> currentGen, nextGen;
	ifs.ignore(15);
	{
		string initialRow;
		getline(ifs, initialRow);
		rowLength = initialRow.length();
		for (size_t i = 0; i < rowLength; i++)
			if (initialRow[i] == '#')
				currentGen[i] = true;
	}
	array<bool, 32> rules = { false };
	ifs.ignore();
	while(ifs.peek() != EOF){
		short ruleId = 0;
		char tmp;
		for (short i = 0; i < 5; i++){
			ifs>>tmp;
			ruleId = ruleId * 2 +(tmp == '#' ? 1 : 0);
		}
		ifs.ignore(4);
		ifs>>tmp;
		rules[ruleId] = tmp == '#';
		ifs.ignore();
	}
	ssize_t lastIndexSum = 0;
	ssize_t indexSum = 0;
	ssize_t lastDiff = 0;
	ssize_t diff = 0;
	size_t gen = 0;
	for (; gen < DESIRED_GENERATION; gen++){
		short ruleId = 0;
		ssize_t minCurrent = currentGen.begin()->first, maxCurrent = currentGen.rbegin()->first;
		for (short i = 0; i < 5; i++)
			ruleId = ruleId * 2 + currentGen[minCurrent - 4 + i];
		nextGen[minCurrent - 2] = rules[ruleId];
		for (ssize_t i = minCurrent + 1; i < maxCurrent + 4; i++) {
			ruleId = ((ruleId * 2) % 32) + currentGen[i];
			nextGen[i - 2] = rules[ruleId];
		}
		currentGen = nextGen;
		nextGen.clear();
		lastIndexSum = indexSum;
		indexSum = 0;
		for (auto it : currentGen) {
			if ( it.second )
				indexSum += it.first;
		}
		lastDiff = diff;
		diff = indexSum - lastIndexSum;
		if (lastDiff == diff)
			break;
	}
	if (gen != DESIRED_GENERATION)
		cout<< indexSum + (DESIRED_GENERATION - (gen + 1)) * (diff)<<endl;
	else
		cout<< indexSum<<endl;
	return 0;
}