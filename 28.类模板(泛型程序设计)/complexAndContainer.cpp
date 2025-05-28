#include <iostream>
#include <assert.h>
#include <iomanip>
#define DEFAULT_CONTAINER_SIZE 10
using namespace std;

// 构造一个容器类, 它能够更方便的管理空间, 以及容纳所有指定类型
// 	实现目标1, 容器可扩展长度
//  实现目标2, 容器可直接赋值

/*
	泛型有一个最大的问题, 就是他将 
	**类名<占位符>** 
	视为一个完整的类型
	单纯的类名是不能够使用的
	因此, 下面的所有Container必须使用
	Container<T> 代替
*/

// 还有, 似乎不能够使用带有默认值的构造函数作为
// 无参构造函数

template <class T> class Container{
	public:
		Container(); // 无参构造函数
		Container(int length); // 有参构造函数
		Container(Container &c); // 拷贝构造
		~Container(); // 析构函数
		// 扩展数组长度
		bool extendSpace(int len);
		// 重载下标运算符
		T & operator[](int index);
		// 重载等号
		Container<T> operator= (Container<T> &c);
		// 重载指针类型(重点)
		operator T * (); 
	private:
		T *list;
		unsigned length;
};

template <class T> Container<T>::Container(){
	this->length = DEFAULT_CONTAINER_SIZE;
	this->list = new T[length];
}
template <class T> Container<T>::Container(int length){
	this->length = length;
	this->list = new T[length];
}
template <class T> Container<T>::Container(Container &c){
	this->length = c.length;
	this->list = new T[length];
	// 赋值值, T类型必须重载过等号
	for (int i=0; i<this->length; i++){
		*(this->list+i) = *(c.list+i); 
	}
}
template <class T> Container<T>::~Container(){
	delete [] this->list;
}
template <class T> bool Container<T>::extendSpace(int len){
	// 扩展大小必须大于0
	if (len > 0){
		// 旧数组长度
		unsigned old_length = this->length;
		// 旧数组指针
		T * old_list = this->list;
		// 更新长度
		this->length += len;
		// 开辟新数组
		this->list = new T[this->length];
		// 检查开辟是否成功
		if (this->list != NULL){
			// 移动原有的值
			for (int i=0; i<old_length; i++){
				*(this->list+i) = *(old_list+i);
			};
			// 删除旧数组
			delete [] old_list;
			return true;
		}
		else{
			// 变回原来的数组
			this->list = old_list;
			return false;	
		}
	}
	return false;
}
template <class T> T &Container<T>::operator[] (int index){
	// 防止下标越界
	assert(index < this->length);
	return this->list[index];
}
template <class T> Container<T> Container<T>::operator= (Container<T> &c){
	// 赋值不是自身
	if (this != &c){
		// 如果长度一致
		if (this->length == c.length){
			// 一一赋值即可
			for (int i=0; i<this->length; i++){
				this->list[i] = c.list[i];
			}
		}
		else{
			// 删除原先数组
			delete [] this->list;
			// 新建数组
			this->list = new T[c.length];
			this->length = c.length;
			for (int i=0; i<this->length; i++){
				this->list[i] = c.list[i];
			}
		}
	}
	return *this;
}
// 下行注释是错误(应该是逻辑上的错误), 理由是使用Container<T> *的指针转换, 结果得到的都是T *的指针, 逻辑错误
// template <class T> T * Container<T>::operator Container<T> *(){
/* 非常重要, 指针运算符的重载函数没有返回值 */
//template <class T> Container<T>::operator Container<T> *(){
template <class T> Container<T>::operator T *(){
	// 原本是获取Container类型的指针
	// 重载后, 将Container实例的list(T *)数组的指针返回
	// 使得原本针对数组的函数(比如遍历函数)能够兼容Container类
	return this->list;
}

// 定义一个复数类
class Complex{
	friend ostream &operator<< (ostream &out, Complex c);
	public:
		Complex(){
			realN = 0;
			virtualN = 0;
		}
		Complex(int realN, int virtualN){
			this->realN = realN;
			this->virtualN = virtualN;
		}
		void setValue(int realN, int virtualN){
			this->realN = realN;
			this->virtualN = virtualN;
		}
		Complex operator+ (Complex c){
			int newRealN = this->realN + c.realN;
			int newVirtualN = this->virtualN + c.virtualN;
			return Complex(newRealN, newVirtualN);
		}
		Complex operator= (Complex c){
			this->realN += c.realN;
			this->virtualN += c.virtualN;
			return *this;
		}
	private:
		int realN;
		int virtualN;
};
// 重载cout,支持复数类打印
/* 排错了好久, 最后查看视频找到了错误, 参数和返回值必须是ostream的引用, 即类似传入地址, 而不能够传入复制 */
ostream &operator<< (ostream &out, Complex c){
	// 似乎能设置一个参数, 控制out的输出格式的, 自己用三目运算符的这个语句太复杂了
//	out << c.realN << (c.virtualN >= 0 ? "+" : "") << c.virtualN << 'i' << endl;
	out << c.realN << setiosflags(ios_base::showpos) << c.virtualN << 'i' << resetiosflags(ios_base::showpos) << endl;
	return out;
}

int main(void){
	// 验证无参
	Container<Complex> c1;
	// 验证有参
	Container<Complex> c2(8);
	// 验证扩展函数
	c2.extendSpace(1);
	// 验证[]下标
	cout << "setValue before:" << c2[8] << endl;
	c2[8].setValue(2, -2);
	cout << "setValue after:" << c2[8] << endl;
	// 验证下标越界
//	cout << "index overflow:" << c2[10] << endl;
	// 赋值
	c2 = c1;
	// 验证=赋值
	cout << "after c2 = c1:" << c2[9] << endl;
	
	return 0;
}
