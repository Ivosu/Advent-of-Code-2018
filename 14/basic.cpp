#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INPUT 556061
#define DESIRED INPUT
using namespace std;

int main() {
	vector<uint8_t> recipes = {3, 7};
	size_t elf1 = 0, elf2 = 1;
	while(recipes.size() < DESIRED + 10){
		uint8_t elf1Recipe = recipes[elf1], elf2Recipe = recipes[elf2];
		uint8_t createdRecipe =  elf1Recipe + elf2Recipe;
		if (createdRecipe < 10)
			recipes.push_back(createdRecipe);
		else {
			recipes.push_back(createdRecipe/10);
			recipes.push_back(createdRecipe%10);
		}
		elf1 = (elf1 + 1 + elf1Recipe) % recipes.size();
		elf2 = (elf2 + 1 + elf2Recipe) % recipes.size();
	}
	for (size_t i = DESIRED; i < DESIRED + 10; i++) {
		cout<<(int)recipes[i];
	}
	cout<<endl;
	return 0;
}