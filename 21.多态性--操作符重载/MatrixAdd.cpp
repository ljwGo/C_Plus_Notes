#include <iostream>
#include <assert.h>
using namespace std;

// 运算符重载的方式有两种
// 一种是类内重载
// 一种是类外重载

// 本次演示类内重载
// 类内重载的特点:
// 	(1)若重载双目运算符X后, 执行 A类 + B类 的表达式
// 	将会调用A中对X的重载函数(说明是有顺序的)
// 	A并不会被传入到重载函数中, 只有右操作数B会被传入其中

class Matrix{
	public:
		double *head; // 始终指向二维数组的首地址
		double *current_ele; // 指向二维数组当前元素的地址
		Matrix(); // 无参构造函数
		Matrix(int row, int column); // 有参构造函数
		Matrix(const Matrix &m); // 拷贝构造函数
		~Matrix(); // 析构函数
		void init(); // 初始化函数
		void reset(); // 重置矩阵的值
		void showMatrix(); // 打印矩阵
		void showInfo(); // 显示矩阵的属性
		// 重载+, 使得Matrix类能够支持+
		Matrix operator + (const Matrix &m2);
		Matrix & operator = (const Matrix &m2);
	private:
		int row;
		int column;
};

Matrix::Matrix(){
	Matrix::init();
};
Matrix::Matrix(int row, int column){
	this->row = row;
	this->column = column;
	head = new double[row*column];
};
Matrix::Matrix(const Matrix &m){
	this->row = m.row;
	this->column = m.column;
	head = new double[row*column];
	for (int i=0; i<row*column; i++){
		*(head+i) = *(m.head+i);
	}
}
Matrix::~Matrix(){
	delete [] head;
}
void Matrix::init(){
	cout << "please input row and column of Matrix:" << endl;
	cin >> row;
	cin >> column;
//	head = (double *)new double[row][column];
	// 妈的, 创建二维数组,两个值必须是常值
	// 创建一维数组就没问题,可恶
	head = new double[row*column];
};
void Matrix::reset(){
	cout << "please input specific value of Matrix:" << endl;
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
Matrix Matrix::operator + (const Matrix &m){
	// 作用似乎是为真时结束程序?
	// false时截断; true继续执行
	assert(this->row == m.row && this->column == m.column);
	Matrix m1(this->row, this->column);
//	Matrix *m1 = new Matrix(this->row, this->column);
	for (int i=0; i<row*column; i++){
		*(m1.head+i) = *(this->head+i) + *(m.head+i);
	};
	return m1;
}
Matrix &Matrix::operator = (const Matrix &m){
	// 如果赋值右边不是自身
	if (&m != this){
		if (m.row != this->row || m.column != this->column){
			// 删除原本的矩阵
			delete [] head;
			// 更新属性
			row = m.row;
			column = m.column;
			// 新建矩阵
			head = new double[m.row*m.column];
		};
		// 更新值 
		for (int i=0; i<row*column; i++){
			*(head+i) = *(m.head+i);
		}
	};
	return *this;
}

int main(void){
	Matrix m1;
//	m1.showInfo();
//	m1.showMatrix();
	m1.reset();
//	m1.showMatrix();
	
	Matrix m2;
//	m2.showInfo();
//	m2.showMatrix();
	m2.reset();
//	m2.showMatrix();
	
	Matrix m3(1, 1);
	m3.showInfo();
	m3.showMatrix();
	m3 = (m1 + m2);
	m3.showInfo();
	m3.showMatrix();

	Matrix m4 = Matrix(2 ,1);
	m4.showInfo();
//  麻了, 下面的表达式是合法的
//	int test;
//	cin >> test;
//	int a[test];
//	int *b = new int[test];
//	cout << a[2] << endl;
	return 0;
}