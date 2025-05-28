#include <iostream>
using namespace std;

// 在类中设置友元, 使得指定的友元能够访问该类中的私有和保护成员
// 在使用友元的过程中, 常搭配const关键字, 使得你能够使用
// 数据, 但是不能够修改, 来达到保证安全的目的

class A{
	// 给另外一个类设置友元
	friend class B;
	// 给其它类的某个具体方法设置为友元失败了!!
//	friend C::funcC1; 失败了
//	friend class C; 成功了
	// 本类的方法设置默认为本类其它对象的友元
	public:
		void funcB(A &a1, A &a2);
	private:
		char a = 'a';
};

class C{
	public:
		void funcC1(A &a);
};

void A::funcB(A &a1, A &a2){
	cout << a1.a << a2.a << endl;
};

void C::funcC1(A &a){
	cout << a.a << endl;
}

class B{
	private:
		char b = 'b';
	public:
		void showBmember(A &a){
			cout << a.a << endl;
		};
};


int main(void){
	A a = A();
	B b = B();
	C c = C();
	A a1 = A(), a2 = A();
	// b访问a中的私有属性
	b.showBmember(a);
	// a访问另外的A类中的属性
	a.funcB(a1, a2);
	c.funcC1(a);
//	c.funcC2(a);
	return 0;
}
