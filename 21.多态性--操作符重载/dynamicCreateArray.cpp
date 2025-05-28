#include <iostream>
using namespace std;

// 运算符重载的方式有两种
// 一种是类内重载
// 一种是类外重载

class Matrix{
	public:
		double *head; // 始终指向二维数组的首地址
		double *current_ele; // 指向二维数组当前元素的地址
//		通过向构造函数传递动态数组的大小, new构建二维数组失败了
//		Matrix(const int row, const int column);
//		我也不会调用模板化的构造函数
//		template <int ROW, int COLUMN> Matrix();
		Matrix();
//		Matrix(const int row, const int column);
		template <int ROW, int COLUMN> void init();
		void reset();
		void showMatrix();
		void showInfo();
	private:
		int row;
		int column;
};

//Matrix::Matrix(const int row, const int column){
//template <int ROW, int COLUMN>
Matrix::Matrix(){
//	这是无效的, head = new double[row][column]; // 动态创建矩阵
//	测试可行, head = (double *)new double[10][10];
//	测试可行, 使用真的常量值给模板函数
	const int row = 3;
//	测试可行, 使用真的常量值给模板函数
	const int column = 3;
	Matrix::init<row, column>();
};

//Matrix::Matrix(const int row, const int column){
//	Matrix::init<row, column>();
//};

// 通过模板化的方式, 向函数传递参数, 这时不会报错
template<int ROW, int COLUMN>
void Matrix::init(){
	this->row = ROW;
	this->column = COLUMN;
	head = (double *)new double[ROW][COLUMN];
	Matrix::reset();
};

void Matrix::reset(){
	for (int i=0; i<row; i++){
		for (int j=0; j<column; j++){
			cin >> *(head+i*row+j);
		}
	}
};
void Matrix::showMatrix(){
	for (int i=0; i<row; i++){
		for (int j=0; j<column; j++){
			cout << *(head+i*row+j) << " ";
		};
		cout << endl;
	};
};

void Matrix::showInfo(){
	cout << "row: " << row << endl;
	cout << "column: " << column << endl;
}


int main(void){
	Matrix m1;
	m1.showInfo();
	m1.showMatrix();

//  结论: 无法通过传递实参的方式, 决定new动态创建
//	const int row = 10;
//	const int column = 10;
//	Matrix m2(row, column);
//	m2.showInfo();
	return 0;
}
