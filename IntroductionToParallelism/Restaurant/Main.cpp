#include <iostream>
#include <thread>
#include <future>

#include <chrono>

#include "Ingredients.h"
#include "Waiter.h"
#include "Cooker.h"

using std::cout;
using std::endl;


class Customer
{
public:
	void orderFood();
	void eatFood();
	void exitRestaurant();
};
class Chief
{
public:
	void mixIngredients();
};

int main() {
	//v Initializations ==============================================
	Ingredients ingredients;

	Customer customer;
	Waiter waiter;
	Cooker cooker;
	Chief chief;

	//^ Initializations ==============================================
	//v Food loop ====================================================
	//v Customer ============================
	// Ask for menu
	
	// Pick food in the menu and ask for it

	//v Waiter ==============================
	// Put order on the order board

	//v Cooker ==============================
	// Cook order ingredients

	//v Chief ===============================
	// Mix ingredients

	// Put order on the counter

	//v Waiter ==============================
	// Pick order and give it to the customer

	//v Customer ============================
	// Eat food

	// Leave restaurnant

	//^ Food loop ====================================================

	return 0;
}