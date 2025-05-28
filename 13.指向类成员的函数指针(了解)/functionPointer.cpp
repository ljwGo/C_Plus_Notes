#include <iostream>
using namespace std;

// 函数指针常常使用在传入的参数为 函数 的情况
// 函数本质是一段被分割的代码, 传入函数, 自定义一些流程代码

class A{
	public:
		char a(int count){
			return 'a'; 
		}
};

int main(void){
	// 1.定义一个指向类函数的指针类型
	char (A::*pa)(int);
	// 2.将该指针指向类的成员函数
	pa = A::a;
	// 3.在具体对象中使用该函数
	A a1;
	cout << (a1.*pa)(1) << endl;
	
	return 0;
}
