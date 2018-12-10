#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;


int main(){
	set<int> frequences;
	vector<int> differences;
	int freq = 0;
	int diff;
	while(cin >> diff){
		differences.push_back(diff);
		freq += diff;
		cout << diff<< " -> " << freq<<endl;
		if (find(frequences.begin(), frequences.end(), freq) == frequences.end()){
			frequences.insert(freq);
		}
		else {
			cout<<freq<<endl;
			return 0;
		}
	}
	while(true){
		for(auto it : differences){
			freq += it;
			cout<< it << " -> "<< freq << endl;
			if (find(frequences.begin(), frequences.end(), freq) == frequences.end()){
	            frequences.insert(freq);
            }
            else {
	            cout<<freq<<endl;
	        	return 0;
	        }
		}
	}
	return 0;
}
