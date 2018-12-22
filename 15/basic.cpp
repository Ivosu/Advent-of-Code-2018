#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory>
#include <numeric>

using namespace std;

class Character {
  public:
	virtual bool isElf() const = 0;
	size_t getX() const {
		return m_X;
	}
	size_t getY() const {
		return m_Y;
	}
	void setXY(size_t x, size_t y) {
		size_t distX = (m_X > x ? m_X - x : x - m_X);
		size_t distY = (m_Y > y ? m_Y - y : y - m_Y);
		if (sqrt(distX*distX + distY*distY) != 1) throw "This should not happen";
		m_X = x;
		m_Y = y;
	}
	ssize_t getHP() const {
		return m_HP;
	}
	size_t getAttackPower() const {
		return m_AttackPower;
	}
	bool operator< (const Character& other) const {
		return m_Y < other.m_Y ? true : m_Y == other.m_Y ? m_X < other.m_X : false;
	}
  protected:
	Character(size_t x, size_t y) : m_X(x), m_Y(y) {}
	ssize_t m_HP = 200;
	size_t m_AttackPower = 3;
	size_t m_X, m_Y;
};

class Elf : public Character {
  public:
	Elf(size_t x, size_t y) : Character(x,y) {}
	bool isElf() const override {
		return true;
	}

  private:
};

class Gnome : public Character {
  public:
	Gnome(size_t x, size_t y) : Character(x,y) {}
	bool isElf() const override {
		return false;
	}
  private:
};

int main() {
	ifstream ifs("input.txt");
	map<size_t, map<size_t, char>> board; // Only map with walls
	map<size_t, map<size_t, shared_ptr<Character>>> characters; // Characters map
	vector<shared_ptr<Character>> elves;
	vector<shared_ptr<Character>> gnomes;
	string line;
	size_t lineCnt = 0;
	while(getline(ifs, line)){
		for (size_t i = 0; i < line.size(); i++) {
			switch (line[i]){
				case 'E':
					elves.push_back(characters[i][lineCnt] = make_shared<Elf>(i, lineCnt));
					board[i][lineCnt] = '.';
					break;
				case 'G':
					gnomes.push_back(characters[i][lineCnt] = make_shared<Gnome>(i, lineCnt));
					board[i][lineCnt] = '.';
					break;
				case '#':
					board[i][lineCnt] = '#';
					break;
				case '.':
					board[i][lineCnt] = '.';
					break;
				default:
					throw "Unknown tile on map";
			}
			lineCnt++;
		}
	}
	size_t round = 0;
	while(true){
		if (elves.empty()) {
			cout<<round * accumulate(gnomes.begin(), gnomes.end(), 0ul, [](size_t sum, const shared_ptr<Character>& character) {
				return sum + character->getHP();
			})<<endl;
			break;
		}
		else if (gnomes.empty()) {
			cout<<round * accumulate(elves.begin(), elves.end(), 0ul, [](size_t sum, const shared_ptr<Character>& character) {
				return sum + character->getHP();
			})<<endl;
			break;
		}



		sort(elves.begin(), elves.end());
		sort(gnomes.begin(), gnomes.end());
	}
	return 0;
}