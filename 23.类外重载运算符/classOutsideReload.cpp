#include <iostream>
#include <assert.h>
using namespace std;

// 本次演示类外重载
// 使得cout可以作用域矩阵类, 打印出矩阵的样子
// 而不再使用自定义方法showMatrix

/*
	重载<<插入运算符
	cout似乎是std::ostream的一个实例
	cout << Matrix;
	相当于 std::ostream(cout)::operator<<(Matrix &m);
	我们无法到ostream类中写入重载代码, 所以只能是类外了
	和类内不同, 左右操作数都会被传入到重载函数中
*/

class Matrix{
	public:
		double *head; // 始终指向二维数组的首地址
		Matrix(); // 无参构造函数
		Matrix(int row, int column); // 有参构造函数
		Matrix(const Matrix &m); // 拷贝构造函数
		~Matrix(); // 析构函数
		void init(); // 初始化函数(键盘输入)
		void reset(); // 重置矩阵的值(键盘输入)
		void resetAuto(); // 重置矩阵的值全为0
		void showMatrix() const; // 打印矩阵
		void showInfo() const; // 显示矩阵的属性
		// 重载+, 使得Matrix类能够支持+
		Matrix operator + (const Matrix &m);
		Matrix & operator = (const Matrix &m);
		// 前置++
		Matrix & operator ++ ();
		// 为了和后置++进行区分, 后缀++参数列表多出一个int形参
		Matrix operator ++(int);
		// 对类外的插入运算符重载设置为友元
		friend void operator<< (std::ostream &out, Matrix &m);
	private:
		unsigned int row;
		unsigned int column;
		unsigned int amount; // 元素总数
};

void operator<< (std::ostream &out, Matrix &m);
void operator<< (std::ostream &out, Matrix &m){
	for (int i=0; i<m.row; i++){
		for (int j=0; j<m.column; j++){
			out << *(m.head+i*m.row+j) << " ";
		};
		out << endl;
	};
}

Matrix::Matrix(){
	Matrix::init();
};
Matrix::Matrix(int row, int column){
	this->row = row;
	this->column = column;
	this->amount = row * column;
	head = new double[amount];
};
Matrix::Matrix(const Matrix &m){
	this->row = m.row;
	this->column = m.column;
	this->amount = m.amount;
	head = new double[amount];
	for (int i=0; i<amount; i++){
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
	amount = row * column;
	head = new double[row*column];
};
void Matrix::reset(){
	cout << "please input specific value of Matrix:" << endl;
	for (int i=0; i<amount; i++){
		cin >> *(head + i);
	}
};
void Matrix::resetAuto(){
	for (int i=0; i<amount; i++){
		*(head+i) = 0;
	}
}
void Matrix::showMatrix() const{
	for (int i=0; i<row; i++){
		for (int j=0; j<column; j++){
			cout << *(head+i*row+j) << " ";
		};
		cout << endl;
	};
};
void Matrix::showInfo() const{
	cout << "row: " << row << endl;
	cout << "column: " << column << endl;
	cout << "amount: " << amount << endl;
}
Matrix Matrix::operator + (const Matrix &m){
	// 矩阵必须等宽登高才能进行加法
	assert(this->row == m.row && this->column == m.column);
	// 新建临时Matrix对象,存放结果
	Matrix m1(this->row, this->column);
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
};
Matrix &Matrix::operator ++ (){
	//先自增, 在返回本身
	for (int i=0; i<amount; i++){
		++(*(head+i));
	}
	return *this;
}
// 好像能够直接写0
Matrix Matrix::operator++ (int temp){
	// 创建临时的矩阵对象用于返回
	Matrix m(*this);
	// 调用前置++
	++(*this);
	// 返回值不能是引用, 不然无法做到先用原来的值, 在自增的目的
	return m;
}

int main(void){
	Matrix m(2,3);
	m.resetAuto();
	m++;
	cout << m;
	Matrix m2 = m + m;
	cout << m2;
	return 0;
}
