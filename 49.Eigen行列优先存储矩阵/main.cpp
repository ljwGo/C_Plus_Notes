#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

int main(void) {
	Matrix<int, 3, 3, ColMajor> colMatrix;
	colMatrix << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;

	cout << "column major matrix: \n" << colMatrix;
	cout << endl;
	cout << "column major data layout: \n";
	for (int i = 0; i < colMatrix.size() ; ++i) {
		cout << *(colMatrix.data() + i) << " ,";
	}
	cout << endl;
	// ()确实是row, column索引; 与矩阵是行列优先无关
	cout << colMatrix(2, 0) << endl;
	cout << colMatrix(2, 1) << endl;
	cout << colMatrix(2, 2) << endl;

	Matrix<int, 3, 3, RowMajor> rowMajor;
	rowMajor << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;

	cout << "row major matrix: \n" << rowMajor;
	cout << endl;
	cout << "row major data layout: \n";
	for (int i = 0; i < rowMajor.size() ; ++i) {
		cout << *(rowMajor.data() + i) << " ,";
	}
	cout << endl;
	// ()确实是row, column索引; 与矩阵是行列优先无关
	cout << rowMajor(2, 0) << endl;
	cout << rowMajor(2, 1) << endl;
	cout << rowMajor(2, 2) << endl;
}