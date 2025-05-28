[toc]

# 1. initializer_list变长初始化器

使用

```c++
#include <iostream>
#include <vector>

using namespace std;

class A {
public:
	std::vector<int> container;

	A(initializer_list<int> list) {
		for (auto iter = list.begin(); iter != list.end(); ++iter) {
			container.push_back(*iter);
		}
	}
};

int main(void) {
	int arr[]{ 1 ,2 ,3 };
	A a{ 1,2,3,4,5 };  // 自定义类也可以使用初始化器了
}
```

initializer_list类型特点

* 除了使用初始化器{}和赋值外, 不能修改内部值, 他是只读的.
* 元素访问只能使用迭代器
* 同一类型
* std::initializer_list 是非常高效的.它的内部并不负责保存初始化列表中元素的拷贝,仅仅存储了列表中元素的引用而已.

# 2. 错误使用

```c++
std::initializer_list<int> func(void)
{
    int a = 1, b = 2;
    return { a, b }; // a、 b 在返回时并没有被拷贝
}
```

