#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(void){
	map<string, int> m;
	m.insert(pair<string, int>("ʱ�������", 2));
	m.insert(pair<string, int>("��С��", 3));
	m.insert(pair<string, int>("�̿�������", 4));
	m.insert(pair<string, int>("���ܰٷְ�", 5));
	
	map<string, int>::iterator it = m.find("��С��");
	if (it != m.end()){
		cout << "�ҵ���! ֵΪ" << it->second << endl;
	}else{
		cout << "û�ҵ�55" << endl;
	}
	
	return 0;
}
