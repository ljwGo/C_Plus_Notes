#include <iostream>
#include <map>
using namespace std;

class Book {
public:
	Book();
	Book(unsigned int amount, double price, string publishing, string title);
	void display(); // 展示书的信息
	void setPrice(double price);
	void setPublishing(string publishing);
	void setTitle(string title);
	void setAmount(unsigned int amount);
	bool operator< (const Book& book) const;
	friend std::ostream& operator<< (std::ostream& out, Book book);
private:
	static unsigned int staticBookId;
	unsigned int id;
	unsigned int amount; // 数量
	double price; // 价格
	string publishing; // 出版社
	string title; // 书名
};

unsigned int Book::staticBookId = 1;

Book::Book() {
	amount = 0;
	price = 0;
	publishing = "";
	title = "";
	id = Book::staticBookId++;
}

Book::Book(unsigned int amount, double price, string publishing, string title) {
	this->amount = amount;
	this->price = price;
	this->publishing = publishing;
	this->title = title;
	id = Book::staticBookId++;
}

void Book::display() {
	cout << "====== 图书信息为 ======" << endl;
	cout << "编号为: " << id << endl;
	cout << "书名为: " << title << endl;
	cout << "价格为: " << price << endl;
	cout << "出版社为: " << publishing << endl;
	cout << "数量为: " << amount << endl;
}

void Book::setAmount(unsigned int amount) {
	this->amount = amount;
}

void Book::setPrice(double price) {
	this->price = price;
}

void Book::setPublishing(string publishing) {
	this->publishing = publishing;
}

void Book::setTitle(string title) {
	this->title = title;
}

bool Book::operator<(const Book& book) const{
	return this->id < book.id;
}

// 重载<<
std::ostream& operator<< (std::ostream& out, Book book) {
	out << "====== 图书信息为 ======" << endl;
	out << "编号为: " << book.id << endl;
	out << "书名为: " << book.title << endl;
	out << "价格为: " << book.price << endl;
	out << "出版社为: " << book.publishing << endl;
	out << "数量为: " << book.amount << endl;
	return out;
}

int main(void){
	Book book01, book02;
	map<Book, int> bookContainer;
	bookContainer.insert(pair<Book, int>(book01, 2));
	bookContainer.insert(pair<Book, int>(book02, 3));
//	bookContainer.insert(pair<Book, int>(book01, 4));
	
	// 只重载了 < 就行了? 它是怎么知道key节点是相同的呢? map本质是二叉树
	cout << bookContainer[book01] << endl;
//	cout << (book01 == book01) << endl;
	return 0;
}