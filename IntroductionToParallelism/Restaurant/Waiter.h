#pragma once
#include <thread>
#include <future>

class Waiter
{
public:
	void giveMenu();

	void takeOrder();
	void sendOrder();
	void giveOrder();
};

