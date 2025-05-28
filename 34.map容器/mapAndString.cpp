#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(void){
	map<string, int> m;
	m.insert(pair<string, int>("时光代理人", 2));
	m.insert(pair<string, int>("罗小黑", 3));
	m.insert(pair<string, int>("刺客伍六七", 4));
	m.insert(pair<string, int>("灵能百分百", 5));
	
	map<string, int>::iterator it = m.find("罗小黑");
	if (it != m.end()){
		cout << "找到了! 值为" << it->second << endl;
	}else{
		cout << "没找到55" << endl;
	}
	
	return 0;
}
