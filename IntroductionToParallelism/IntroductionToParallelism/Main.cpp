#include <iostream>
#include <thread>

#include <vector>

using std::cout;
using std::endl;

using std::vector;

void sayHello() {
	cout << "Hello world" << endl;
}

struct Matrix
{
	Matrix(std::vector<float> contentP, int widthP, int heightP) :
		content{contentP},
		width{widthP},
		height{heightP}
	{};

	std::vector<float> content{ NULL };
	int width{ 1 };
	int height{ 1 };
};

void displayMatrix(Matrix& matrixP) {
	for (int i = 0; i < matrixP.width; i++)
	{
		for (int j = 0; j < matrixP.height; j++) {
			cout << matrixP.content[j + i * matrixP.width] << " ";
		}
		cout << "\n";
	}
}

float singleNumberCalculus(vector<float>& rowP, vector<float>& colP, int sizeP) {
	float result{ 0.0f };

	for (int i = 0; i < sizeP; i++)
	{
		result += rowP[i] * colP[i];
	}

	return result;
}

vector<float> getMatrixColByIndex(Matrix& matrixP, int indexP) {
	vector<float> result;
	
	for (int i = 0; i < matrixP.height; i++)
	{
		result.push_back(matrixP.content[indexP + i * matrixP.width]);
	}

	return result;
}

Matrix matrixProduct(Matrix& aMatrixP, Matrix& bMatrixP) {
	vector<std::thread> threads;

	size_t resultMatrixSize = bMatrixP.width * bMatrixP.height;
	vector<float> resultMatrixContent;
	resultMatrixContent.reserve(resultMatrixSize);

	if (aMatrixP.width != bMatrixP.height)
	{
		cout << "YOU CAN'T MULTIPLY THOSE TWO MATRICES" << endl;

		Matrix errorMatrix{
			{ 0.0f },
			1,
			1
		};

		return errorMatrix;
	}
	
	for (int height = 0; height < bMatrixP.height; height++)
	{
		vector<float> aMatrixRow{
			aMatrixP.content.begin() + height * aMatrixP.width,
			aMatrixP.content.begin() + height * aMatrixP.width + aMatrixP.width
		};

		for (int width = 0; width < bMatrixP.width; width++) {
			vector<float> bMatrixCol = getMatrixColByIndex(bMatrixP, width);

			std::thread t(
				[&] {
					float result = singleNumberCalculus(aMatrixRow, bMatrixCol, aMatrixP.width);

					int currentIndex = width + height * bMatrixP.width;
					resultMatrixContent[currentIndex] = result;
				}
			);		

			threads.push_back(std::move(t));
		}
	}

	for (std::thread& t : threads)
	{
		t.join();
	}

	Matrix resultMatrix(
		resultMatrixContent,
		bMatrixP.width,
		bMatrixP.height
	);

	return  resultMatrix;
}

int main() {
	//std::thread t{ sayHello };

	//t.join(); // Wait for the thread

	Matrix aMatrix{
		{
			2.0, 0.0, 0.0,
			0.0, 2.0, 0.0,
			0.0, 0.0, 3.0
		},
		3,
		3
	};
	Matrix bMatrix{
		{
			2.0, 4.0, 2.0,
			4.0, 1.0, 3.0,
			2.0, 3.0, 1.0
		},
		3,
		3
	};

	Matrix resultMatrix = matrixProduct(aMatrix, bMatrix);

	displayMatrix(resultMatrix);

	return 0;
}