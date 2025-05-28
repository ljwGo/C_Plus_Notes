#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* 
二进制写文件
open(filename): 打开文件
wirte(memory address, byte size): 将内存的块写入文件
seekp(int): 移动写指针
tellp(): 返回当前写指针位置
close(): 关闭文件资源 
*/

/*
二进制读文件
除wirte外, 其余基本相同
read(memory address): 将文件内容读取到指定内存块中
*/
// 简单的类和结构体是支持序列化的, 而复杂的类,多继承,虚继承等是不支持直接序列化的
// c++库中有可以将复杂类序列化的类

enum GANDER{
	MALE = 0,
	FEMALE = 1,
};

class StudentClass{
	public:
		string name;
		StudentClass(const char * str): name(str){};
		StudentClass(){};
};

struct Student{
	char name[32];
	int score;
	GANDER gander;
};

int main(void){
	/* 写入普通数据 */
	int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	ofstream outputFile;
	
	// reinterpret_cast<>()是专门用于指针类型转换的模板函数
	// write和read的第一个参数必须是char *类型
	outputFile.open("io_binary_file", ios_base::out | ios_base::binary);
	outputFile.write(reinterpret_cast<char *>(values), sizeof(values));
	outputFile.close();
	
	ifstream inputFile;
	inputFile.open("io_binary_file", ios_base::in | ios_base::binary);
	// 读取第四个数据, 移动指针
	inputFile.seekg(3 * sizeof(int));
	
	int n;
	inputFile.read(reinterpret_cast<char *>(&n), sizeof(int));
	cout << "n = " << n << endl;
	inputFile.close();
	
	/* 写入结构体 */
	// 真正的文件中, 一定不要将所有数据混合到同一个文件中
	Student stu01 = {
		"ljw",
		100,
		MALE,
	};
	// 一般模式是w, 也就是说会覆盖原本的数据
	outputFile.open("io_binary_file", ios_base::out | ios_base::binary);
	outputFile.write(reinterpret_cast<char *>(&stu01), sizeof(stu01));
	cout << sizeof(stu01) << endl;
	outputFile.close();
	
	// 结构体中的字符串利用的是字符数组, 该字符串长度是可预见的, 如果换成string类会怎么样呢?
	inputFile.open("io_binary_file", ios_base::in | ios_base::binary);
	inputFile.seekg(9 * sizeof(int));
	inputFile.read(reinterpret_cast<char *>(&n), sizeof(int));
	cout << "n = " << n << endl;
	inputFile.close();
	
	/* 写入组合类 */
	StudentClass stuc01("ljw"), stuc02("张三"), stuc03("很长很长很长的名字哇!!!!!!");
	// 很神奇, sizeof对含有string成员的类的大小是固定的(但很明显, name成员的长度是可变的)
	cout << "stuc01 size = " << sizeof(stuc01) << endl;
	cout << "stuc02 size = " << sizeof(stuc02) << endl;
	cout << "stuc03 size = " << sizeof(stuc03) << endl;
	
	cout << "stuc01 sizeof = " << stuc01.name.size() << endl;
	cout << "stuc02 sizeof = " << stuc02.name.size() << endl;
	cout << "stuc03 sizeof = " << stuc03.name.size() << endl;
	
	outputFile.open("io_binary_file", ios_base::out | ios_base::binary);
	outputFile.write(reinterpret_cast<char *>(&stuc01), sizeof(stuc01));
	outputFile.write(reinterpret_cast<char *>(&stuc02), sizeof(stuc02));
	outputFile.write(reinterpret_cast<char *>(&stuc03), sizeof(stuc03));
	outputFile.close();
	
	// 发生错误了
	StudentClass stuc04;
	inputFile.open("io_binary_file", ios_base::in | ios_base::binary);
	inputFile.read(reinterpret_cast<char *>(&stuc04), sizeof(stuc01));
	cout << stuc04.name << endl;
	inputFile.close();
;	return 0;
}
