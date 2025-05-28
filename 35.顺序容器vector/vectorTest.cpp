#include <iostream>
#include <vector>
using namespace std;

int main(void){
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
//	v.erase(2); // 是错误的, erase好像只重载了指针类型

//	cout << v.size() << endl;
//	
//	v.push_back(10);
//	cout << v.size() << endl;
//	cout << v.max_size() << endl;
//	
//	v.pop_back();
//	cout << v.size() << endl;
//	
//	// 访问最后一个元素?  奇怪, 10应该被删除了, 但是还能够被访问
//	cout << v[v.size()] << endl;
//
////	cout << v[v.size() - 1] << endl;
//	v.push_back(20);
//	cout << v[2] << endl;
//	
//	v.erase(v.begin());
//	cout << v[0] << endl;
	return 0;
}
