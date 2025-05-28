#include <iostream>
using namespace std;

/*
	函数模板可以
	省略多个类型不同, 但逻辑相同或类似的
	函数重载
	本质可以理解为函数重载的简写或者统一
	(原因, 编译器会根据函数模板和程序中的具体使用
	生成对应类型的重载函数
	是切切实实占用内存的
	)
*/

// template关键字表示后面<>内的
// 标识符将作为指定类型的**占位符**
template <typename T>
// 通用加法
T add(T n1, T n2){
	return n1 + n2;
}
// 通用乘法
template <typename T> T multiply(T n1, T n2){
	return n1 * n2;
}

// 甚至是将字面量作为参数传入
template <int SIZE, class T> T *newArray(){
	return new T[SIZE]; // 调用T的无参构造函数
}

char little = 'a';
class A{
	public:
		A(){
			a = little++;
		}
		char a;
};

/*
	可见, 模板可以将基本数据类型, 自定义类(类型), 甚至是字面量
	作为参数传入到模板中, 构成具现化的函数
*/

int main(void){
	// add只是模板, add<类型typename>是模板具现化
//	cout << add<int>(1, 3) << endl;
//	cout << add<double>(2.3, 3) << endl;
//  cout << multiply<double>(2.3, 3) << endl;
	const int n = 10;
	A *pa;
	
	pa = newArray<n, A>();
	for (int i=0; i<n; i++){
		cout << (pa+i)->a << endl;
	}
	
	return 0;
}
