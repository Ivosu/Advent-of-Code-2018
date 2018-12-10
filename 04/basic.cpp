#include <iostream>
#include <array>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>

using namespace std;

struct timestamp {
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	bool operator< (const timestamp& x) const {
		if (year < x.year)
			return true;
		if (year > x.year)
			return false;
		if (month < x.month)
			return true;
		if (month > x.month)
			return false;
		if (day < x.day)
			return true;
		if (day > x.day)
			return false;
		if (hour < x.hour)
			return true;
		if (hour > x.hour)
			return false;
		return (minute < x.minute);
	}
	friend istream& operator>>(istream & is, timestamp& time){
		char x;
		return is>>time.year>>x>>time.month>>x>>time.day>>time.hour>>x>>time.minute;
	}
};

struct entry{
	timestamp time;
	string message;
	bool operator<(const entry& x) const{
		return time<x.time;
	}
	friend istream& operator>>(istream & is, entry& entry){
		char x;
		is>>x>>entry.time>>x;
		is.get();
		getline(is, entry.message);
		return is;
	}
};

int main() {
	ifstream ifs("input.txt");
	entry entr;
	vector<entry> entries;
	while(ifs>>entr){
		entries.push_back(entr);
	}
	sort(entries.begin(), entries.end());
	map<unsigned int, array<unsigned int, 60>> sleepStats;
	unsigned int currentGuardId = 0;
	unsigned int sleepStart = 0;
	bool asleep = false;
	for (const auto& it : entries){
		cout<<it.time.minute<<" "<<it.message<<endl;
		if (it.message[0] == 'G'){ // new day entry
			assert(!asleep);
			stringstream ss(it.message.substr(7));
			ss>>currentGuardId;
		}
		else if (it.message[0] == 'f'){ // falls asleep
			sleepStart = it.time.minute;
			asleep = true;
		}
		else if (it.message[0] == 'w') { // wakes up
			assert(asleep);
			for (unsigned int i = sleepStart; i < it.time.minute; i++) {
				(sleepStats[currentGuardId][i])++;
			}
			asleep = false;
		}
		else {
			assert(false);
		}
	}

	unsigned int max = 0;
	currentGuardId = 0;
	for (auto& it : sleepStats){
		unsigned int localSum = 0;
		for (unsigned int i = 0; i < 60; i++) {
			localSum += it.second[i];
		}
		if (max < localSum){
			currentGuardId = it.first;
			max = localSum;
		}
	}
	max = 0;
	unsigned int minute = 0;
	for (unsigned int i = 0; i < 60; i++){
		if (max < sleepStats[currentGuardId][i]){
			max = sleepStats[currentGuardId][i];
			minute = i;
		}
	}
	cout<<"Winner of sleeping contest is: "<<currentGuardId<<" with most time slept: "<< max <<" @ "<<minute<<endl;
	cout<<"Puzzle answer: "<<currentGuardId*minute<<endl;
	return 0;
}