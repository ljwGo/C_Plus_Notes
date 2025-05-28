#include <iostream>
using namespace std;

// 虚基类有一个最大问题, 就是继承链上的每个派生类都需要给最远虚基类传递参数
// 当然, 只有最远派生类传递参数会被使用
// 但是, 其它派生类依旧传递参数(保证形式), 尽管不会被使用

class A{
	// 虚基类必须给它一个无参构造函数
	public:
		A(){
			;
		}
		A(char a){
			this->a = a; 
		};
		void sayHello(){
			cout << "hello in A" << endl;
		}
	protected:
		char a;
};

class B: virtual public A{
	public:
		B(char b){
			this->b = b;
		};
	protected:
		char b;
};

class C: virtual public A{
	public:
		C(char c){
			this->c = c; 
		};
	private:
		char c;
};

class D: public B, public C{
	public:
		// 在这里给A的构造函数传递参数
		D(char d, char c, char b, char a): B(b), C(c), A(a){
			this->d = d;
		}
		char d;
};

int main(void){
	// 请看继承关系图
	// 菱形关系图会带来二义性问题
	D d1('d', 'c', 'b', 'a');
	// 而且也不符合逻辑, 因为需要从B和C中重复对A进行两次实例化
	d1.sayHello();	
	// 虚基类, 在共同继承一个类时, 使用virtual关键字
	// 虚基类的实例化(调用构造函数), 在最远的派生类处
	return 0;
}
