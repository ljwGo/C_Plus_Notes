#include <iostream>
// 文件输出流内置对象
#include <fstream>

/*
	cout 标准输出流(windows默认输入io设备是显示器)
	cerr 标准错误流, 无缓冲
	clog 有缓存, 缓存满后写入文件
*/

using namespace std;

int main(void){
	// 创建用于输出的文件对象
	ofstream myFile("./test.txt", ios_base::out | ios_base::binary);
	// 修改cout的输出方向, 不再是显示器, 而是文件(重定向到磁盘io设备)
	// cout.rdbuf(myFile.rdbuf())意思是将myFile的缓冲区设置为cout的缓冲区?? 不知道这样理解对不对
	// streambuf * pOld是旧的缓冲区, 这里就是显示器的缓冲, 显示器的接口?(io设备寄存器)
	streambuf * pOld = cout.rdbuf(myFile.rdbuf());
	cout << "我出现在文件中了, 理想中" << endl;
	// cout还原
	cout.rdbuf(pOld);
	cout << "我出现在显示器中, 说明还原了" << endl;
	return 0;
}
