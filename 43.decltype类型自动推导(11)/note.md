[toc]

# 1. decltype介绍

功能描述: 返回一个类型的**右值引用**, 不管是否有没有默认构造函数或该类型不可以创建对象

```c++
#include <iostream>
#include <type_traits>

using namespace std;

class A {
public:
	virtual void fn() = 0;

	static const int value = 0;
};

constexpr bool value1 = std::is_same_v<A&&, decltype(declval<A>())>;
constexpr bool value2 = std::is_same_v<A, decltype(declval<A>())>;

int main(void) {
	// 因为是右值引用, 必须立刻赋值
	decltype(declval<A>().value) a = 0;

	cout << value1 << endl;
	cout << value2 << endl;
}
```

