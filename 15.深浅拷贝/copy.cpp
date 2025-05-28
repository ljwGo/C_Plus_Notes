#include <iostream>
#include <cmath>
#include "../Point.cpp" // 看来支持相对路径
using namespace std;

class Line{
	public:
		Line(const Point *p1, const Point *p2);
		double getLen() const;
		void showPoints() const;
		// 深拷贝构造函数
		Line(const Line &line){
			len = line.getLen();
			// 简单赋值
			// point01 = line.point01;
			// point02 = line.point02;
			// 无语, 一是不能简化语法(也许是必须要有变量名指向的空间存放对象吧, 毕竟指针不存放本体), 
			// 二是我将指针指向了构造函数内的局部变量, 居然没事
			Point point1(*(line.point01));
			Point point2(*(line.point02));
			point01 = &point1;
			point02 = &point2;
		}
	private:
		// 点成员改为指针, 而非点对象
		// 奇怪, 命名指针指向的常对象类型, 结果后面能够调用move方法, 该方法会改变对象成员值
		const Point *point01;
		const Point *point02;
		double len;
};
Line::Line(const Point *p1, const Point *p2): point01(p1), point02(p2){
	int xOffset = (*point01).x - (*point02).x;
	int yOffset = (*point01).y - (*point02).y;
	len = static_cast<double>(sqrt(xOffset * xOffset + yOffset * yOffset));
};
double Line::getLen() const{
	return len;
};
void Line::showPoints() const{
	cout << "p1.x: " << point01->x << "; p1.y:" << point01->y << endl;
	cout << "p2.x: " << point02->x << "; p2.y:" << point02->y << endl;
}

int main(void){
	Point p1(1,2), p2(2,3);
	Line l1(&p1, &p2);
	Line l2(l1);
	
	l1.showPoints();
	l2.showPoints();
	p1.move(1, 2);
	// 发现, 改变了p1点, 结果l1和l2都改变了.
	// 原因是默认的拷贝构造函数, 只是将对象1和对象2的值简单的一一对应赋值而已
	// 图解
	// 想要做到l1和l2的数据彼此隔离, 需要做到深拷贝
	// 深拷贝, 需要手动书写一个线对象的拷贝构造函数, 
	// 在里面利用点的拷贝构造函数, 生成新的点
	l1.showPoints();
	l2.showPoints();
	return 0;
}
