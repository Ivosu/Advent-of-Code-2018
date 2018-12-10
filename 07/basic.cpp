#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct node {
	set<char> dependsOn;
	set<char> dependee;
};

int main() {
	ifstream ifs("input.txt");
	string line;
	map<char, node> nodes;
	while (getline(ifs, line)){
		char bef = line[5];
		char dependee = line[36];
		if (nodes.find(bef) == nodes.end())
			nodes.insert(make_pair(bef, node()));
		if (nodes.find(dependee) == nodes.end())
			nodes.insert(make_pair(dependee, node()));
		nodes[bef].dependee.insert(dependee);
		nodes[dependee].dependsOn.insert(bef);
	}
	priority_queue<char, vector<char>, greater<>> q;
	for (const auto& pair : nodes){
		if (pair.second.dependsOn.empty())
			q.push(pair.first);
	}
	while(!q.empty()){
		char wrk = q.top();
		cout<<wrk;
		q.pop();
		for ( const char & x : nodes[wrk].dependee){
			nodes[x].dependsOn.erase(wrk);
			if (nodes[x].dependsOn.empty())
				q.push(x);
		}
	}
	cout<<endl;
	return 0;
}