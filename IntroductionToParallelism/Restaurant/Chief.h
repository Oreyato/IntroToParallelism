#pragma once
#include "Ingredients.h"

#include <thread>
#include <future>

class Chief
{
public:
	Chief();
	Chief(const Chief&);

	std::thread chiefThread;

	void setPlate(std::vector<Ingredient> ingredientsP);
	inline void setWorkingStatus(bool isWorkingP) { isWorking = isWorkingP; }

	void dressIngredients();

private:
	void dressIngredient(Ingredient ingredientP);

	bool isWorking{ true };

	std::promise<std::vector<Ingredient>> ingredientsProm;
	std::future<std::vector<Ingredient>> dressingFuture;
};
