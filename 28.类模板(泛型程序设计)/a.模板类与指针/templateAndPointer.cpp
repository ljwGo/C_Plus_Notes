#include <iostream>
using namespace std;

//class Template{
//	public:
//		T* pt;
//		T t;
//};

// T是类型, T*是代指T类型的指针

template <typename T>
class Template01{
	public:
		T* pt;
		T t;
};

int main(void){
	int n = 10;
	Template01<int> t01;
	
	t01.pt = &n;
	t01.t = n;
	
	cout << *(t01.pt) << endl;
	cout << t01.t << endl;
	return 0;
}
