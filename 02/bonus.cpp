#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool exactlyOneCharOff(const string& a, const string& b){
	// just to make sure
	if (a.size() != b.size())
		return false;
	bool oneOff = false;
	for (size_t i = 0; i < a.size(); i++){
		if (a[i] != b[i])
			if (oneOff)
				return false;
			else
				oneOff = true;
	}
	return oneOff;
}

int main(){
	vector<string> boxIds;
	string tmp;
	while(cin>>tmp){
		for(auto it : boxIds)
			if (exactlyOneCharOff(it, tmp)) {
				for (size_t i = 0; i < tmp.size(); i++)
					if (tmp[i] == it[i])
						cout<<tmp[i];
				cout<<endl;
				return 0;
			}
		boxIds.push_back(tmp);
	}
	return 1;
}

