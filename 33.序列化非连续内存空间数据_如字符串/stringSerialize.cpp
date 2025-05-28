#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
	***无解, 哈哈***
一: string类型在内存中存贮是不连续的, 其中含有指针
	如果使用write直接读入string类, 不包含真正的字符数据
二: 可以使用.data()方法获取真正字符数据的地址
	.size()可以获取字符的字节大小
三: 不能够直接将字符数据直接读入到string对象中
	现在有一个笨方法, 就是将保存在文件中的字符
	读入到字符数组中, 然后使用=号, 赋值给string对象
	***会发生访问冲突, 有空在去深入理解好了***
*/

void SerializeString(std::ostream& os, string str) {
	os.write((const char*)str.data(), str.size());
}

/* 在内存中是连续的, 或逻辑上是连续的(内存对齐) */
struct StudentStruct {
	char gander;
	int score;
	double height;
} lisi = {
	'f',
	90,
	180.3,
};
class SimpleStudent {
public:
	char gander;
	int score;
	double height;
	char name[16] = "张三";
	// sizeof不包含成员, 其中的语句是指令集合, 应该被作为子程序在其它位置
	SimpleStudent() {
		gander = 'm';
		score = 100;
		height = 180.2;
	}
};
class ComplexStudent {
public:
	char gander;
	int score;
	double height;
	string name; // string 32字节大小(8字节指针, 字符串大小8字节? 其它16字节?)
	ComplexStudent() {
		gander = 'm';
		score = 100;
		height = 180.2;
		name = "张三!!!!!!!!!!";
	};
	ComplexStudent(char g, int s, double h, string n) {
		gander = g;
		score = s;
		height = h;
		name = n;
	}
};

int main(void) {
	//	// 测试内存对齐
	//	cout << "struct size = " << sizeof(lisi) << endl;
	//	
	//	SimpleStudent ss01;
	//	cout << "simple class size = " << sizeof(ss01) << endl;
	//	
	//	ComplexStudent cs01;
	//	cout << "simple class size = " << sizeof(cs01) << endl;
	//	
		//string name = "张三!";
	//	// 字符串是连续的, 并不是unicode那样, 均是4字节
	//	cout << "data(): " << name.data() << endl;
	//	cout << "size(): " << name.size() << endl;
	//	cout << "sizeof: " << sizeof(name) << endl;
	//	
	//	cout << "======华丽的分割线======" << endl;
	//	
	//	// 将字符串二进制直接写入文件
		//ofstream ofile("ContainStringClassSerial", ios_base::out | ios_base::trunc);
	////	ofile.write((const char *)&name, sizeof(name));
		//SerializeString(ofile, name); // 调用序列化函数存贮字符串
		//ofile.close();
	//	
	//	// 将文件中内容读入到字符串中
		//string copyName;
		//char arrayName[32], arrayName02[32];
		//ifstream ifile("ContainStringClassSerial", ios_base::in);
	//	// 会报错
	////	ifile.read(reinterpret_cast<char *>(&copyName),sizeof(name));
	////	ifile.read((char *)(&copyName),sizeof(name));
		//ifile.read((char *)arrayName, name.size());
		//arrayName[name.size()] = '\0';
	//	// seekg可以直接设置位置
	//	ifile.seekg(0);
	//	ifile.read((char *)arrayName02, name.size());
	//	ifile.close();
	//	
	//	cout << "copyName: " << copyName << endl;
	//	cout << "arrayName: " << arrayName << endl; // 成功的, 不过就将string变为字符数组了
	//	cout << "arrayName02: " << arrayName02 << endl; 
	//	
		//copyName = arrayName;
		//cout << "after = copyName: " << copyName << endl;

	// 现在测试将含有string类的对象从文件中复原
	ComplexStudent cs1('f', 99, 172.2, "lisi"), cs2;
	ofstream ofile("ContainStringClassSerial", ios_base::out | ios_base::trunc);
	ofile.write((char*)&cs1, sizeof(cs1));
	// 保存真正的字符数据
	ofile.write((char*)cs1.name.data(), cs1.name.size());
	ofile.close();

	// 创建临时的字符数组, 用于还原复杂类中组合的string对象
	char tempStr[1024];
	ifstream ifile("ContainStringClassSerial", ios_base::in);
	ifile.read((char*)&cs2, sizeof(cs2));
	cout << cs2.name.size() << endl;
	ifile.read(tempStr, cs2.name.size());
	tempStr[cs2.name.size()] = '\0';
	cs2.name = tempStr;
		
	cout << "cs2.name: " << cs2.name << endl; 
	ifile.close();
	return 0;
}
