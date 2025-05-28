#include "LinkAndTemplateInstance.h"

// Container类实现
template <class PELE>
Container<PELE>::~Container() {
	for (PELE iele : elements) {
		delete iele;
	}
}
template <class PELE>
void Container<PELE>::push(PELE pNewEle) {
	elements.push_back(pNewEle);
}
template <class PELE>
bool Container<PELE>::pop() {
	if (!elements.empty()) {
		delete elements[elements.size() - 1];
		elements.pop_back();
		return true;
	}
	else {
		return false;
	}
}
template <class PELE>
void Container<PELE>::removeEleById(unsigned int id) {
	for (PELE iele : this->elements) {
		if (iele->getId() == id) {
			delete iele;
			this->elements.erase(iele);
		}
	}
}
template <class PELE>
PELE Container<PELE>::getEleById(unsigned int id) {
	for (PELE iele : this->elements) {
		if (iele->getId() == id) {
			return iele;
		}
	}
	return NULL;
}
template <class PELE>
void Container<PELE>::display() {
	for (PELE iele : this->elements) {
		cout << *iele << endl;
	}
}

// BookShelf类实现
template <class PELE>
void BookShelf<PELE>::removeEleByTitle(string title) {
	for (PELE iele : this->elements) {
		if (iele->getTitle() == title) {
			delete iele;
			this->elements.erase(iele);
		}
	}
}
template <class PELE>
PELE BookShelf<PELE>::getEleByTitle(string title) {
	for (PELE iele : this->elements) {
		if (iele->getTitle() == title) {
			return iele;
		}
	}
	return NULL;
}
template <class PELE>
bool BookShelf<PELE>::isEleExist(PELE ele) {
	for (PELE pele : this->elements) {
		if (pele == ele) {
			return true;
		}
	}
	return false;
}

// Book类的实现
unsigned int Book::staticBookId = 1;
Book::Book() {
	amount = 0;
	price = 0;
	publishing = "";
	title = "";
	author = "";
	id = Book::staticBookId++;
	_isInit = false;
}
Book::Book(string title, string author, string publishing, double price, unsigned int amount) {
	this->amount = amount;
	this->price = price;
	this->publishing = publishing;
	this->title = title;
	this->author = author;
	id = Book::staticBookId++;
	_isInit = true;
}
void Book::display() const  {
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
void Book::setAuthor(string author) {
	this->author = author;
}
void Book::init(string title, string author, string publishing, double price, unsigned int amount) {
	this->title = title;
	this->price = price;
	this->publishing = publishing;
	this->amount = amount;
	this->author = author;
	_isInit = true;
}
string Book::getTitle() const {
	return title;
}
string Book::getPublishing() const {
	return publishing;
}
string Book::getAuthor() const {
	return author;
};
double Book::getPrice() const {
	return price;
}
unsigned int Book::getId() const{
	return id;
}
unsigned int Book::getAmount() const {
	return amount;
}
bool Book::hasInit() {
	return _isInit;
}

// 重载<<
std::ostream& operator<< (std::ostream& out, Book& book) {
	out << "====== 图书 " << book.id << " ======" << endl;
	out << "书名为: " << book.title << endl;
	out << "价格为: " << book.price << endl;
	out << "出版社为: " << book.publishing << endl;
	out << "数量为: " << book.amount << endl;
	return out;
}

// 失败
BookShelf<Book *> _BookShelfInstance_;