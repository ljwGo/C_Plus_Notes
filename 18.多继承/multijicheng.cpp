#include <iostream>
using namespace std;

class A{
	public:
		A(char a){
			this->a = a; 
		};
	protected:
		char a;
};

class B: public A{
	public:
		B(char b, char a): A(a){
			this->b = b;
		};
	protected:
		char b;
};

//class C: public A{
class C{
	public:
		C(char c){
			this->c = c; 
		};
	private:
		char c;
};

// ¶à¼Ì³Ğ
class D: public B, public C{
	public:
		D(char d, char c, char b, char a): B(b, a), C(c){
			this->d = d;
		}
		char d;
};

int main(void){
	return 0;
}
