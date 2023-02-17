#include "Chief.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Chief::Chief()
{
	dressingFuture = ingredientsProm.get_future();
	chiefThread = std::thread([this] {
		while (isWorking)
		{
			dressIngredients();
		}
		});
}

Chief::Chief(const Chief&)
{
	dressingFuture = ingredientsProm.get_future();
	chiefThread = std::thread([this] {
		while (isWorking)
		{
			dressIngredients();
		}
		});
}

void Chief::setPlate(std::vector<Ingredient> ingredientsP)
{
	ingredientsProm.set_value(ingredientsP);
}

void Chief::dressIngredients()
{
	vector<Ingredient> ingredients = dressingFuture.get();

	if (ingredients.empty()) return;

	vector<Ingredient> plate;

	cout << "\n=== Chief got order ===\n" << endl;

	for (uint8_t i = 0; i < ingredients.size(); i++)
	{
		dressIngredient(ingredients[i]);
		plate.push_back(ingredients[i]);
	}

	cout << "\n== Finished dressing ==\n" << endl;

	// Empty promise
	vector<Ingredient> emptyList;
	setPlate(emptyList);
}

void Chief::dressIngredient(Ingredient ingredientP)
{
	cout << "Dress " << ingredientP.name << " (" << ingredientP.dressingTime << "s)\n";
	std::this_thread::sleep_for(std::chrono::seconds(ingredientP.dressingTime));
}


