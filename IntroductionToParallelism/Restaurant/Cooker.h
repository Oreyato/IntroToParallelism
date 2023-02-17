#pragma once

#include "Chief.h"

class Cooker
{
public:
	Cooker(Chief& chiefP);

	std::thread cookerThread;

	void setOrder(std::vector<Ingredient> ingredientsP);
	inline void setWorkingStatus(bool isWorkingP) { isWorking = isWorkingP; }

	void prepareOrder();

private:
	void prepareIngredient(Ingredient ingredientP);

	bool isWorking{ true };

	std::promise<std::vector<Ingredient>> ingredientsProm;
	std::future<std::vector<Ingredient>> cookingFuture;
	
	Chief linkedChief;
};

