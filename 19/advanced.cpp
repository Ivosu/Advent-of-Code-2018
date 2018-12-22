#include <iostream>

#define REG2 10551377

using namespace std;

int main() {
	unsigned long reg1 = 1, reg4 = 1, reg0 = 0;
	while(reg4 <= REG2){
		//cout<<reg0<<", "<<reg1<<", "<<reg4<<endl;
		if (reg4*reg1 == REG2)
			reg0 += reg4;
		reg1++;
		if (reg1 <= REG2)
			continue;
		reg4++;
		reg1 = 1;
	}
	cout<<reg0<<endl;
	return 0;
}