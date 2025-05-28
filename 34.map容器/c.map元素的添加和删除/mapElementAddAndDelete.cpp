#include <iostream>
#include <map>
using namespace std;

int main(void){
	map<string, int> m;
	m["hello"] = 1;
	// 使用[]和索引的方式
	cout << m["hello"] << endl;
	m["hello"] = 2;
	cout << m["hello"] << endl;
	// 访问为赋值的项, 默认值为0
	cout << m["noInit"] << endl;
	// 删除已经存在的
	m.erase("hello");
	cout << m["hello"] << endl;
	// 删除不存在的
	m.erase("noExist");
	return 0;
}
