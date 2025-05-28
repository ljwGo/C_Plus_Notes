#include <iostream>
using namespace std;

// c++ 类的继承有三种方式
// 方式一: public 也是最常用的方式
// 		这种方式的特点是, 从基类继承下来的public和protected成员
//		都保持不变, 基类的private成员依旧不能被访问
// 方式二: private
//  	从基类继承下来的public和protected成员都会变为private
//		但是仍能够通过特殊方式访问
// 		private成员依旧无法访问
//      其次, 后续的继承, 无论是什么方式, 所有继承下来的成员都是private属性
// 方式三: protected
// 		从基类继承下来的public和protected成员都会变为protected
// 		private成员依旧无法访问
//      其次, 后续的继承, 无论是什么方式, 所有继承下来的成员都是protected属性

class A{
	public:
		A(char a){
			this->pro_a = a;
			this->pri_a = a;
		};
		void showAPosition(){
			cout << "in A" << endl;
		}
	protected:
		char pro_a;
	private:
		char pri_a;
};

class B: public A{
	public:
		B(char b, char a): A(a){
			this->pro_b = b;
			this->pri_b = b;
		};
		void showBPosition(){
			cout << "in B" << endl;
		}
	protected:
		char pro_b;
	private:
		char pri_b;
};

class C: private B{
	// 私有继承, 仅在C中能够通过指名方式访问B
//	class D; 前向声明必须配合对象内的引用或者指针
	public:
		C(char c, char b, char a): B(b, a){
			this->pri_c = c;
			this->pro_c = c; 
		};
		void showCPosition(){
			cout << "in C" << endl;
		};
		void showBinC(){
			// 错误的: 只能利用指明的方式, 
			// 测试结果是都可以, 只是, 继续继承C的将无法访问A和B
			showBPosition();
//			B::showBPosition();
		}
	private:
		char pri_c;
	protected:
		char pro_c;
	
};

class D: public C{
	// 编译方面就不让通过了, 毕竟C继承B的方式是private, D无法访问A和B中的成员
	public:
		D(char d, char c, char b, char a): C(c, b, a){
			this->pro_d = d;
			this->pri_d = d;
		}
		void showABCD(){
//			cout << pro_a << pro_b << pro_c << pro_d << endl;
		}
	private:
		char pri_d;
	protected:
		char pro_d;
};

int main(void){
	C c1('c', 'b', 'a');
	D d1('d', 'c', 'b', 'a');
	c1.showCPosition();
	c1.showBinC();
	d1.showABCD();
	// 虽然无法访问C继承的B和A,但是C本身的成员还是能够访问的
	d1.showCPosition();
	return 0;
}
