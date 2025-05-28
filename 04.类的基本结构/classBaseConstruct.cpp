#include <iostream>

// 类的定义方式一
//   成员属性和方法在声明时, 同时定义
class Person {
	public:
		double height = 180.0;
//		char[16] gander; 数组是不可以的, 不知道有没有解决方案
//		char * gander = "f"; 有警告不好, 最好将指针改为常量
		const char * const gander = "female";
		void sayHello(){
			std::cout << "hello c++ class" << std::endl;
		};
	private:
		unsigned int age = 18;
	protected:
		// 继承链上允许访问的成员
		unsigned int _num = 10;
};

// 类的定义方式二:
//   声明和定义分开
class Student{
	public:
		const char * name;
		unsigned int sign;
		void doHomework(int n);
	private:
		unsigned int age;
};

// 方法在类外进行定义
void Student::doHomework(int n){
	std::cout << "还有" << n << "的作业要完成, 好烦!!!";
}


int main(void){

	// 实例化方式一:
	//   调用类的构造函数
	Person zhangsan = Person();
	zhangsan.sayHello();
	std::cout << zhangsan.height << std::endl;
	
	Student lisi = Student();
	lisi.doHomework(1);
	return 0;
}
