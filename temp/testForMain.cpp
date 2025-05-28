#include "container.h"
#include "bookShelf.h"
#include "adminGroup.h"
#include "customerGroup.h"
//#include "orderGroup.h"
#include "admin.h"
#include "book.h"
#include "order.h"
#include "buyer.h"
#include <iostream>

using namespace std;

AdminGroup<Admin*> adminGroup;
CustomerGroup<Buyer*> customerGroup;

int main() {
	/*����������ĺܷ�*/

	BookShelf<Book*> bookShelf;
	AdminGroup<Admin*> adminGroup;
	CustomerGroup<Buyer*> customerGroup;
	Admin admin01("������", "ljw123", "123456", adminGroup), admin02("����", "2333", "2333", adminGroup);
	Book* pBook01 = new Book("ʱ�������", "δ֪", "bվ", 150, 2);
	Book* pBook02 = new Book("��С��", "δ֪", "����", 200, 2);
	Buyer buyer01("����", "123456", "123456", "����", 200, 0, customerGroup), buyer02("����", "2333", "2333", "�Ϻ�", 300, 0, customerGroup);

	cout << "���Թ���Աչʾ" << endl;
	admin01.display();
	cout << admin02 << endl;

	cout << "��������鼮(ͨ������Ա����ֱ�����): " << endl;
	bookShelf.push(pBook01);
	bookShelf.push(pBook02);
	//admin01.addBook(bookShelf);
	cout << "ɾ�����Ϊ2����: " << endl;
	bookShelf.display();
	admin02.removeBook(bookShelf, 2);
	bookShelf.display();

	cout << "��������������, ���߲�����(���Ϊ2����)" << endl;
	buyer01.buyBookById(2, 2, bookShelf);
	buyer02.buyBookByTitle("ʱ�������", 3, bookShelf);
	buyer02.display();

	cout << "����δ���������������ı��鼮����" << endl;
	bookShelf.display();
	buyer01.buyBookByTitle("ʱ�������", 1, bookShelf);
	bookShelf.display();

	cout << "�����ύ������ı��鼮����" << endl;
	buyer01.showOrder();
	buyer01.pay(bookShelf);
	//buyer01.showMoney();
	//bookShelf.display();

	cout << "��������, ���ܹ�����" << endl;
	buyer01.buyBookById(1, 1, bookShelf);
	buyer01.pay(bookShelf);
	buyer01.showMoney();

	//cout << "�������ö���" << endl;
	//buyer01.resetOrder();
	//buyer01.showOrder();
	return 0;
}