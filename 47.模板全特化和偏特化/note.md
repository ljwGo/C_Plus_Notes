[toc]

# 0. 序言

​	模板的全特化和偏特化是实现模板元编程的原理之一. 他可以定义特殊情况下的不同行为. 可以作为编译期间计算, 递归的结束条件.



# 1. 模板的全特化和偏特化

模板全特化和偏特化:

>可以为某些特殊的模板特化, 提供不同的操作实现(类似函数重载, 以实现不同形参下的不同功能).

```c++
// 要使用模板全特化或偏特化, 需要模板名称一致
// 主模板是模板类型参数个数最多的
template <typename T, typename U>
struct A{
	A() { cout << "A1" << endl; }
};

// 模板全特化: 对主模板的全部模板类型参数指定具体值
template <>
struct A<float, float>{
	A() { cout << "A2" << endl; }
};

// 模板偏特化: 对主模板的部分模板类型参数指定具体值
template <typename U>
struct A<float, U> {
	A() { cout << "A3" << endl; }
};

int main(void) {
	// 特化类型只是占位符, 仍然需要传入相同数量的模板实参
	A<int, int> a;  // 主模板
	A<float, int> b;  // 偏特化
	A<float, float> b;  // 全特化
}
```



# 2. 模板函数的全特化和偏特化

可以看到模板函数的全特化和偏特化与模板稍有不同, **其特点是要求有相同数量的形参, 不要求显式指定模板实参**

当指定了具体的模板实参, 那么匹配过程中, **模板实参的个数要求与模板中的形参个数严格相同**

```c++
// 要使用模板全特化或偏特化, 需要模板名称一致
// 主模板是模板类型参数个数最多的
template <typename T, typename U>
void fn(const T& t, const U& u) {
	cout << "fn1" << endl;
};

// 模板全特化: 对主模板的全部模板类型参数指定具体值
template <>
void fn(const double& t, const double& u) {
	cout << "fn2" << endl;
};

// 模板偏特化: 对主模板的部分模板类型参数指定具体值
template <typename T>
void fn(const T& t, const float& u) {
	cout << "fn3" << endl;
};

int main(void) {
	// 模板函数因为可以从实参推到类型, 所以不要求传入具体的模板实参
	fn<int, int>(10, 10);  // 主模板
	fn<int, float>(10, 10.f); // 偏特化失败(模板参数个数不一致)
	fn<int>(10, 10.f); // 偏特化
	fn<double, double>(10.f, 10.f);  // 全特化
	fn<double, double>(10, 10);  // 全特化
	fn<>(10., 10.);  // 全特化
	fn<>(10.f, 10.f);  // 偏特化
  fn<>(10, 10);  // 主模板
}
```



# 3. 小结

* 偏特化优先级更高, 全特化优先级最高;
* 模板的特化类型只是占位符, 仍然需要传入和主模板相同数量的模板实参
* 模板函数的特化类型书写在形参列表上, 注意模板和模板函数特化的区别



# 4. 右值案例

```c++
#include <iostream>

#define DN 5

using namespace std;

template <size_t N, size_t ...NN>
struct foo {
	foo() { cout << "foo1" << endl; }
	static constexpr size_t value = N + foo<NN...>::value;
};

template <>
struct foo<DN> {
	foo() { cout << "foo2" << endl; }
	static constexpr size_t value = DN;
};


int main(void) {
	foo<1, 2, 3, 4, 5> a;  // 只调用一次foo的构造函数.

	int i = foo<1, 2, 3, 4, 5>::value;

	cout << i << endl;
}
```

