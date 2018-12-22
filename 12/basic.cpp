#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>

#define DESIRED_GENERATION 20

using namespace std;

int main() {
	ifstream ifs("input.txt");
	size_t rowLength;
	map<int, bool> currentGen, nextGen;
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
	for (size_t gen = 0; gen < DESIRED_GENERATION; gen++){
		short ruleId = 0;
		int minCurrent = currentGen.begin()->first, maxCurrent = currentGen.rbegin()->first;
		for (short i = 0; i < 5; i++)
			ruleId = ruleId * 2 + currentGen[minCurrent - 4 + i];
		nextGen[minCurrent - 2] = rules[ruleId];
		for (int i = minCurrent + 1; i < maxCurrent + 4; i++) {
			ruleId = ((ruleId * 2) % 32) + currentGen[i];
			nextGen[i - 2] = rules[ruleId];
		}
		currentGen = nextGen;
		nextGen.clear();
	}
	long int indexSum = 0;
	for (auto it : currentGen) {
		if ( it.second )
			indexSum += it.first;
	}
	cout<<indexSum<<endl;
	return 0;
}