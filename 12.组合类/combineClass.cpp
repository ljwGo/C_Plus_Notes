#include <iostream>
#include <cmath>
using namespace std;

// 组合类的特点, 我们在实例化一个类的同时(如Line类), 需要实例化另外的类(Point类)

class Point{
	friend class Line;
	public:
		Point();
		Point(int x, int y);
		int getX() const;
		int getY() const;
		void setAxis(int x, int y);
	private:
		int x;
		int y;
};
class Line{
	public:
		Line(const Point &p1, const Point &p2);
		double getLen() const;
		// 为了验证改变点是否影响线里面的点对象成员
		void showPoints() const;
	private:
		Point point01;
		Point point02;
		double len;
};

Point::Point(){
	x = 0;
	y = 0;
};
Point::Point(int x, int y): x(x), y(y){
};
int Point::getX() const{
	return x;
};
int Point::getY() const{
	return y;
};
void Point::setAxis(int x, int y){
	this->x = x;
	this->y = y;
}
Line::Line(const Point &p1, const Point &p2): point01(p1), point02(p2){
	int xOffset = point01.x - point02.x;
	int yOffset = point01.y - point02.y;
	len = static_cast<double>(sqrt(xOffset * xOffset + yOffset * yOffset));
};
double Line::getLen() const{
	return len;
};
void Line::showPoints() const{
	cout << "p1.x: " << point01.x << "; p1.y:" << point01.y << endl;
	cout << "p2.x: " << point02.x << "; p2.y:" << point02.y << endl;
}

int main(void){
	Point p1(1, 0), p2(4, 4);
	Line l1(p1, p2);
	cout << "len: " << l1.getLen() << endl;
	// 答案是并不会
	l1.showPoints();
	p1.setAxis(0, 0);
	l1.showPoints();
	return 0;
}
