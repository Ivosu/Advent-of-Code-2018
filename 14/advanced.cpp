#include <iostream>
#include <vector>
#include <cmath>

#define INPUT 556061
using namespace std;

int main() {
	vector<uint8_t> recipes = {3, 7};
	size_t elf1 = 0, elf2 = 1;
	unsigned long lastSum = 0;
	unsigned int inputLenght = floor(log10(INPUT)) + 1;
	unsigned long modulo = pow(10, inputLenght);
	while(true){
		uint8_t elf1Recipe = recipes[elf1], elf2Recipe = recipes[elf2];
		uint8_t createdRecipe =  elf1Recipe + elf2Recipe;
		if (createdRecipe < 10) {
			lastSum = (lastSum * 10) % modulo + createdRecipe;
			if (lastSum == INPUT){
				cout<<recipes.size() - inputLenght + 1<<endl;
				break;
			}
			recipes.push_back(createdRecipe);
		}
		else {
			lastSum = (lastSum * 10) % modulo + createdRecipe/10;
			if (lastSum == INPUT){
				cout<<recipes.size() - inputLenght + 1<<endl;
				break;
			}
			recipes.push_back(createdRecipe/10);
			lastSum = (lastSum * 10) % modulo + createdRecipe%10;
			if (lastSum == INPUT){
				cout<<recipes.size() - inputLenght + 1<<endl;
				break;
			}
			recipes.push_back(createdRecipe%10);
		}
		elf1 = (elf1 + 1 + elf1Recipe) % recipes.size();
		elf2 = (elf2 + 1 + elf2Recipe) % recipes.size();
	}
	return 0;
}