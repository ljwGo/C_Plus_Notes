#include <iostream>
using namespace std;

class A{
	public:
		A(char a){
			this->a = a; 
		};
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

class D{
	public:
		D(char d){
			this->d = d;
		}
		char d;
};

class C: public B{
//	class D; // 前向声明
	public:
		C(char c, char b, char a, char d): B(b, a), d(d){
			this->c = c; 
		};
		void showABCD(){
			cout << a << b << c << d.d << endl;
		}
//	protected:
//		char c;
	private:
		char c;
		D d;
};


// 从上面的代码, 我们可以看到A, B, C, D 4个类的关系是
// A->B->C, A是基类, D是C的组合类
// 继承链上直接相连的被称为直接基类
// 派生类负责直接基类的初始化
// 和组合类一样, 是在构造函数的初始化列表中调用直接基类的构造函数
// 基类构造函数的调用顺序为类继承基类的顺序(c++支持多继承), 再到组合类
/*
	class 类名: 基类1, 基类2 ... {
		public:
			类名(参数列表): 基类1(参数), 基类2(参数) ... ,组合类对象字段(参数)...{
				...
			}
		private:
			组合类1 标识符;
			组合类2 标识符;
			...
	}
*/

int main(void){
	C c1('c', 'b', 'a', 'd');
	c1.showABCD();
	return 0;
}
