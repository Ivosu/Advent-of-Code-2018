#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>

using namespace std;

uint16_t registers[4];

uint16_t addr(uint16_t a, uint16_t b) {
	return registers[a] + registers[b];
}

uint16_t addi(uint16_t a, uint16_t b) {
	return registers[a] + b;
}

uint16_t multr(uint16_t a, uint16_t b) {
	return registers[a]*registers[b];
}

uint16_t multi(uint16_t a, uint16_t b) {
	return registers[a]*b;
}

uint16_t banr(uint16_t a, uint16_t b) {
	return registers[a]&registers[b];
}

uint16_t bani(uint16_t a, uint16_t b) {
	return registers[a]&b;
}

uint16_t borr(uint16_t a, uint16_t b) {
	return registers[a]|registers[b];
}

uint16_t bori(uint16_t a, uint16_t b) {
	return registers[a]|b;
}

uint16_t setr(uint16_t a, uint16_t b) {
	return registers[a];
}

uint16_t seti(uint16_t a, uint16_t b) {
	return a;
}

uint16_t gtrr(uint16_t a, uint16_t b) {
	return registers[a] > registers[b];
}

uint16_t gtir(uint16_t a, uint16_t b) {
	return a > registers[b];
}

uint16_t gtri(uint16_t a, uint16_t b) {
	return registers[a] > b;
}

uint16_t eqrr(uint16_t a, uint16_t b) {
	return registers[a] == registers[b];
}

uint16_t eqir(uint16_t a, uint16_t b) {
	return a == registers[b];
}

uint16_t eqri(uint16_t a, uint16_t b) {
	return registers[a] == b;
}

array<function<uint16_t(uint16_t, uint16_t)>, 16> allOperations;
map<uint16_t, set<uint16_t>> possibleOpCodes;

int main() {
	ifstream ifs("input.txt");
	allOperations = { addr, addi, multr, multi, banr, bani, borr, bori, setr, seti, gtrr, gtir, gtri, eqrr, eqir, eqri};
	string line;
	char tmp;
	uint16_t after[4];
	for (uint16_t i = 0; i < 16; i++)
		for (uint16_t j = 0; j < 16; j++)
			possibleOpCodes[i].insert(j);
	while(getline(ifs, line) && line.size() > 0){
		uint16_t op, a, b, c;
		stringstream ss(line.substr(9));
		ss>>registers[0]>>tmp>>registers[1]>>tmp>>registers[2]>>tmp>>registers[3];
		ifs>>op>>a>>b>>c;
		ifs.ignore();
		getline(ifs, line);
		ss = stringstream(line.substr(9));
		ss>>after[0]>>tmp>>after[1]>>tmp>>after[2]>>tmp>>after[3];
		ifs.ignore();
		uint16_t realResult = after[c];
		for (uint16_t option : possibleOpCodes[op]) {
			auto& operation = allOperations[option];
			uint16_t result = operation(a,b);
			if (result != realResult)
				possibleOpCodes[op].erase(option);
		}
	}
	for (uint16_t j = 0; j < 16; j++)
		for (uint16_t i = 0; i < 16; i++)
			if (possibleOpCodes[i].size() == 1)
				for (uint16_t k = 0; k < 16; k++) {
					if (k == i) continue;
					possibleOpCodes[k].erase(*possibleOpCodes[i].begin());
				}
	array<function<uint16_t(uint16_t, uint16_t)>, 16> operations;
	for (uint16_t i = 0; i < 16; i++)
		operations[i] = allOperations[*possibleOpCodes[i].begin()];
	registers[0] = registers[1] = registers[2] = registers[3] = 0;
	while(ifs) {
		uint16_t op, a, b, c;
		ifs>>op>>a>>b>>c;
		registers[c] = operations[op](a,b);
	}
	cout<<registers[0]<<endl;
	return 0;
}