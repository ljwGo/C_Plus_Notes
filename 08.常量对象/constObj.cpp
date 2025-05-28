#include <iostream>
using namespace std;

class Point{
	public:
		Point();
		Point(Point &p);
		Point(int x, int y): x(x), y(y){
		}
//		int getY();
		// 常对象必须使用常函数
		// 常对象必须在函数 后面 添加const关键字
		// 后面的const也是函数重载的依据之一
		int getX() const;
		int getY() const;
		void setAxis(int x, int y);
		int getV() const{
			return v;
		}
		void setV(int v) const{
			this->v = v;
		}
	private:
		int x;
		int y;
		// 该成员只能够在构造函数的初始化列表处初始化或直接赋值
		const int z = 0;
		// mutable慎用, 因为该修饰符会破坏常对象的规则
		// 也就是说, 可以在常对象中改变该属性
		mutable int v = 1;
};

Point::Point(){
	x = 0;
	y = 0;
};
Point::Point(Point &p){
	x = p.x * 2;
	y = p.y * 2;
}
//int Point:getX(){
//	return x;
//};
int Point::getX() const{
	return x;
}
//int Point::getY(){
//	return y;
//};
int Point::getY() const {
	return y;
}
void Point::setAxis(int x, int y){
	this->x = x;
	this->y = y;
};

int main(void){
	// 如果使用无参构造函数实例化对象, 不需要使用()
	Point p1;
	Point p2(1, 2);
	Point p3(p2);
	cout << "p1: (" << p1.getX() << "," << p1.getY() << ") " << endl;
	cout << "p2: (" << p2.getX() << "," << p2.getY() << ") " << endl;
	cout << "p3: (" << p3.getX() << "," << p3.getY() << ") " << endl;
	// 使用const修饰的对象, 其成员的值自初始化后就不能够被改变
	const Point p4(2,3);
	// 下面将会报错, 因为它修改了对象成员的值
//	p4.setAxis(3,4);
	// 这理论上不会报错, 因为它仅仅使用了值, 而未修改
	// 需要在类中显示声明该方法是无副作用的, 在getX和getY后添加const
	cout << "p4: (" << p4.getX() << "," << p4.getY() << ") " << endl;
	/* 
	需要注意的是常函数也能够被非常对象使用, 所以最好在确定该函数不会
	修改对象成员时, 添加上const
	*/
	
	/*
	试了一下, 下面的内容是错误的, 常对象可以在构造体函数体部分初始化
	不能够在构造体内赋值的情况是成员本身是常量
	*/
	// 常对象的所有数据只能够初始化, 而不能赋值
	// 在类的构造函数中, 只能够在初始化列表(: 后面)中,
	// 在构造函数的函数体内算作赋值
	const Point p5(p3);
	cout << "p5: (" << p5.getX() << "," << p5.getY() << ") " << endl;
//	p5.setAxis(1, 2);
	p5.setV(10);
	cout << "p5 v:" << p5.getV() << endl;
	return 0;
}
