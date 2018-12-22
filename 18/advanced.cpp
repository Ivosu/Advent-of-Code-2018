#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include <thread>
#include <chrono>


#define SIZE_X_REAL 50
#define SIZE_Y_REAL 50

#define SIZE_X_TEST 10
#define SIZE_Y_TEST 10

#define ROUND_CNT 1000000000ul

//#define TEST

//---------------------

#ifdef TEST

#define SIZE_X SIZE_X_TEST
#define SIZE_Y SIZE_Y_TEST

#else

#define SIZE_X SIZE_X_REAL
#define SIZE_Y SIZE_Y_REAL

#endif

//----------------------

using namespace std;

enum tile {
	open = '.', trees = '|', lumber = '#', none
};

tile transform(tile curr, const array<tile, 8>& neighbours) {
	if (curr == open) {
		if (count(neighbours.begin(), neighbours.end(), trees) >= 3){
			return trees;
		}
		return open;
	} else if (curr == trees){
		if (count(neighbours.begin(), neighbours.end(), lumber) >= 3){
			return lumber;
		}
		return trees;
	} else if (curr == lumber) {
		if (find(neighbours.begin(), neighbours.end(), lumber) != neighbours.end() &&
			find(neighbours.begin(), neighbours.end(), trees) != neighbours.end())
			return lumber;
		return open;
	} else
		throw "THIS SHOULDN'T HAPPEN";
}

array<tile,8> getNeighbours(size_t x, size_t y, const array<array<tile, SIZE_Y>, SIZE_X>& board) {
	array<tile,8> ret;
	bool canGoLeft = x > 0;
	bool canGoRight = x + 1 < board.size();
	bool canGoUp = y > 0;
	bool canGoDown = y + 1 < board[x].size();
	ret[0] = canGoLeft ? board[x-1][y] : none;
	ret[1] = canGoUp ? board[x][y-1] : none;
	ret[2] = canGoRight ? board[x+1][y] : none;
	ret[3] = canGoDown ? board[x][y+1] : none;
	ret[4] = canGoLeft && canGoUp ? board[x-1][y-1] : none;
	ret[5] = canGoLeft && canGoDown ? board[x-1][y+1] : none;
	ret[6] = canGoRight && canGoUp ? board[x+1][y-1] : none;
	ret[7] = canGoRight && canGoDown ? board[x+1][y+1] : none;
	return ret;
}

int main() {
#ifdef TEST
	ifstream ifs("input_test.txt");
#else
	ifstream ifs("input.txt");
#endif
	array<array<tile, SIZE_Y>, SIZE_X> field;
	{
		string line;
		for (size_t y = 0; y < SIZE_Y; y++) {
			getline(ifs, line);
			for (size_t x = 0; x < SIZE_X; x++) {
				field[x][y] = tile(line[x]);
			}
		}
	}
	array<array<tile, SIZE_Y>, SIZE_X> newField;
	for (volatile size_t i = 0; i < ROUND_CNT; i++){
		for (size_t y = 0; y < SIZE_Y; y++) {
			for (size_t x = 0; x < SIZE_X; x++) {
				newField[x][y] = transform(field[x][y], getNeighbours(x, y, field));
				cout << (newField[x][y] == trees ? "|" : (newField[x][y] == open ? "." : "#"));
			}
			cout<<endl;
		}
		cout<<endl;
		swap(newField, field);
		if (i > 524) {
			size_t luberCnt, treesCnt = luberCnt = 0;
			for (size_t x = 0; x < SIZE_X; x++)
				for (size_t y = 0; y < SIZE_Y; y++){
					if (field[x][y] == trees)
						treesCnt++;
					else if (field[x][y] == lumber)
						luberCnt++;
				}
			cout<<luberCnt*treesCnt<<endl;
				getchar();
		}
	}
	size_t luberCnt, treesCnt = luberCnt = 0;
	for (size_t x = 0; x < SIZE_X; x++)
		for (size_t y = 0; y < SIZE_Y; y++){
			if (field[x][y] == trees)
				treesCnt++;
			else if (field[x][y] == lumber)
				luberCnt++;
		}
	cout<<luberCnt*treesCnt<<endl;
	return 0;
}