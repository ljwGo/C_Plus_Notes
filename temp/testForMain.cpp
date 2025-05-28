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
	/*这样测试真的很烦*/

	BookShelf<Book*> bookShelf;
	AdminGroup<Admin*> adminGroup;
	CustomerGroup<Buyer*> customerGroup;
	Admin admin01("赖建威", "ljw123", "123456", adminGroup), admin02("张三", "2333", "2333", adminGroup);
	Book* pBook01 = new Book("时光代理人", "未知", "b站", 150, 2);
	Book* pBook02 = new Book("罗小黑", "未知", "北京", 200, 2);
	Buyer buyer01("李四", "123456", "123456", "北京", 200, 0, customerGroup), buyer02("王五", "2333", "2333", "上海", 300, 0, customerGroup);

	cout << "测试管理员展示" << endl;
	admin01.display();
	cout << admin02 << endl;

	cout << "测试添加书籍(通过管理员或者直接添加): " << endl;
	bookShelf.push(pBook01);
	bookShelf.push(pBook02);
	//admin01.addBook(bookShelf);
	cout << "删除编号为2的书: " << endl;
	bookShelf.display();
	admin02.removeBook(bookShelf, 2);
	bookShelf.display();

	cout << "测试书数量不够, 或者不存在(编号为2的书)" << endl;
	buyer01.buyBookById(2, 2, bookShelf);
	buyer02.buyBookByTitle("时光代理人", 3, bookShelf);
	buyer02.display();

	cout << "测试未交订单不会真正改变书籍数量" << endl;
	bookShelf.display();
	buyer01.buyBookByTitle("时光代理人", 1, bookShelf);
	bookShelf.display();

	cout << "测试提交订单会改变书籍数量" << endl;
	buyer01.showOrder();
	buyer01.pay(bookShelf);
	//buyer01.showMoney();
	//bookShelf.display();

	cout << "测试余额不足, 不能够付款" << endl;
	buyer01.buyBookById(1, 1, bookShelf);
	buyer01.pay(bookShelf);
	buyer01.showMoney();

	//cout << "测试重置订单" << endl;
	//buyer01.resetOrder();
	//buyer01.showOrder();
	return 0;
}