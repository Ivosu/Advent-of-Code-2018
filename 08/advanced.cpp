#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct node{
	unsigned int childrenCnt = 0;
	vector<node> children;
	unsigned int metadataEntriesCnt = 0;
	vector<unsigned int> metadataEntries;
	bool storedNodeValue = false;
	unsigned int nodeValue = 0;

	unsigned int getNodeValue(){
		if (!storedNodeValue) {
			if (childrenCnt == 0)
				nodeValue = accumulate(metadataEntries.begin(), metadataEntries.end(), 0u);
			else
				for (unsigned int index : metadataEntries)
					if (index != 0 && index - 1 < childrenCnt)
						nodeValue += children[index - 1].getNodeValue();
			storedNodeValue = true;
		}
		return nodeValue;
	}

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

int main() {
	ifstream ifs("input.txt");
	node root;
	ifs>>root;
	cout<<root.getNodeValue()<<endl;
	return 0;
}