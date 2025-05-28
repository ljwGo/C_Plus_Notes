#include <iostream>
using namespace std;

// 测试广度优先还是深度优先

class A{
	public:
		A(char a){
			this->a = a; 
		};
		void sayHello(){
			cout << "response in A deep access!" << endl;
		}
	protected:
		char a;
};

class B: public A{
	public:
		B(char b, char a): A(a){
			this->b = b;
		};
	protected:
		char b;
};

class C{
	public:
		C(char c){
			this->c = c; 
		};
		void sayHello(){
			cout << "response in C width access!" << endl;
		}
	private:
		char c;
};

class D: public B, public C{
	public:
		D(char d, char c, char b, char a): B(b, a), C(c){
			this->d = d;
		}
		char d;
//		void sayHello(){
//			// 本类有的话, 不会出错
//			A::sayHello();
//		}
};

int main(void){
	D d1('d', 'c', 'b', 'a');
	// 测试证明c++中没有广度和深度优先的概念
	// 会有二义性, 直接报错
//	d1.sayHello();
	// 二义性解决, 添加名称空间限制
	d1.A::sayHello();
	return 0;
}
