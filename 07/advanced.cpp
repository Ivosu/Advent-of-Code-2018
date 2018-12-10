#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

#define BASIC_TIMEOUT 60
#define WORKERS_CNT 5

struct node {
	set<char> dependsOn;
	set<char> dependee;
};

bool compare(const pair<char, size_t>& a, const pair<char, size_t>& b){
	return a.second < b.second;
}

int main() {
	ifstream ifs("input.txt");
	string line;
	map<char, node> nodes;
	while (getline(ifs, line)){
		char bef = line[5];
		char dependee = line[36];
		nodes[bef].dependee.insert(dependee);
		nodes[dependee].dependsOn.insert(bef);
	}
	priority_queue<char, vector<char>, greater<>> q;
	for (const auto& pair : nodes){
		if (pair.second.dependsOn.empty())
			q.push(pair.first);
	}
	vector< pair< char, size_t> > workTimes;
	size_t workingWorkersCnt = 0;
	size_t elapsedTime = 0;
	while(!q.empty() || !workTimes.empty()){
		if (!q.empty() && workingWorkersCnt < WORKERS_CNT) {
			char wrk = q.top();
			q.pop();
			pair<char, size_t> tmp(wrk, BASIC_TIMEOUT + (wrk - 'A' + 1 ));
			workTimes.insert(upper_bound(workTimes.begin(), workTimes.end(), tmp, compare), tmp);
			workingWorkersCnt++;
			//cout<<"started working on "<<wrk<<" at time "<<elapsedTime<<endl;
		} else {
			assert(!workTimes.empty());
			auto done = workTimes.front();
			size_t time = done.second;
			workTimes.erase(workTimes.begin(), next(workTimes.begin()));
			for (auto& it : workTimes){
				it.second -= time;
			}
			elapsedTime += time;
			//cout<<"ended working on "<<done.first<<" at time "<<elapsedTime<<endl;
			workingWorkersCnt--;
			for ( const char & x : nodes[done.first].dependee){
				nodes[x].dependsOn.erase(done.first);
				if (nodes[x].dependsOn.empty())
					q.push(x);
			}
		}
	}
	assert(q.empty() && workTimes.empty());
	cout<<elapsedTime<<endl;
	return 0;
}