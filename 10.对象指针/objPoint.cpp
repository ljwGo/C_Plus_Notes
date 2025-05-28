#include <iostream>
using namespace std;

class A{
	public:
		char getA();
		void setA(char a);
	private:
		char a = 'a';
};
char A::getA(){
	return a;
};
void A::setA(char a){
	this->a = a;
}

// 使用对象指针解决类中互相引用的问题
//class B{
//	class C; // 前向声明, 告诉编译器C是类
//	public:
//		C c;
//};
//class C{
//	public:
//		B b;
//};
// 之所以不行, 就是编译器需要确定B和C类的大小(字节),
// B的大小确立需要具体C的大小,C的大小确立需要B具体的大小

// 解决: 使用大小确定的对象指针, 而非对象
class B{
	class C; 
	public:
		// 指针的大小是确定的
		C *pc;
};
class C{
	public:
		B b;
};
// 使用指针需要注意一个问题, 就是它存的是地址,
// 而非一个真正的对象(不像类C, 实例化类C的同时, 成员对象b也会被实例化)
// 指针指向的对象由new关键字动态创建

int main(void){
	A a;
	A *pa = &a;
	// 使用方法同结构体指针
	pa->setA('c');
	cout << pa->getA() << endl;
	return 0;
}
