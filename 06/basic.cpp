#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <queue>
#include <set>
#include <map>

using namespace std;

bool isBoarder(size_t x, size_t y, size_t xSize, size_t ySize){
	return (x == 0 || y == 0 || x >= (xSize - 1) || y >= (ySize - 1));
}

struct gridSquare {
	gridSquare(size_t id = 0, size_t wave = 0) : occupyId(id), occupiedInWave(wave) {
	}
	size_t occupyId;
	size_t occupiedInWave;
};

struct bfsEntry{
	bfsEntry(size_t x, size_t y, size_t id, size_t wave) : x(x), y(y), id(id), wave(wave) {};
	size_t x, y, id, wave;
};

int main() {
	ifstream ifs("input.txt");
	vector<pair<size_t, size_t>> coordinates;
	size_t x, y, minX = UINT_MAX, maxX = 0, minY = UINT_MAX, maxY = 0;
	char comma;
	while(ifs>>x>>comma>>y){
		assert(comma == ',');
		if (x < minX)
			minX = x;
		else if (x > maxX)
			maxX = x;
		if (y < minY)
			minY = y;
		else if (y > maxY)
			maxY = y;
		coordinates.emplace_back(x, y);
	}
	transform(coordinates.begin(), coordinates.end(), coordinates.begin(), [minX, minY] (pair<size_t, size_t> coord) {
		coord.first -= (minX - 1);
		coord.second -= (minY - 1);
		return coord;
	});
	size_t undefinedId = coordinates.size();
	size_t sharedId = undefinedId + 1;
	size_t xSize = maxX-minX + 3, ySize = maxY - minY + 3;
	auto sizeCnt = new size_t[coordinates.size()]; // for every coordinate create size counter
	auto grid = new gridSquare * [xSize];
	for (size_t i = 0; i < xSize; i++) {
		grid[i] = new gridSquare[ySize];
		for (size_t j = 0; j < ySize; j++)
			grid[i][j] = gridSquare(undefinedId, 0);
	}
	queue<bfsEntry> q;
	set<size_t> finite;
	map<pair<size_t, size_t>, set<size_t>> visited;
	for (size_t i = 0; i < coordinates.size(); i++) {
		finite.insert(i);
		auto it = coordinates[i];
		q.emplace(it.first, it.second, i, 1);
		sizeCnt[i] = 1;
		grid[it.first][it.second] = gridSquare(i, 0);
	}
	while(!q.empty()){
		auto top = q.front();
		q.pop();
		size_t wave = top.wave + 1;
		if (top.x > 0) {
			gridSquare &tmp = grid[top.x - 1][top.y];
			if (tmp.occupyId == undefinedId) {
				tmp.occupyId = top.id;
				tmp.occupiedInWave = wave;
				sizeCnt[top.id]++;
				q.emplace(top.x - 1, top.y, top.id, wave);
				visited[make_pair(x-1, y)].insert(top.id);
			} else if (tmp.occupiedInWave == wave) {
				auto wtf = visited[make_pair(x-1, y)];
				if (find(wtf.begin(), wtf.end(), top.id) == wtf.end()) {
					wtf.insert(top.id);
					q.emplace(top.x - 1, top.y, top.id, wave);
				}
				if (tmp.occupyId != top.id && tmp.occupyId != sharedId) {
					sizeCnt[tmp.occupyId]--;
					tmp.occupyId = sharedId;
				}
			}
		}
		if (top.x + 1 < xSize) {
			gridSquare &tmp = grid[top.x + 1][top.y];
			if (tmp.occupyId == undefinedId) {
				tmp.occupyId = top.id;
				tmp.occupiedInWave = wave;
				sizeCnt[top.id]++;
				q.emplace(top.x + 1, top.y, top.id, wave);
				visited[make_pair(x+1, y)].insert(top.id);
			} else if (tmp.occupiedInWave == wave) {
				auto wtf = visited[make_pair(x+1, y)];
				if (find(wtf.begin(), wtf.end(), top.id) == wtf.end()) {
					wtf.insert(top.id);
					q.emplace(top.x + 1, top.y, top.id, wave);
				}
				if (tmp.occupyId != top.id && tmp.occupyId != sharedId) {
					sizeCnt[tmp.occupyId]--;
					tmp.occupyId = sharedId;
				}
			}
		}
		if (top.y > 0) {
			gridSquare &tmp = grid[top.x][top.y - 1];
			if (tmp.occupyId == undefinedId) {
				tmp.occupyId = top.id;
				tmp.occupiedInWave = wave;
				sizeCnt[top.id]++;
				q.emplace(top.x, top.y - 1, top.id, wave);
				visited[make_pair(x, y - 1)].insert(top.id);
			} else if (tmp.occupiedInWave == wave) {
				auto wtf = visited[make_pair(x, y-1)];
				if (find(wtf.begin(), wtf.end(), top.id) == wtf.end()) {
					wtf.insert(top.id);
					q.emplace(top.x, top.y - 1, top.id, wave);
				}
				if (tmp.occupyId != top.id && tmp.occupyId != sharedId) {
					sizeCnt[tmp.occupyId]--;
					tmp.occupyId = sharedId;
				}
			}
		}
		if (top.y + 1 < ySize) {
			gridSquare &tmp = grid[top.x][top.y + 1];
			if (tmp.occupyId == undefinedId) {
				tmp.occupyId = top.id;
				tmp.occupiedInWave = wave;
				sizeCnt[top.id]++;
				q.emplace(top.x, top.y + 1, top.id, wave);
				visited[make_pair(x, y + 1)].insert(top.id);
			} else if (tmp.occupiedInWave == wave) {
				auto wtf = visited[make_pair(x, y + 1)];
				if (find(wtf.begin(), wtf.end(), top.id) == wtf.end()) {
					wtf.insert(top.id);
					q.emplace(top.x, top.y + 1, top.id, wave);
				}
				if (tmp.occupyId != top.id && tmp.occupyId != sharedId) {
					sizeCnt[tmp.occupyId]--;
					tmp.occupyId = sharedId;
				}
			}
		}
	}
	for (size_t i = 0; i < xSize; i++){
		size_t tmp = grid[i][0].occupyId;
		if (tmp != undefinedId && tmp != sharedId)
			finite.erase(tmp);
		tmp = grid[i][ySize-1].occupyId;
		if (tmp != undefinedId && tmp != sharedId)
			finite.erase(tmp);
	}
	for (size_t i = 1; i < xSize - 1; i++){
		size_t tmp = grid[0][i].occupyId;
		if (tmp != undefinedId && tmp != sharedId)
			finite.erase(tmp);
		tmp = grid[xSize-1][i].occupyId;
		if (tmp != undefinedId && tmp != sharedId)
			finite.erase(tmp);
	}
	size_t max = 0;
	for (size_t index : finite) {
		if (max < sizeCnt[index])
			max = sizeCnt[index];
	}
	cout<<max<<endl;
	return 0;
}