#include <iostream>

#include <chrono>

#include "Ingredients.h"
#include "Waiter.h"
#include "Cooker.h"
#include "Chief.h"

using std::cout;
using std::endl;


class Customer
{
public:
	void orderFood();
	void eatFood();
	void exitRestaurant();
};

int main() {
	//v Initializations ==============================================
	Ingredients ingredients;

	Customer customer;
	Waiter waiter;
	Chief chief;
	Cooker cooker(chief);
	

	//^ Initializations ==============================================
	//v Food loop ====================================================
	//v Customer ============================
	// Ask for menu
	
	// Pick food in the menu and ask for it

	//v Waiter ==============================
	// Get order
	// waiter.takeOrder();
	cooker.setOrder(ingredients.pickDish());

	// Put order on the order board
	// waiter.sendOrder();

	//v Cooker ==============================
	// Cook order ingredients


	//v Chief ===============================
	// Mix ingredients

	// Put order on the counter

	//v Waiter ==============================
	// Pick order and give it to the customer

	//v Customer ============================
	// Eat food

	// Leave restaurant

	cooker.cookerThread.join();
	chief.chiefThread.join();
	//^ Food loop ====================================================

	return 0;
}