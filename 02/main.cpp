#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main(){
	int withTwo = 0;
	int withThree = 0;
	string tmp;
	while(cin>>tmp){
		bool two = false, three = false;
		multiset<char> counts;
		set<char> chars;
		for (auto it : tmp){
			counts.insert(it);
			chars.insert(it);
		}
		for (auto it : chars){
			if (!two && counts.count(it) == 2){
				withTwo++;
				two = true;
			}
			if (!three && counts.count(it) == 3){
				withThree++;
				three = true;
			}
			if (two && three)
				break;
		}
	}
	cout<<withTwo<<" "<<withThree<<endl;
	cout<<withTwo*withThree<<endl;
	return 0;
}
