[toc]

# 0. 序言

参考[什么情况下需要在 C++ 中使用 return std::move(X)-CSDN博客](https://blog.csdn.net/Kovnt/article/details/139413925)



# 1. Return返回值

在C++17后, **RVO(返回值优化)和 NRVO(具名返回值优化)**进入标准,(无论在此之前还是后), 返回一个右值引用对象还会影响函数重载决议(体现在阻止NRVO上).

对于函数返回值, 一般不需要使用move语义, 因为函数返回值有**更好的优化方法**

```c++
#include <iostream>

using namespace std;

class B;

class A
{
public:
	A() { puts("A()"); };
	A(const A& a) { puts("A(&)"); };
	A(A&& a) noexcept { puts("A(&&)"); };
	~A() { puts("~A()"); };

	B* b;
};

class B {
public:
	B(int val) { puts("B()"); value = val; };
	B(const B& a) { puts("B(&)"); };
	B(B&& a) noexcept { puts("B(&&)"); };
	~B() { puts("~B()"); value = 10; };

	int value;
};

A foo() {
	A a;
	B b(20);

	a.b = &b;
	return a;
}

int main(void) {
	A a = foo();
	cout << a.b->value << endl;;
}

/*
执行顺序:
A()
B()
~B()
10
~A()
*/
```

可见局部变量A的生命周期**延长了**, 只产生了一个对象.

```c++
#include <iostream>

using namespace std;

class A
{
public:
	A() { puts("A()"); };
	A(const A& a) { puts("A(&)"); };
	A(A&& a) noexcept { puts("A(&&)"); };
	~A() { puts("~A()"); };
};

A foo() {
	A a;
	return std::move(a);
}

int main(void) {
	A a = foo();
}

/*
A()
A(&&)
~A()
~A()
*/
```

产生了一次不必要的右值拷贝

# 2. 需要使用move的情景

​	当**被转移的对象生命周期大于函数域时**, 可以转移.

比如**对象的属性**

```c++
#include <iostream>

using namespace std;

class A
{
public:
	A() { puts("A()"); };
	A(const A& a) { puts("A(&)"); };
	A(A&& a) noexcept { puts("A(&&)"); };
	~A() { puts("~A()"); };
};

class B {
public:
	A m;
	A foo() {
    return m;  // 结果1
		return std::move(m);  // 结果2
	}
};

int main(void) {
	B b;
	A a = b.foo();
  cout << "---" << endl;
}

/*
结果1
A()
A(&)
---
~A()
~A()

结果2
A()
A(&&)
---
~A()
~A()
*/
```

因为m是A的属性, foo()返回的值不是foo内的局部变量, 所以必须进行**拷贝**.

因为不能**使返回值影响其他作用域的值**.



## 2.1 (C++17)解枸赋值, 也叫结构化绑定

```c++
#include <iostream>

using namespace std;

class A
{
public:
	A() { puts("A()"); };
	A(const A& a) { puts("A(&)"); };
	A(A&& a) noexcept { puts("A(&&)"); };
	~A() { puts("~A()"); };
};

A foo() {
	// a,b,c为右值引用类型
	auto [a, b, c] = std::tuple<A, float, std::string>(A(), 2.0f, "hello");
	cout << "---" << endl;
	return a;  // 结果1
  return std::move(a);  // 结果2
}

int main(void) {
	A a = foo();
}

/*
结果1
A()
A(&&)
~A()
---  // 使用引用拷贝
A(&)
~A()
~A()

结果2
A()
A(&&)
~A()
---
A(&&)
~A()
~A()
*/
```



