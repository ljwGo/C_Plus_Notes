#pragma once
#include <random>
#define N 4
#define DEFAULTSIZE 10000000

class ComplexClass {
public:
	ComplexClass() {
		elements = new unsigned int[DEFAULTSIZE];
		this->size = DEFAULTSIZE;

		// ��������
		for (int i = 0; i < size; i++) {
			elements[i] = fabs(rd() % N);
			sum += elements[i];
		}
	}

	ComplexClass(int size) {
		elements = new unsigned int[size];
		this->size = size;
		
		// ��������
		for (int i = 0; i < size; i++) {
			elements[i] = fabs(rd() % N);
			sum += elements[i];
		}
	}

	ComplexClass(ComplexClass const& c02) {
		// ɾ��ԭ����Դ
		if (elements != nullptr) {
			delete[] elements;
			elements = nullptr;
		}

		// copy����
		elements = new unsigned[c02.size];
		this->size = c02.size;
		this->sum = 0;

		for (int i = 0; i < size; i++) {
			elements[i] = c02.elements[i];
			sum += elements[i];
		}
	}

	ComplexClass(ComplexClass && c02) noexcept{
		// ������������
		unsigned int *temp;
		temp = c02.elements;
		c02.elements = this->elements;
		this->elements = temp;

		// ������С����
		unsigned int tempSize;
		tempSize = size;
		size = c02.size;
		c02.size = tempSize;

		// �����ܺ�
		unsigned int tempSum;
		tempSum = sum;
		sum = c02.sum;
		c02.sum = tempSize;
	}

	~ComplexClass() {
		delete[] elements;
	}

	ComplexClass& operator= (ComplexClass& c02) {
		// ɾ��ԭ����Դ
		delete[] elements;

		// copy����
		elements = new unsigned[c02.size];
		this->size = c02.size;
		this->sum = 0;

		for (int i = 0; i < size; i++) {
			elements[i] = c02.elements[i];
			sum += elements[i];
		}
		return *this;
	}

	// �������Ļ�, ע���ԵЧӦ
	// ԭ������Դ���滻��c02��, ��֪��ʲôʱ������, ��������Դ���ܲ�����ԵЧӦ
	// �����߳���
	ComplexClass& operator= (ComplexClass&& c02) noexcept{
		// ������������
		unsigned int* temp;
		temp = c02.elements;
		c02.elements = this->elements;
		this->elements = temp;

		// ������С����
		unsigned int tempSize;
		tempSize = size;
		size = c02.size;
		c02.size = tempSize;

		// �����ܺ�
		unsigned int tempSum;
		tempSum = sum;
		sum = c02.sum;
		c02.sum = tempSize;

		return *this;
	}

	// ��С�Ƚϵ��������ܺ�
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
	unsigned int* elements = nullptr;  // ��Ϊ����ָ��, ����Ĭ�Ͽ���������������
	std::random_device rd;
};