#include <iostream>
#include <string>
using namespace std;

int main(void){
	
	int choice;
	char word01;
	char word02;
	string str;
	char cArray[20] = {NULL};
	
	// 这里输入不是整形的数据, 比如输入 cin字符串
	cin.getline(cArray, 5);
	cin.get(word02);

	cout << "cArray: " << cArray << endl;
	cout << "word02: " << word02 << endl;

//	cout << "choice: " << choice << endl;
//	cout << "str: " << str << endl;
	
	return 0;
}
