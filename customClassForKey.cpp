#include <iostream>
#include <map>
using namespace std;

class Test{
	public:
		char a;
};

int main(void){
	Test _01, _02;
	map<Test, int> m;
	m.insert(pair<Test, int>(_01, 1));
	m.insert(pair<Test, int>(_02, 2));
	return 0;
}
