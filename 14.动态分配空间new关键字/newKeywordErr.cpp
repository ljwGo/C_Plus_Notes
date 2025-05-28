#include <iostream>
using namespace std;

enum Gander{
	Female,
	Male,
};

class Student{
	public:
		Student();
		Student(unsigned int ID, Gander gander, char *name);
		static Student * createStudent();
		void showInfo();
	private:
		unsigned int studentID;
		Gander gander;
		char name[16];
};
Student::Student(unsigned int ID, Gander gander, char *name):name("xxx"), gander(Female), studentID(0){
};
void Student::showInfo(){
	cout << "name: " << name << "; gander: " << gander << "; id: " << studentID << endl;
}
Student *Student::createStudent(){
	cout << "please input name, gander and id: " << endl;
	char * name;
	int sex;
	Gander gander;
	unsigned id;
	
	
	cin >> sex >> id;
	
	switch (sex){
		case 0: gander = Female;break;
		case 1: gander = Male;break;
		default: gander = Male;
	}
//	return new Student(id, gander, name);
	return new Student(id, gander, "lisi");

};
int main(void){
	Student *oneStu = Student::createStudent();
	oneStu->showInfo();
	return 0;
}
