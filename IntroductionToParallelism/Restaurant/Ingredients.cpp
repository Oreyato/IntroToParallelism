#include "Ingredients.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

Ingredients::Ingredients()
{
	menuOptions.emplace_back("Carrot", 4);
	menuOptions.emplace_back("Courgette", 3);
	menuOptions.emplace_back("Pepper", 2);
	menuOptions.emplace_back("Salad", 1);
	vegetablesNum = 4;

	menuOptions.emplace_back("Potatoe", 8);
	menuOptions.emplace_back("Rice", 3);
	menuOptions.emplace_back("Pasta", 2);
	starchNum = 3;

	menuOptions.emplace_back("Chicken", 3);
	menuOptions.emplace_back("Beaf", 3);
	menuOptions.emplace_back("Pollock", 4);
	menuOptions.emplace_back("Tofu", 2);
	proteinsNum = 4;
}

void Ingredients::showMenu() const
{
	uint8_t startingIndex{ 0 };

	cout << "===== Simple Menu =====\n";
	displayIngredientsCategory("Vegetables", startingIndex, vegetablesNum);
	startingIndex += vegetablesNum;

	displayIngredientsCategory("Starch food", startingIndex, starchNum);
	startingIndex += starchNum;

	displayIngredientsCategory("Proteins", startingIndex, proteinsNum);
	startingIndex += proteinsNum;
}

std::vector<Ingredient> Ingredients::pickDish() const
{
	srand((unsigned)time(0));
	std::vector<Ingredient> orderedIngredients;
	uint8_t startingIndex{ 0 };

	// Pick vegetable
	orderedIngredients.push_back(menuOptions[findIngredientIndex(startingIndex, vegetablesNum)]);
	startingIndex += vegetablesNum;

	// Pick starch food
	orderedIngredients.push_back(menuOptions[findIngredientIndex(startingIndex, starchNum)]);
	startingIndex += starchNum;

	// Pick protein
	orderedIngredients.push_back(menuOptions[findIngredientIndex(startingIndex, proteinsNum)]);
	startingIndex += proteinsNum;

	cout << "===== You picked: =====\n";
	uint8_t ingredientsNum = orderedIngredients.size();

	for (uint8_t i = 0; i < ingredientsNum - 1; i++)
	{
		cout << orderedIngredients[i].name << " | ";
	}
	cout << orderedIngredients[ingredientsNum - 1].name << endl;

	return orderedIngredients;
}

void Ingredients::displayIngredientsCategory(std::string categoryNameP, uint32_t startingIndexP, int categoryQuantityP) const
{
	cout << categoryNameP << ":\n";
	for (uint8_t i = startingIndexP; i < startingIndexP + categoryQuantityP; ++i)
	{
		cout << "- " << menuOptions[i].name << "\n";
	}
	cout << endl;
}

uint8_t Ingredients::findIngredientIndex(uint8_t startingIndexP, int categoryQuantityP) const
{
	uint8_t ingredientIndex = startingIndexP + (rand() % categoryQuantityP);
	return ingredientIndex;
}

