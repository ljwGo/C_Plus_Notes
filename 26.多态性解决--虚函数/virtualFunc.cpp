#include <iostream>
using namespace std;

// 特别的, 在继承链上,
// 析构函数需要注意使用虚析构函数
// 以保证是派生类的析构函数被调用

/*
	虚函数的实现原理,通过给每一个拥有虚函数的类准备一个
	虚函数表, 该虚函数表记录着指针, 指向每一个虚函数的函数体代码
	在实例化对象时, 对象中将会**隐含一个指针, 该指针指向虚函数表**
	当通过基类指针访问派生类实例的虚函数时,
	编译器不会根据基类指针的类型直接确定函数体代码
	而是**约定俗成的访问对象实例的隐含指针(该指针指向虚函数表)**
	通过查表的方式, 再到合适的函数
*/

// 交通工具类
class Transport{
	public:
		// 虚函数
		virtual void run(){
			cout << "交通工具运行了!!" << endl;
		}
};

// 车辆类
class Vehical:public Transport{
	public:
		// 由于与基类中的虚函数run的函数签名相同
		// 即使不写virtual, 该函数也默认为虚函数
		// 和C#就不同了, C#必须有override关键字修饰
		void run(){
			cout << "车辆运行了!!" << endl;
		}
};

// 汽车类
class Car:public Vehical{
	public:
		void run(){
			cout << "汽车运行了!!" << endl;
		}
};

// 货车类
class Truck:public Vehical{
	public:
		void run(){
			cout << "货车运行了!!" << endl;
		};
};

int main(void){
	// 生成交通工具指针
	Transport *p;
	Transport t1;
	Vehical v1;
	Car c1;
	Truck tk1;
	p = &t1;
	p->run();
	p = &v1;
	// 这里不是访问Transport部分的run函数体代码
	// 而是访问Vehical部分的隐含指针
	p->run();
	p = &c1;
	p->run();
	p = &tk1;
	p->run();
	// 理解参考图解
	return 0;
}