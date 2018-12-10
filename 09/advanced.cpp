#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

list<unsigned int>::iterator nextCircularIterator(list<unsigned int>& l, const list<unsigned int>::iterator& it, size_t step = 1){
	auto tmp = it;
	for (size_t i = 0; i < step; i++) {
		auto nextIt = next(tmp);
		tmp = nextIt == l.end() ? l.begin() : nextIt;
	}
	return tmp;
}

list<unsigned int>::iterator prevCircularIterator(list<unsigned int>& l, const list<unsigned int>::iterator& it, size_t step = 1) {
	auto tmp = it;
	for (size_t i = 0; i < step; i++)
		tmp = tmp == l.begin() ? prev(l.end()) : prev(tmp);
	return tmp;
}

int main() {
	ifstream ifs("input.txt");
	unsigned int playerCnt;
	unsigned int marbleCnt;
	ifs >> playerCnt;
	ifs.ignore(31);
	ifs >> marbleCnt;
	ifs.ignore(8);
	list<unsigned int> board = {0};
	auto currIt = board.begin();
	map<unsigned int, unsigned int> scores;
	for (unsigned int i = 1; i <= marbleCnt * 100; i++) {
		if (i % 23 == 0) {
			currIt = prevCircularIterator(board, currIt, 7);
			scores[i % playerCnt] += i + *currIt;
			currIt = board.erase(currIt);
			if (currIt == board.end())
				currIt = board.begin();
		} else {
			currIt = nextCircularIterator(board, currIt, 2);
			if (currIt == board.begin()) {
				board.push_back(i);
				currIt = prev(board.end());
			} else
				currIt = board.insert(currIt, i);
		}
	}
	cout<<max_element(scores.begin(), scores.end(),
					  [](const pair<unsigned int, unsigned int>& a, const pair<unsigned int, unsigned int>& b){
						  return a.second < b.second;
					  }
	)->second<<endl;
	return 0;
}
