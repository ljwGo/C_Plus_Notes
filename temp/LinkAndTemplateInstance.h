#include <vector>
#include <iostream>
using namespace std;

// Container类声明
template <class PELE>
class Container {
public:
	~Container();
	void removeEleById(unsigned int id); // 根据元素id删除元素(元素必须含有id属性) 
	void push(PELE pNewEle);
	bool pop();
	PELE getEleById(unsigned int id);
	void display();
protected:
	vector<PELE> elements;
};

// BookShelf类声明
template <class PELE>
class BookShelf : public Container<PELE> {
public:
	void removeEleByTitle(string title);
	PELE getEleByTitle(string title);
	bool isEleExist(PELE pele);
};

// Book类的声明
class Book {
public:
	Book();
	Book(string title, string author, string publishing, double price, unsigned int amount);
	void display() const; 
	void setPrice(double price);
	void setPublishing(string publishing);
	void setTitle(string title);
	void setAmount(unsigned int amount);
	void setAuthor(string author);
	void init(string title, string author, string publishing, double price, unsigned int amount);
	string getTitle() const;
	string getPublishing() const;
	string getAuthor() const;
	double getPrice() const;
	unsigned int getId() const;
	unsigned int getAmount() const;
	bool hasInit();
	friend std::ostream& operator<< (std::ostream& out, Book& book);
private:
	static unsigned int staticBookId;
	unsigned int id;
	unsigned int amount; // 数量
	double price; // 价格
	string publishing; // 出版社
	string title; // 书名
	string author; // 作者
	bool _isInit;
};
