#include <iostream>
#include <assert.h>
using namespace std;

// 运算符重载的方式有两种
// 一种是类内重载
// 一种是类外重载

// 本次演示类内重载
// 类内重载的特点:
// 	(1)若重载双目运算符X后, 执行 A类 + B类 的表达式
// 	将会调用A中对X的重载函数(说明是有顺序的), 并将A自动传进该重载函数中
// 	作为第一个实参, B的对象则作为第二个实参
//  (2)* . .* () 等运算符不允许重载

class Matrix{
	public:
		double *head; // 始终指向二维数组的首地址
		double *current_ele; // 指向二维数组当前元素的地址
		Matrix(); // 无参构造函数
		Matrix(int row, int column);
		void init(); // 初始化函数
		void reset(); // 重置矩阵的值
		void showMatrix(); // 打印矩阵
		void showInfo(); // 显示矩阵的属性
		// 重载+, 使得Matrix类能够支持+
		Matrix & operator + (const Matrix &m2);
		friend Matrix & operator + (const Matrix &m2);
	private:
		int row;
		int column;
};

Matrix::Matrix(){
	Matrix::init();
};

Matrix::Matrix(int row, int column){
	head = new double[row*column];
	this->row = row;
	this->column = column;
}

void Matrix::init(){
	cout << "please input row and column of Matrix:" << endl;
	int row;
	int column;
	cin >> row;
	cin >> column;
//	head = (double *)new double[row][column];
	// 妈的, 创建二维数组,两个值必须是常值
	// 创建一维数组就没问题,可恶
	head = new double[row*column];
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
// 双目运算符的左操作数(即本身)不会被作为实参传入, 使用this直接访问
Matrix & Matrix::operator + (const Matrix &m2){
	// 作用似乎是为真时结束程序?
	assert(this->row != m2.row || this->column != m2.column);
	Matrix m1(this->row, this->column);
	for (int i=0; i<row*column; i++){
		*(m1.head+i) = *(this->head+i) + *(m2.head+i);
	};
	return m1;
}

int main(void){
	Matrix m1;
	Matrix m2;
	Matrix m3 = m1 + m2;

//  麻了, 下面的表达式是合法的
//	int test;
//	cin >> test;
//	int a[test];
//	int *b = new int[test];
//	cout << a[2] << endl;
	return 0;
}

