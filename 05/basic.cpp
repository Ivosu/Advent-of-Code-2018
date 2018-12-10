#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool isReactive(char a, char b){
	return (a ^ b) == 32;
}

string::iterator react(const string::iterator& pos, string& original){
	if (distance(pos, original.end()) >= 2){
		string::iterator newNextPos = react(next(pos), original), newPos = prev(newNextPos);
		if (newNextPos != original.end() && isReactive(*newPos, *newNextPos))
			newPos = original.erase(newPos, next(newPos, 2));
		return newPos;
	}
	else
		return pos;
}

int main() {
	ifstream ifs("input.txt");
	string polymer;
	ifs>>polymer;
	react(polymer.begin(), polymer);
	cout<<polymer.length()<<endl;
	return 0;
}