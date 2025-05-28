#include <iostream>

// constructor 构造函数
class Student{
	public:
		const char * name;
		unsigned int sign;
		// 构造函数, 无返回值
		Student(){
			name = 0;
			sign = 0;
			age = 0;
		}
		Student(char *t_name, int t_sign, int t_age){
			// 不需要this或者self
			name = t_name;
			sign = t_sign;
			age = t_age;
		};
		// 特殊的, 使用引用的方式的构造函数
		// 特点一: 形参实参可以不一一对应
		// 特点二: 会与无参构造函数冲突, 所以一般有这个构造函数, 就不要书写无参构造函数
//		Student(int &t_sign, int &t_age){
//			name = "lisi";
//			sign = t_sign;
//			age = t_age;
//		}
		void showInformation(){
			std::cout << "name: " << name << "; sign: " << sign << "; age: " << age << std::endl;
		}
	private:
		unsigned int age;
};

// 需要注意的是, 绝大部分编译器
// 在类没有构造函数时, 会默认生成一个无参构造函数(这个函数什么也不做)
// 当我们手动书写了有参构造函数时, 缺省无参构造函数将不再自动创建
// 为了防止报错(实例化时, 不传入参数), 最好手动创建一个无参构造函数

int main(void){
	Student lisi = Student("lisi", 1003, 10);
//	使用引用方式的传入, 特点是必须传入变量
//	int a=1;
//	int b=2;
//	Student lisi = Student(a, b);
	lisi.showInformation();
	return 0;
}
