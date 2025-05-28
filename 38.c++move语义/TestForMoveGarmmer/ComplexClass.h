#pragma once
#include <random>
#define N 4
#define DEFAULTSIZE 10000000

class ComplexClass {
public:
	ComplexClass() {
		elements = new unsigned int[DEFAULTSIZE];
		this->size = DEFAULTSIZE;

		// 存放随机数
		for (int i = 0; i < size; i++) {
			elements[i] = fabs(rd() % N);
			sum += elements[i];
		}
	}

	ComplexClass(int size) {
		elements = new unsigned int[size];
		this->size = size;
		
		// 存放随机数
		for (int i = 0; i < size; i++) {
			elements[i] = fabs(rd() % N);
			sum += elements[i];
		}
	}

	ComplexClass(ComplexClass const& c02) {
		// 删除原本资源
		if (elements != nullptr) {
			delete[] elements;
			elements = nullptr;
		}

		// copy数据
		elements = new unsigned[c02.size];
		this->size = c02.size;
		this->sum = 0;

		for (int i = 0; i < size; i++) {
			elements[i] = c02.elements[i];
			sum += elements[i];
		}
	}

	ComplexClass(ComplexClass && c02) noexcept{
		// 交换核心数据
		unsigned int *temp;
		temp = c02.elements;
		c02.elements = this->elements;
		this->elements = temp;

		// 交换大小数据
		unsigned int tempSize;
		tempSize = size;
		size = c02.size;
		c02.size = tempSize;

		// 交换总和
		unsigned int tempSum;
		tempSum = sum;
		sum = c02.sum;
		c02.sum = tempSize;
	}

	~ComplexClass() {
		delete[] elements;
	}

	ComplexClass& operator= (ComplexClass& c02) {
		// 删除原本资源
		delete[] elements;

		// copy数据
		elements = new unsigned[c02.size];
		this->size = c02.size;
		this->sum = 0;

		for (int i = 0; i < size; i++) {
			elements[i] = c02.elements[i];
			sum += elements[i];
		}
		return *this;
	}

	// 仅交换的话, 注意边缘效应
	// 原本的资源被替换到c02里, 不知道什么时候销毁, 遗留的资源可能产生边缘效应
	// 比如线程锁
	ComplexClass& operator= (ComplexClass&& c02) noexcept{
		// 交换核心数据
		unsigned int* temp;
		temp = c02.elements;
		c02.elements = this->elements;
		this->elements = temp;

		// 交换大小数据
		unsigned int tempSize;
		tempSize = size;
		size = c02.size;
		c02.size = tempSize;

		// 交换总和
		unsigned int tempSum;
		tempSum = sum;
		sum = c02.sum;
		c02.sum = tempSize;

		return *this;
	}

	// 大小比较的是两者总和
	bool operator< (ComplexClass& const c02) {
		long c02Sum = 0;
		long c01Sum = 0;

		for (int i = 0; i < size; i++) {
			c01Sum += elements[i];
		}

		for (int i = 0; i < c02.size; i++) {
			c02Sum += c02.elements[i];
		}
	
		return c01Sum < c02Sum;
	}

	bool operator<= (ComplexClass& const c02) {
		long c02Sum = 0;
		long c01Sum = 0;

		for (int i = 0; i < size; i++) {
			c01Sum += elements[i];
		}

		for (int i = 0; i < c02.size; i++) {
			c02Sum += c02.elements[i];
		}

		return c01Sum <= c02Sum;
	}

	bool operator> (ComplexClass& const c02) {
		long c02Sum = 0;
		long c01Sum = 0;

		for (int i = 0; i < size; i++) {
			c01Sum += elements[i];
		}

		for (int i = 0; i < c02.size; i++) {
			c02Sum += c02.elements[i];
		}

		return c01Sum > c02Sum;
	}

	bool operator>= (ComplexClass& const c02) {
		long c02Sum = 0;
		long c01Sum = 0;

		for (int i = 0; i < size; i++) {
			c01Sum += elements[i];
		}

		for (int i = 0; i < c02.size; i++) {
			c02Sum += c02.elements[i];
		}

		return c01Sum >= c02Sum;
	}

	unsigned int size;
	unsigned int sum = 0;
	unsigned int* elements = nullptr;  // 因为存在指针, 所以默认拷贝函数不起作用
	std::random_device rd;
};