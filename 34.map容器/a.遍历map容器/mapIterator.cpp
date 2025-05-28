#include <iostream>
#include <map>
using namespace std;

int main(void){
	map<int, int> m;
	m.insert(pair<int, int>(1, 2));
	m.insert(pair<int, int>(3, 4));
	m.insert(pair<int, int>(5, 6));
	for (map<int, int>::iterator it=m.begin(); it!=m.end(); it++){
		cout << it->first << endl;
	}
	return 0;
}
