#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool isReactive(char a, char b){
	return (a ^ b) == 32;
}

string::iterator react(const string::iterator& pos, string& original) {
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
	size_t min = polymer.size();
	string lowered;
	transform(polymer.begin(), polymer.end(), back_inserter(lowered), [](char a) {
		return tolower(a);
	});
	for (char x = 'a'; x <= 'z'; x++){
		string tmp;
		string::iterator lowerIt = lowered.begin();
		copy_if(polymer.begin(), polymer.end(), back_inserter(tmp), [x, &lowerIt](char a) -> bool {
			return x != *(lowerIt++);
		});
		react(tmp.begin(), tmp);
		min = std::min(min, tmp.length());
	}
	cout<<min<<endl;
	return 0;
}