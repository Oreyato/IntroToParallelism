#include <iostream>
#include <vector>

#include <algorithm>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;

using namespace std::chrono;

#pragma region Utils
vector<float> generateTable(int tableSizeP) {
	vector<float> table(tableSizeP);
	// Generate controlled random values
	auto f = []() -> float { return rand() % 20; };
	// Fill up the vector
	std::generate(table.begin(), table.end(), f);

	return table;
}

void displayResult(float tableSumP, std::chrono::steady_clock::time_point& startTimerP, std::chrono::steady_clock::time_point& stopTimerP) {
	cout << "Table sum: " << tableSumP << endl;

	auto duration = duration_cast<microseconds>(stopTimerP - startTimerP);
	cout << "Time taken: " << duration.count() << " microseconds" << endl;
}
#pragma endregion

#pragma region Sequential Solution
float seqTableSum(vector<float>& tableP) {
	float sum{ 0.0f };

	for (float& val : tableP) {
		sum += val;
	}

	return sum;
}
#pragma endregion

int main() {
	//v Generate table ======================
	vector<float> table = generateTable(100000);
 
	//^ Generate table ======================

	#pragma region Sequential
	//v Sequential ===================================================
	cout << "===== SEQ =====" << endl;

	auto start = high_resolution_clock::now(); // <--- START TIMER
	float tableSum = seqTableSum(table);
	auto stop = high_resolution_clock::now(); // <--- STOP TIMER

	// Display results
	displayResult(tableSum, start, stop);

	//^ Sequential ===================================================
	#pragma endregion

	return 0;
}