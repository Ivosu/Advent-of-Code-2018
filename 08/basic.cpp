#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>

using namespace std;

struct node{
	node(){
		childrenCnt = 0;
		metadataEntriesCnt = 0;
	}

	unsigned int childrenCnt;
	vector<node> children;
	unsigned int metadataEntriesCnt;
	vector<unsigned int> metadataEntries;
	friend istream& operator>>(istream& is, node& n){
		is>>n.childrenCnt>>n.metadataEntriesCnt;
		n.children.reserve(n.childrenCnt);
		n.metadataEntries.reserve(n.metadataEntriesCnt);
		for (unsigned int i = 0; i < n.childrenCnt; i++) {
			node tmp;
			is >> tmp;
			n.children.push_back(tmp);
		}
		for (unsigned int i = 0; i < n.metadataEntriesCnt; i++) {
			unsigned int tmp;
			is >> tmp;
			n.metadataEntries.push_back(tmp);
		}
		return is;
	}
};

unsigned int getMedataEntriesSum(const node& root){
	unsigned int sum = accumulate(root.children.begin(), root.children.end(), 0u,
			[](unsigned int sum, const node& x){
		return sum + getMedataEntriesSum(x);
	});
	return accumulate(root.metadataEntries.begin(), root.metadataEntries.end(), sum);
}

int main() {
	ifstream ifs("input.txt");
	node root;
	ifs>>root;
	cout<<getMedataEntriesSum(root)<<endl;
	return 0;
}