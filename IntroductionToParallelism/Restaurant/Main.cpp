#include <iostream>
#include <thread>
#include <future>

#include <chrono>

#include "Ingredients.h"

using std::cout;
using std::endl;


int main() {
	Ingredients ingredientsList;
	ingredientsList.menu();
	ingredientsList.pickDish();

	return 0;
}