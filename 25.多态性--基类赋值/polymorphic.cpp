#include <iostream>
using namespace std;

// ��ͨ������
class Transport{
	public:
		void run(){
			cout << "��ͨ����������!!" << endl;
		}
};

// ������
class Vehical:public Transport{
	public:
		void run(){
			cout << "����������!!" << endl;
		}
};

// ������
class Car:public Vehical{
	public:
		void run(){
			cout << "����������!!" << endl;
		}
};

// ������
class Truck:public Vehical{
	public:
		void run(){
			cout << "����������!!" << endl;
		};
};

int main(void){
	// ���ɽ�ͨ����ָ��
	Transport *p;
	Transport t1;
	Vehical v1;
	Car c1;
	Truck tk1;
	// �ܺ����, �����ͻ���Ҳ�ǳ���, ����Ҳ�ǽ�ͨ���ߵ�һ��
	// ���Խ�ͨ���ߵ�ָ���ܹ�ָ������**�������������**
	p = &t1;
	p->run();
	p = &v1;
	p->run();
	p = &c1;
	p->run();
	p = &tk1;
	p->run();
	// ����, ��������������Ĳ�һ��
	// �������**��ͨ����������!!**
	
	/*
		����ʵ��˵��ԭ��, ����ΪC++�Ǳ������Ե�ԭ��
		�����뵽p->run()���ʱ, ���������Ӧ������
		��ʱֻ֪��p����������, ���Ա������Ͱ�pָ��Ķ�
		��ΪTransport��Դ�
		��ס, �����������޷�Ԥ֪����ִ�е�״̬��
	*/
	return 0;
}
