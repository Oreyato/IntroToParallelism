#include <iostream>
#include <vector>

#include <algorithm>
#include <chrono>

#include <thread>

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
	cout << "Time taken: " << duration.count() << " microseconds\n" << endl;
}
#pragma endregion

#pragma region Sequential Solution
float sequentialTableSum(vector<float>& tableP) {
	float sum{ 0.0f };

	for (float& val : tableP) {
		sum += val;
	}

	return sum;
}
#pragma endregion

#pragma region Local threads Solution
float localThreadsTableSum(vector<float>& tableP, int subTableSizeP) {
	vector<std::thread> threads;
	float sum{ 0.0f };

	vector<vector<float>> subTables;

	for (vector<float> subTable : subTables) {
		std::thread t(
			[=, &sum, &subTable] {
				float subSum = sequentialTableSum(subTable);
				sum += subSum;
			}
		);

		threads.push_back(std::move(t));
	}

	for (std::thread& t : threads) {
		t.join();
	}

	return sum;
};
#pragma endregion

int main() {
	//v Generate table ======================
	vector<float> table = generateTable(100000);
 
	//^ Generate table ======================

	#pragma region Sequential
	//v Sequential ===================================================
	cout << "===== SEQ =====" << endl;

	auto seqStart = high_resolution_clock::now(); // <--- START TIMER
	float seqTableSum = sequentialTableSum(table);
	auto seqStop = high_resolution_clock::now(); // <--- STOP TIMER

	// Display results
	displayResult(seqTableSum, seqStart, seqStop);

	//^ Sequential ===================================================
	#pragma region Local threads
	//v Local threads ================================================
	cout << "===== LTH =====" << endl;

	auto lThreadStart = high_resolution_clock::now(); // <--- START TIMER
	float lThreadTableSum = localThreadsTableSum(table, 10);
	auto lThreadStop = high_resolution_clock::now(); // <--- STOP TIMER

	// Display results
	displayResult(lThreadTableSum, lThreadStart, lThreadStop);

	//v Local threads ================================================
	#pragma endregion

	return 0;
}