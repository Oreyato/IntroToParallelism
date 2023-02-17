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

std::mutex sharedMutex;
int i{ 0 };

void displayEvenNum(int minDisplayedNum = 0, int maxDisplayedNum = 1000) {
	while (i < maxDisplayedNum + 1)
	{
		if (i % 2 == 0) {
			std::lock_guard<std::mutex> lock(sharedMutex);
			
			cout << i << "\n";
		
			i++;
		}
	}
}
void displayOddNum(int minDisplayedNum = 0, int maxDisplayedNum = 1000) {
	while (i < maxDisplayedNum)
	{
		if (i % 2 != 0) {
			std::lock_guard<std::mutex> lock(sharedMutex);

			cout << i << "\n";

			i++;
		}
	}
}

int main() {
	int minNum{ 0 };
	int maxNum{ 1000 };

	#pragma region Without thread version
	//displayNumbers(minNum, maxNum, true); // Display even numbers
	//cout << "=====" << endl;
	//displayNumbers(minNum, maxNum, false); // Display odd numbers
	#pragma endregion
	#pragma region Threads without mutexes
	//std::thread tEven(displayNumbers, minNum, maxNum, true); // Display even numbers
	//cout << "=====" << endl;
	//std::thread tOdd(displayNumbers, minNum, maxNum, false); // Display odd numbers
	#pragma endregion
	std::thread tEven(displayEvenNum, minNum, maxNum); // Display even numbers
	cout << "=====" << endl;
	std::thread tOdd(displayOddNum, minNum, maxNum); // Display odd numbers

	tEven.join();
	tOdd.join();

	return 0;
}