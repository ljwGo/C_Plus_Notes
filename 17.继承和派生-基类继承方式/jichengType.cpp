#include <iostream>
using namespace std;

// c++ ��ļ̳������ַ�ʽ
// ��ʽһ: public Ҳ����õķ�ʽ
// 		���ַ�ʽ���ص���, �ӻ���̳�������public��protected��Ա
//		�����ֲ���, �����private��Ա���ɲ��ܱ�����
// ��ʽ��: private
//  	�ӻ���̳�������public��protected��Ա�����Ϊprivate
//		�������ܹ�ͨ�����ⷽʽ����
// 		private��Ա�����޷�����
//      ���, �����ļ̳�, ������ʲô��ʽ, ���м̳������ĳ�Ա����private����
// ��ʽ��: protected
// 		�ӻ���̳�������public��protected��Ա�����Ϊprotected
// 		private��Ա�����޷�����
//      ���, �����ļ̳�, ������ʲô��ʽ, ���м̳������ĳ�Ա����protected����

class A{
	public:
		A(char a){
			this->pro_a = a;
			this->pri_a = a;
		};
		void showAPosition(){
			cout << "in A" << endl;
		}
	protected:
		char pro_a;
	private:
		char pri_a;
};

class B: public A{
	public:
		B(char b, char a): A(a){
			this->pro_b = b;
			this->pri_b = b;
		};
		void showBPosition(){
			cout << "in B" << endl;
		}
	protected:
		char pro_b;
	private:
		char pri_b;
};

class C: private B{
	// ˽�м̳�, ����C���ܹ�ͨ��ָ����ʽ����B
//	class D; ǰ������������϶����ڵ����û���ָ��
	public:
		C(char c, char b, char a): B(b, a){
			this->pri_c = c;
			this->pro_c = c; 
		};
		void showCPosition(){
			cout << "in C" << endl;
		};
		void showBinC(){
			// �����: ֻ������ָ���ķ�ʽ, 
			// ���Խ���Ƕ�����, ֻ��, �����̳�C�Ľ��޷�����A��B
			showBPosition();
//			B::showBPosition();
		}
	private:
		char pri_c;
	protected:
		char pro_c;
	
};

class D: public C{
	// ���뷽��Ͳ���ͨ����, �Ͼ�C�̳�B�ķ�ʽ��private, D�޷�����A��B�еĳ�Ա
	public:
		D(char d, char c, char b, char a): C(c, b, a){
			this->pro_d = d;
			this->pri_d = d;
		}
		void showABCD(){
//			cout << pro_a << pro_b << pro_c << pro_d << endl;
		}
	private:
		char pri_d;
	protected:
		char pro_d;
};

int main(void){
	C c1('c', 'b', 'a');
	D d1('d', 'c', 'b', 'a');
	c1.showCPosition();
	c1.showBinC();
	d1.showABCD();
	// ��Ȼ�޷�����C�̳е�B��A,����C����ĳ�Ա�����ܹ����ʵ�
	d1.showCPosition();
	return 0;
}
