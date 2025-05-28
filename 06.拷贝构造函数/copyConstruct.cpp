#include <iostream>

// 有时, 我们想通过传入一个类型的对象, 来方便的复制对象
// 这时, 就用到了复制函数
class Student{
	public:
		const char * name;
		unsigned int sign;
		Student(){
			name = 0;
			sign = 0;
			age = 0;
		}
		Student(char *t_name, int t_sign, int t_age){
			name = t_name;
			sign = t_sign;
			age = t_age;
		};
		// 拷贝函数, 必须有const修饰; 必须是引用方式
		Student(const Student &stu){
			name = stu.name;
			sign = stu.sign;
			age= stu.age;
		}
		void showInformation(){
			std::cout << "name: " << name << "; sign: " << sign << "; age: " << age << std::endl;
		}
	private:
		unsigned int age;
};

// 复制构造函数是存在缺省的, 这个缺省的拷贝构造函数
// 作用仅仅是将属性变量一一复制而已, 当然可以书写更复杂的方法
// 来满足更复杂的场景需要
int main(void){
	Student lisi = Student("lisi", 1004, 34);
	Student zhangshan = Student(lisi);
	zhangshan.showInformation();
	return 0;
}
