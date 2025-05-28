#include <iostream>
using namespace std;

class Point{
	public:
		Point();
		Point(Point &p);
		Point(int x, int y): x(x), y(y){
			count++;
		};
		// 静态成员, 能够类的所有对象访问, 也能直接通过类进行访问 
		// 记录点对象的个数
		static int count;
		// 析构函数, 当点对象被销毁时, 自动减一
		~Point(){
			count--;
		}
		int getX() const;
		int getY() const;
		void setAxis(int x, int y);
	private:
		int x;
		int y;
};

Point::Point(){
	x = 0;
	y = 0;
	count++;
};
Point::Point(Point &p){
	x = p.x;
	y = p.y;
	count++;
}
int Point::getX() const{
	return x;
}
int Point::getY() const {
	return y;
}
void Point::setAxis(int x, int y){
	this->x = x;
	this->y = y;
};
// 给静态成员赋值
int Point::count = 0;

int main(void){
	Point p1;
	cout << "count: " << Point::count << endl;
	Point p2(2,3);
	// 说明当对象在本作用域中找不到成员时, 会访问类中的静态成员
	cout << "count: " << p2.count << endl;
	Point p3(p1);
	cout << "count: " << Point::count << endl;
	return 0;
}
