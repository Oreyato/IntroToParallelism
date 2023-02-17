#pragma once
#include <string>
#include <vector>

struct Ingredient
{
	Ingredient(std::string nameP, float cookingTimeP) : 
		name{nameP},
		cookingTime{cookingTimeP}
	{};

	std::string name{ "" };
	float cookingTime{ 0.0f };
};

class Ingredients
{
public:
	Ingredients();

	void showMenu() const;
	inline const std::vector<Ingredient> getMenu() { return menuOptions; }

	std::vector<Ingredient> pickDish() const;

private:
	std::vector<Ingredient> menuOptions;

	int vegetablesNum{ 0 };
	int starchNum{ 0 };
	int proteinsNum{ 0 };

	void displayIngredientsCategory(std::string categoryNameP, uint32_t startingIndexP, int categoryQuantityP) const;
	uint8_t findIngredientIndex(uint8_t startingIndexP, int categoryQuantityP) const;
};

