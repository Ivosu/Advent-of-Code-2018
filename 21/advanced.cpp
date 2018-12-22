#include <utility>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;



unsigned long registers[6];

struct instruction {
	instruction(function<unsigned long(unsigned long, unsigned long)> op, unsigned long a, unsigned long b, unsigned long c) : op(move(op)), a(a), b(b), c(c) {}
	void execute() {
		registers[c] = op(a, b);
	}
	const function<unsigned long(unsigned long, unsigned long)> op;
	const unsigned long a, b, c;
};

unsigned long addr(unsigned long a, unsigned long b) {
	return registers[a] + registers[b];
}

unsigned long addi(unsigned long a, unsigned long b) {
	return registers[a] + b;
}

unsigned long mulr(unsigned long a, unsigned long b) {
	return registers[a]*registers[b];
}

unsigned long muli(unsigned long a, unsigned long b) {
	return registers[a]*b;
}

unsigned long banr(unsigned long a, unsigned long b) {
	return registers[a]&registers[b];
}

unsigned long bani(unsigned long a, unsigned long b) {
	return registers[a]&b;
}

unsigned long borr(unsigned long a, unsigned long b) {
	return registers[a]|registers[b];
}

unsigned long bori(unsigned long a, unsigned long b) {
	return registers[a]|b;
}

unsigned long setr(unsigned long a, unsigned long b) {
	return registers[a];
}

unsigned long seti(unsigned long a, unsigned long b) {
	return a;
}

unsigned long gtrr(unsigned long a, unsigned long b) {
	return registers[a] > registers[b];
}

unsigned long gtir(unsigned long a, unsigned long b) {
	return a > registers[b];
}

unsigned long gtri(unsigned long a, unsigned long b) {
	return registers[a] > b;
}

unsigned long eqrr(unsigned long a, unsigned long b) {
	return registers[a] == registers[b];
}

unsigned long eqir(unsigned long a, unsigned long b) {
	return a == registers[b];
}

unsigned long eqri(unsigned long a, unsigned long b) {
	return registers[a] == b;
}

int main() {
	map<string, function<unsigned long (unsigned long, unsigned long)>> ops = {
			{ "addi", addi},
			{ "addr", addr},
			{ "muli", muli},
			{ "mulr", mulr},
			{ "bani", bani},
			{ "banr", banr},
			{ "bori", bori},
			{ "borr", borr},
			{ "seti", seti},
			{ "setr", setr},
			{ "gtir", gtir},
			{ "gtrr", gtrr},
			{ "gtri", gtri},
			{ "eqrr", eqrr},
			{ "eqri", eqri},
			{ "eqir", eqir},
	};
	ifstream ifs("input.txt");
	unsigned long opRegister;
	vector<instruction> instructions;
	ifs.ignore(3);
	ifs>>opRegister;
	{
		string opName;
		unsigned long a, b, c;
		while (ifs) {
			ifs>>opName>>a>>b>>c;
			if (ifs)instructions.emplace_back(ops[opName], a, b, c);
		}
	}
	registers[0] = 0;
	vector<unsigned long> reg3s;
	unsigned long op = 0;
	while(op < instructions.size()) {
		if (op == 28) {
			if (find(reg3s.begin(), reg3s.end(), registers[3]) != reg3s.end()) {
				cout<<reg3s.back();
				return 0;
			}
			reg3s.push_back(registers[3]);
		}
		registers[opRegister] = op;
		instructions[op].execute();
		//cout<<op<<" -> ["<<registers[0]<<","<<registers[1]<<","<<registers[2]<<","<<registers[3]<<","<<registers[4]<<","<<registers[5]<<"]"<<endl;
		op = registers[opRegister] + 1;
	}
	return 0;
}