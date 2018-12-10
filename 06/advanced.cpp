#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <numeric>
#include <set>
#include <queue>

#define MAX_DISTANCE 10000

using namespace std;

ssize_t getManhatonDistance(pair<ssize_t, ssize_t> a, pair<ssize_t, ssize_t> b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

ssize_t getDistance(const pair<ssize_t, ssize_t>& point, const vector<pair<ssize_t, ssize_t>>& otherPoints){
	return accumulate(otherPoints.begin(), otherPoints.end(), ssize_t(), [point](const ssize_t& acc, const pair<ssize_t, ssize_t>& coord) -> ssize_t{
		return acc + getManhatonDistance(point, coord);
	});
}

int main() {
	ifstream ifs("input.txt");
	vector<pair<ssize_t, ssize_t>> coordinates;
	ssize_t x, y, xSum = 0, ySum = 0;
	char comma;
	while(ifs>>x>>comma>>y){
		assert(comma == ',');
		coordinates.emplace_back(x, y);
		xSum += x;
		ySum += y;
	}
	ssize_t centerX = xSum / coordinates.size(), centerY = ySum / coordinates.size();
	pair<ssize_t, ssize_t> center(centerX, centerY);
	assert(getDistance(center, coordinates) < MAX_DISTANCE);
	set<pair<ssize_t, ssize_t>> included;
	queue<pair<ssize_t, ssize_t>> q;
	q.push(center);
	included.insert(center);
	while(!q.empty()){
		auto wrk = q.front();
		q.pop();
		pair<ssize_t, ssize_t> tmp = make_pair(wrk.first + 1, wrk.second);
		if (included.find(tmp) == included.end() && getDistance(tmp, coordinates) < MAX_DISTANCE) {
			included.insert(tmp);
			q.push(tmp);
		}
		tmp = make_pair(wrk.first - 1, wrk.second);
		if (included.find(tmp) == included.end() && getDistance(tmp, coordinates) < MAX_DISTANCE) {
			included.insert(tmp);
			q.push(tmp);
		}
		tmp = make_pair(wrk.first, wrk.second + 1);
		if (included.find(tmp) == included.end() && getDistance(tmp, coordinates) < MAX_DISTANCE) {
			included.insert(tmp);
			q.push(tmp);
		}
		tmp = make_pair(wrk.first, wrk.second - 1);
		if (included.find(tmp) == included.end() && getDistance(tmp, coordinates) < MAX_DISTANCE) {
			included.insert(tmp);
			q.push(tmp);
		}
	}
	cout<<included.size()<<endl;
	return 0;
}