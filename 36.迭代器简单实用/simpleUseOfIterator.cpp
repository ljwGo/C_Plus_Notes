#include <iostream>
#include <vector>
using namespace std;

int main(void){
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	
	// 简单的迭代方式
	for (int it: v){
		cout << it << endl;
	}
	return 0;
}
