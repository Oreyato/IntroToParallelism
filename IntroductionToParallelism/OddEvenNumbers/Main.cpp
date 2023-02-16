#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;


void displayNumbers(int minDisplayedNum = 0, int maxDisplayedNum = 1000, bool evenNumbers = true) {
	int evenNumberTest = 0;

	if (!evenNumbers) {
		evenNumberTest = 1;
	}

	for (int i = minDisplayedNum; i < maxDisplayedNum + 1; i++)
	{
		if (i % 2 == evenNumberTest) {
			cout << i << "\n";
		}
	}
}

int main() {
	#pragma region Without thread version
	//displayNumbers(0, 1000, true); // Display even numbers
	//cout << "=====" << endl;
	//displayNumbers(0, 1000, false); // Display odd numbers
	#pragma endregion

	std::thread tEven(displayNumbers, 0, 1000, true); // Display even numbers
	cout << "=====" << endl;
	std::thread tOdd(displayNumbers, 0, 1000, false); // Display odd numbers

	tEven.join();
	tOdd.join();

	return 0;
}