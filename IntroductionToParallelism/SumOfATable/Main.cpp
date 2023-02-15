#include <iostream>
#include <vector>

#include <algorithm>
#include <chrono>

#include <thread>

using std::cout;
using std::endl;
using std::vector;

using namespace std::chrono;

static const int tableSize = 10000;

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
#pragma region Sequential Solution (more relevant comparison)
float sequentialSubTableSum(vector<float>& tableP, int subTableSizeP) {
	float sum{ 0.0f };

	//v Create sub tables ===================
	vector<vector<float>> subTables;
	int subTablesNumber = tableSize / subTableSizeP;

	for (int i = 0; i < subTablesNumber; i++)
	{
		subTables.emplace_back(tableP.begin() + i * subTableSizeP, tableP.begin() + i * subTableSizeP + subTableSizeP);
	}
	int remainingTableEntries = tableSize % subTableSizeP;
	// Create last sub table	
	if (remainingTableEntries != 0) {
		subTables.emplace_back(tableP.end() - remainingTableEntries, tableP.end());
	}
	//^ Create sub tables ===================

	// Launch threads
	for (vector<float>& subTable : subTables) {
		float subSum = sequentialTableSum(subTable);
		sum += subSum;
	}

	return sum;
};
#pragma endregion
#pragma region Local threads Solution
float localThreadsTableSum(vector<float>& tableP, int subTableSizeP) {
	vector<std::thread> threads;
	float sum{ 0.0f };

	//v Create sub tables ===================
	vector<vector<float>> subTables;
	int subTablesNumber = tableSize / subTableSizeP;

	for (int i = 0; i < subTablesNumber; i++)
	{
		subTables.emplace_back(tableP.begin() + i * subTableSizeP, tableP.begin() + i * subTableSizeP + subTableSizeP);
	}
	int remainingTableEntries = tableSize % subTableSizeP;
	// Create last sub table	
	if (remainingTableEntries != 0) {
		subTables.emplace_back(tableP.end() - remainingTableEntries, tableP.end());
	}
	//^ Create sub tables ===================

	// Launch threads
	for (vector<float>& subTable : subTables) {
		std::thread t(
			[=, &sum, &subTable] {
				float subSum = sequentialTableSum(subTable);
				sum += subSum;
			}
		);

		threads.push_back(std::move(t));
	}

	// Join threads
	for (std::thread& t : threads) {
		 t.join();
	}

	return sum;
};
#pragma endregion

int main() {
	//v Generate table ======================
	vector<float> table = generateTable(tableSize);
 
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
	#pragma endregion
	#pragma region Sequential (more relevant comparison)
	//v Sequential (more relevant comparison) ========================
	cout << "==== SEQ.2 ====" << endl;

	auto seq2Start = high_resolution_clock::now(); // <--- START TIMER
	float seq2TableSum = sequentialSubTableSum(table, 10);
	auto seq2Stop = high_resolution_clock::now(); // <--- STOP TIMER

	// Display results
	displayResult(seq2TableSum, seq2Start, seq2Stop);

	//^ Sequential (more relevant comparison) ========================
	#pragma endregion
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