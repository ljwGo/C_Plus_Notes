[toc]

# 1. 模板参数为指针类型

```c++
#include <iostream>

using namespace std;

struct B {
	void fn() { cout << "B" << endl; }
};

template <typename T>
class A {

public:
	T a;
	
	void fn() {
		a.fn();
	}

	void pfn() {
		a->fn();
	}
};

int main(void) {

	B b;
	A<B> a;
	a.fn();
	//a.pfn();  // error. T is B

	A<B*> a2;
	//a2.fn();  // error. T is B*
	a2.pfn();

	return 0;
}
```

