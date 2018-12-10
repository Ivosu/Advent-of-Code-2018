#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

class light {
  public:
	light(int x, int y, int velX, int velY) : m_X(x), m_Y(y), m_VelX(velX), m_VelY(velY) {}

	int getX() const {
		return m_X;
	}

	int getY() const {
		return m_Y;
	}

	void update() {
		m_X += m_VelX;
		m_Y += m_VelY;
	}
  private:
	const int m_VelX, m_VelY;
	int m_X, m_Y;
};

using namespace std;

int main() {
	ifstream ifs("input.txt");
	vector<light> lights;
	int x, y, velX, velY;
	while(1){
		ifs.ignore(10);
		ifs>>x;
		ifs.get();
		ifs>>y;
		ifs.ignore(12);
		ifs>>velX;
		ifs.get();
		ifs>>velY;
		ifs.ignore(2);
		if (!ifs)
			break;
		lights.emplace_back(x, y, velX, velY);
	}
	int counter = 0;
	bool skip;
	do {
		counter++;
		int minX = std::numeric_limits<int>::max(), maxX = std::numeric_limits<int>::min(), minY = minX, maxY = maxX;
		for (auto &l : lights) {
			l.update();
			minX = min(l.getX(), minX);
			minY = min(l.getY(), minY);
			maxX = max(l.getX(), maxX);
			maxY = max(l.getY(), maxY);
		}
		size_t sizeX = maxX - minX + 1;
		size_t sizeY = maxY - minY + 1;
		if (sizeX < 100 && sizeY < 100) {
			skip = false;
			bool **grid = new bool *[sizeX];
			for (size_t i = 0; i < sizeX; i++) {
				grid[i] = new bool[sizeY];
				for (size_t j = 0; j < sizeY; j++)
					grid[i][j] = false;
			}
			for (const auto &l : lights) {
				grid[l.getX() - minX][l.getY() - minY] = true;
			}
			for (size_t j = 0; j < sizeY; j++) {
				for (size_t i = 0; i < sizeX; i++)
					cout << (grid[i][j] ? "X" : " ");
				cout << '\n';
			}

			for (size_t i = 0; i < sizeX; i++)
				delete[]grid[i];
			delete[] grid;
			cout << "@" << counter << endl;
		}
		else skip = true;
	} while(skip || getchar() != 's');
	return 0;
}