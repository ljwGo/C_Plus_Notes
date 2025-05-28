#include <iostream>
// 里面有许多 操作符, 操作符和插入运算符共同作用, 控制输出流的格式
#include <iomanip>
using namespace std;

int main(void){
	// setw调整占位数
	cout << setw(10) << "10" << endl;
	// width也能够做到
	cout.width(10);
	cout << "20" << endl;
	// setiosflags()支持更多的格式控制, 其具体参数参考图片
	return 0;
}
