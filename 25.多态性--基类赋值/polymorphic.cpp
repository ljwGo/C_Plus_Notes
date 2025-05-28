#include <iostream>
using namespace std;

// 交通工具类
class Transport{
	public:
		void run(){
			cout << "交通工具运行了!!" << endl;
		}
};

// 车辆类
class Vehical:public Transport{
	public:
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
	// 很好理解, 汽车和货车也是车辆, 车辆也是交通工具的一类
	// 所以交通工具的指针能够指向它的**所有派生类对象**
	p = &t1;
	p->run();
	p = &v1;
	p->run();
	p = &c1;
	p->run();
	p = &tk1;
	p->run();
	// 但是, 输出结果和我们想的不一样
	// 都是输出**交通工具运行了!!**
	
	/*
		按老实所说的原因, 是因为C++是编译语言的原因
		当编译到p->run()语句时, 必须给出对应机器码
		此时只知道p的数据类型, 所以编译器就把p指向的都
		作为Transport类对待
		记住, 编译语言是无法预知程序执行的状态的
	*/
	return 0;
}
