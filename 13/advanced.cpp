#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

enum trackType {
	horizontal = '-', vertival = '|', curve1 = '\\', curve2 = '/', intersection = '+', none = ' '
};

class cart {
  public:
	cart(size_t x, size_t y, int dirX, int dirY) : m_DirX(dirX), m_DirY(dirY), m_X(x), m_Y(y){
		intersectionsEncountered = 0;
	}
	bool operator<(const cart& x) const {
		if (m_Y < x.m_Y)
			return true;
		else if (m_Y > x.m_Y)
			return false;
		else return m_X < x.m_X;
	}
	bool operator==(const cart& x) const {
		return m_X == x.m_X && m_Y == x.m_Y;
	}
	size_t m_X, m_Y, intersectionsEncountered;
	int m_DirX, m_DirY;
};

void turnLeft(cart& c) {
	if (c.m_DirY){
		c.m_DirX = c.m_DirY;
		c.m_DirY = 0;
	} else {
		c.m_DirY = -c.m_DirX;
		c.m_DirX = 0;
	}
}

void turnRight(cart& c) {
	if (c.m_DirY){
		c.m_DirX = -c.m_DirY;
		c.m_DirY = 0;
	} else {
		c.m_DirY = c.m_DirX;
		c.m_DirX = 0;
	}
}

void turnOnCurve(cart& c, trackType type) {
	if (type == '/') {
		if (c.m_DirY)
			turnRight(c);
		else
			turnLeft(c);
	} else {
		if (c.m_DirY)
			turnLeft(c);
		else
			turnRight(c);
	}
}

int main() {
	ifstream ifs("input.txt");
	vector<vector<trackType>> board;
	map<size_t, map<size_t, shared_ptr<cart>>> carts;
	string line;
	size_t y = 0;
	vector<shared_ptr<cart>> cartsVector;
	while(getline(ifs, line)) {
		board.emplace_back();
		size_t x = 0;
		for (char & c : line){
			switch (c){
				case 'v':
					board.back().emplace_back(trackType::vertival);
					cartsVector.emplace_back(make_shared<cart>(x,y,0,1));
					break;
				case '^':
					board.back().emplace_back(trackType::vertival);
					cartsVector.emplace_back(make_shared<cart>(x,y,0,-1));
					break;
				case '<':
					board.back().emplace_back(trackType::horizontal);
					cartsVector.emplace_back(make_shared<cart>(x,y,-1,0));
					break;
				case '>':
					board.back().emplace_back(trackType::horizontal);
					cartsVector.emplace_back(make_shared<cart>(x,y,1,0));
					break;
				default:
					board.back().emplace_back(trackType(c));
			}
			x++;
		}
		y++;
	}
	while(cartsVector.size() > 1){
		for (auto it = cartsVector.begin(); it != cartsVector.end(); it++){
			auto curCart = *it;
			carts[curCart->m_X][curCart->m_Y] = nullptr;
			size_t newX = curCart->m_X + curCart->m_DirX, newY = curCart->m_Y + curCart->m_DirY;
			if (carts[newX][newY]){
				cout<<"crash at "<<newX<<","<<newY<<endl;
				ssize_t dist = distance(cartsVector.begin(), it);
				cartsVector.erase(it);
				cartsVector.erase(find(cartsVector.begin(), cartsVector.end(), carts[newX][newY]));
				it = next(cartsVector.begin(), dist - 2 );
				carts[newX][newY] = nullptr;
				continue;
			}
			switch (board[newY][newX]){
				case '+':
					switch(curCart->intersectionsEncountered){
						case 0:
							turnLeft(*curCart);
							break;
						case 2:
							turnRight(*curCart);
							break;
					}
					curCart->intersectionsEncountered = (curCart->intersectionsEncountered + 1) % 3;
					break;
				case ' ':
					throw runtime_error("WTF");
				case '\\':
				case '/':
					turnOnCurve(*curCart, board[newY][newX]);
					break;
			}
			curCart->m_X = newX;
			curCart->m_Y = newY;
			carts[newX][newY] = curCart;
		}
		sort(cartsVector.begin(), cartsVector.end());
	}
	if (cartsVector.size() == 1) {
		cout << cartsVector.front()->m_X << "," << cartsVector.front()->m_Y << endl;
		return 0;
	}
	return 1;
}