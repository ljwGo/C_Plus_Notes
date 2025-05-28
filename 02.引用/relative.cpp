#include <iostream>
using namespace std;

void func(int &a, int &b){
	a += 1;
	b += 1;
}

// 引用看作变量的别名, 可以看作地址传址的简化
int main(void){
	int x = 10;
	int y = 20;
	cout << "x: " << x << " y: " << y << endl;
	func(x, y);
	cout << "x: " << x << " y: " << y << endl;
	return 0;
}

