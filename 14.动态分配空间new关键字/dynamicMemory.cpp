#include <iostream>
using namespace std;

class Point{
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

int main(void){
	int x, y;
	Point *dynamicPoint;
	
	cout << "please input x and y of point position: " << endl;
	cin >> x >> y;
	
	/* 
	c++中使用new关键字来进行动态空间分配, 它比c语言的
	更方便(返回的类型为指针), 同样的new创建的空间, 在程序生存周期中必须手动删除
	使用delete删除
	*/ 
	dynamicPoint = new Point(x, y);
	cout << "x: " << dynamicPoint->getX() << "; y: " << dynamicPoint->getY() << endl;
	
	delete dynamicPoint;
	// 以下会出现垃圾数据
//	cout << "x: " << dynamicPoint->getX() << "; y: " << dynamicPoint->getY() << endl;
	
	// 使用new关键字动态开辟点集(数组)
	// 缺点是无法调用有参构造函数了
	dynamicPoint = new Point[4];
	// 分别给数组中的每个点设置坐标, 使用普通成员
	for (int i=0; i<4; i++){
		(dynamicPoint[i].setAxis)(i*2, i*2);
	};
	// 输出每个点的坐标
	for (int i=0; i<4; i++){
		cout << "i: " << i << "; x: " << dynamicPoint[i].getX() << "; y: " << dynamicPoint[i].getY() << endl;
	};
	
	// 此时删除使用 delete [] 指针名 的方式
	delete [] dynamicPoint;
	return 0;
}
