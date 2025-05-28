#include <iostream>
#include "Point.h"
using namespace std;

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
};
void Point::showPosition(){
	cout << "x: " << x << "; y: " << y << endl;
};
void Point::move(int xOffset, int yOffset){
	x += xOffset;
	y += yOffset;
}
