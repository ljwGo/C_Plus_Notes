#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* 
	(1)发现一个问题, 派生类想要访问基类的protected成员时, 要带上this->
	(2)该容器类, 模板实参必须是指针类型.
	(3)指针指向的对象必须是动态创建的, 支持delete方法
*/

template <typename PELE>
class Container {
public:
	void push(PELE pNewEle); // 添加末尾元素
	//PELE pop(); // 移除末尾元素, 返回被删除元素值的该方法先不做
	bool pop();
	bool removeEleById(unsigned int id); // 根据元素id删除元素(元素必须含有id属性) 
	PELE getEleById(unsigned int id); // 返回指定id值的元素引用
	void display(); // 显示函数
protected:
	vector<PELE> elements;
};

/* 后面优化时尽量使用异常处理, 而非靠返回bool值来判断是否成功! */

template <typename PELE>
void Container<PELE>::push(PELE pNewEle) {
	elements.push_back(pNewEle);
}

template <typename PELE>
//PELE Container<PELE>::pop(){
bool Container<PELE>::pop() {
	if (!elements.empty()) {
		// 由于是动态创建的元素, 删除前必须先delete
		delete elements[elements.size() - 1];
		elements.pop_back();
		return true;
	}
	else {
		return false;
	}
}

template <typename PELE>
bool Container<PELE>::removeEleById(unsigned int id) {
	int flag = 0;
	typename vector<PELE>::iterator targetIt;
	// 迭代
	for (typename vector<PELE>::iterator it = elements.begin(); it != elements.end(); it++) {
		if ((*it)->getId() == id) {
			flag = 1;
			targetIt = it;
			break;
		}
	}

	if (flag) {
		// 找到了
		delete *targetIt;
		elements.erase(targetIt);
		return true;
	}
	else {
		return false;
	}
}

template <typename PELE>
PELE Container<PELE>::getEleById(unsigned int id){
	int flag = 0;
	typename vector<PELE>::iterator targetIt;
	// 迭代
	for (typename vector<PELE>::iterator it = elements.begin(); it != elements.end(); it++) {
		if ((*it)->getId() == id) {
			flag = 1;
			targetIt = it;
			break;
		}
	}

	if (flag) {
		// 返回元素的引用
		return *targetIt;
	}
	else {
		return NULL;
	}
}

template <typename PELE>
void Container<PELE>::display() {
	for (typename vector<PELE>::iterator it = elements.begin(); it != elements.end(); it++) {
		// PELE必须重载过 << 插入和输出流的函数
		// (先不写)或使用display
		cout << **it << endl;
	}
}

template <typename PELE>
class BookShelf: public Container<PELE> {
public:
	bool removeEleByTitle(string title); // 根据名称删除元素(元素必须含有title的string类型属性)
	PELE getEleByTitle(string title); // 返回指定名称的元素引用
};

template <typename PELE>
bool BookShelf<PELE>::removeEleByTitle(string title) {
	int flag = 0;
	typename vector<PELE>::iterator targetIt;
	// 迭代
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getTitle().compare(title) == 0) {
			flag = 1;
			targetIt = it;
			break;
		}
	}

	if (flag) {
		// 找到了
		delete* targetIt;
		this->elements.erase(targetIt);
		return true;
	}
	else {
		return false;
	}
}

template <typename PELE>
PELE BookShelf<PELE>::getEleByTitle(string title) {
	int flag = 0;
	typename vector<PELE>::iterator targetIt;
	// 迭代
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getTitle().compare(title) == 0) {
			flag = 1;
			targetIt = it;
			break;
		}
	}

	if (flag) {
		// 返回元素的引用
		return *targetIt;
	}
	else {
		return NULL;
	}
}

class Book {
public:
	Book();
	Book(unsigned int amount, double price, string publishing, string title);
	void display(); // 展示书的信息
	void setPrice(double price);
	void setPublishing(string publishing);
	void setTitle(string title);
	void setAmount(unsigned int amount);
	string getTitle() const;
	string getPublishing() const;
	double getPrice() const;
	unsigned int getId() const;
	unsigned int getAmount() const;
	bool operator< (const Book& book) const;
	friend std::ostream& operator<< (std::ostream& out, Book& book);
private:
	static unsigned int staticBookId;
	unsigned int id;
	unsigned int amount; // 数量
	double price; // 价格
	string publishing; // 出版社
	string title; // 书名
};

// 重载<<
std::ostream& operator<< (std::ostream& out, Book& book) {
	out << "====== 图书 " << book.id << " ======" << endl;
	out << "书名为: " << book.title << endl;
	out << "价格为: " << book.price << endl;
	out << "出版社为: " << book.publishing << endl;
	out << "数量为: " << book.amount << endl;
	return out;
}

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
	cout << "====== 图书 " << id << " ======" << endl;
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

bool Book::operator< (const Book& book) const {
	return this->id < book.id;
}

string Book::getTitle() const {
	return title;
}

string Book::getPublishing() const {
	return publishing;
}

double Book::getPrice() const {
	return price;
}

unsigned int Book::getId() const{
	return id;
}

unsigned int Book::getAmount() const {
	return amount;
}

int main(void){
	Book* book01 = new Book(10, 20.2, "B站", "时光代理人");
	Book* book02 = new Book(2, 32.4, "ljw", "罗小黑");
	Book* book03 = new Book();
	BookShelf<Book *> bookShelf;
	bookShelf.push(book01);
	bookShelf.push(book02);
	bookShelf.push(book03);
//	bookShelf.display();
//	bookShelf.pop();
//	bookShelf.display();
	
	Book* book04 = bookShelf.getEleById(2);
	Book* book05 = bookShelf.getEleByTitle("罗小黑");
	cout << book04 << endl;
	cout << book05 << endl;
	if (bookShelf.removeEleByTitle("罗小黑")){
		cout << "删除成功" << endl;
	}
	bookShelf.display();
}
