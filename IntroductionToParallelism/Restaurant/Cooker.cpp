#include "Cooker.h"

#include <iostream>
#include <chrono>

using std::vector;
using std::cout;
using std::endl;

Cooker::Cooker(Chief& chiefP) :
	linkedChief{chiefP}
{
	cookingFuture = ingredientsProm.get_future();
	cookerThread = std::thread([this] {
		while (isWorking)
		{
			prepareOrder();
		}
	});
}


void Cooker::setOrder(std::vector<Ingredient> ingredientsP)
{
	ingredientsProm.set_value(ingredientsP);
}

void Cooker::prepareOrder()
{
	vector<Ingredient> ingredients = cookingFuture.get();

	if (ingredients.empty()) return;

	vector<Ingredient> cookedIngredients;

	cout << "\n=== Cook got order ====\n" << endl;

	for (uint8_t i = 0; i < ingredients.size(); i++)
	{
		prepareIngredient(ingredients[i]);
		cookedIngredients.push_back(ingredients[i]);
	}

	cout << "\n=== Finished cooking ==\n" << endl;

	// Give ingredients to chief
	linkedChief.setPlate(cookedIngredients);
	
	// Empty promise
	vector<Ingredient> emptyList;
	setOrder(emptyList);
}

void Cooker::prepareIngredient(Ingredient ingredientP)
{
	cout << "Cooking " << ingredientP.name << " (" << ingredientP.cookingTime << "s)\n";
	std::this_thread::sleep_for(std::chrono::seconds(ingredientP.cookingTime));
}
