#include <cstdio>
#include <iostream>
#include <vector>

#define FABRIC_SIZE 1000

using namespace std;

struct request{
	size_t id, left, top, x, y;
};

int main(){
	size_t overlappingCnt = 0;
	vector<request> requests;
	int** usedSpace = new int*[FABRIC_SIZE];
	for (size_t i = 0; i < FABRIC_SIZE; i++){
		usedSpace[i] = new int[FABRIC_SIZE];
		for (size_t j = 0; j < FABRIC_SIZE; j++)
			usedSpace[i][j] = 0;
	}
	size_t id, left, top, x, y;
	char hash, at, comma, semicolomn, times;
	while(cin>>hash>>id>>at>>left>>comma>>top>>semicolomn>>x>>times>>y && hash == '#' && at == '@' && comma == ',' && semicolomn == ':' && times == 'x'){
		if (left + x > FABRIC_SIZE || top + y > FABRIC_SIZE){
			for (size_t i = 0; i < FABRIC_SIZE; i++)
				delete[] usedSpace[i];
			delete[] usedSpace;
			printf("Invalid size @%lu,%lu: %lu x %lu, make bigger array\n", left, top, x, y);
			return 1;
		}
		request req;
		req.id = id;
		req.left = left;
		req.top = top;
		req.x = x;
		req.y = y;
		requests.push_back(req);
		for(size_t i = 0; i < x; i++){
			for(size_t j = 0; j < y; j++){
				if (usedSpace[i+left][j+top] == 0)
					usedSpace[i+left][j+top] = 1;
				else if (usedSpace[i+left][j+top] == 1){
					overlappingCnt++;
					usedSpace[i+left][j+top] = 2;
				}
			}
		}
	}
	for (auto it : requests){
		bool uniq = true;
		for(size_t i = 0; i < it.x; i++){
            for(size_t j = 0; j < it.y; j++){
            	if (usedSpace[i+it.left][j+it.top] == 2){
            		uniq = false;
            		break;
        		}
    		}
		}
		if (uniq){
			cout<<it.id<<endl;
			break;
		}
	}
	for (size_t i = 0; i < FABRIC_SIZE; i++)
    	delete[] usedSpace[i];
    delete[] usedSpace;
    printf("%lu\n", overlappingCnt);
}
