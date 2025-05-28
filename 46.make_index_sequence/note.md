[toc]

# 1. make_index_sequence

​	在模板参数中生成0, 1, 2, ..., N-1的整数序列

## 1.1 实现原理

 **利用模板继承实现迭代的逻辑; 利用偏特化作为迭代结束的条件**

```c++
#include <iostream>

using namespace std;

template <size_t ...NS>
struct my_index_sequence {};

template <size_t N, size_t ...NS>
struct my_make_index_sequence : public my_make_index_sequence<N - 1, N - 1, NS...>{};

template <size_t ...NS>
struct my_make_index_sequence<0, NS...> : public my_index_sequence<NS...> {};

```

## 1.2 使用案例

```c++
#include <iostream>

using namespace std;

template <size_t ...NS>
void foo(index_sequence<NS...> seq) {
	// 展开表达式
	std::initializer_list<int>{(cout << NS << endl, 0)...};
}

template <size_t N>
void fn() {
	foo(make_index_sequence<N>{});
}

int main(void) {
	fn<10>();
}
```

参考make_index_sequence的实现可知.

make_index_sequence\<N\>的**基类是index_sequence<NS...>**, 对于**make_index_sequence\<N\>**的返回值, 可以使用index_sequence<NS...>来接受. 可见如下是**标准使用方式**

```c++
template <size_t ...NS>
void foo(index_sequence<NS...>);

// {}必须要有, 可以提替换为(). 语法越来越怪了.
// make_index_sequence<N>是个具体类型, 加入()或{}表示变量
foo(make_index_sequence<N>{});
```

# 2. 折叠表达式与打表

## 2.1 遍历tuple

对标准使用方式进行扩展, 关键在11行, 这里**提取tuple的模板参数为ARG...**

```c++
#include <iostream>

using namespace std;

template <typename TUPLE, typename FUNC, size_t ...NS>
void wrapper(TUPLE& t, FUNC&& fn, index_sequence<NS...>) {
	static_cast<void>(std::initializer_list<int>{(fn(std::get<NS>(t)), 0)...});
}

template <typename FUNC, typename ...ARG>
void call(std::tuple<ARG...>& t, FUNC&& fn) {  // 关键在这里
	wrapper(t, fn, make_index_sequence<sizeof...(ARG)>{});
}

int main(void) {
	std::tuple t(10, 10.f, std::string("hello template meta programme"));
	call(t, [](auto&& v) {
		cout << v << endl;
		});
}
```

## 2.2 编译期间打表

```c++
#include <iostream>
#include <type_traits>
#include <array>

using namespace std;

// 枚举类型
enum Color {
    RED,
    GREEN,
    BLUE,
};

// 特殊宏, 打印函数签名
template <typename T>
void print_fn() {
#if __GNUC__ || __clang__
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#elif _MSC_VER
    std::cout << __FUNCSIG__ << std::endl;
#endif
}

template <size_t N>
void print_fn() {
#if __GNUC__ || __clang__
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#elif _MSC_VER
    std::cout << __FUNCSIG__ << std::endl;
#endif
}

template<auto value>
constexpr auto enum_name() {
    std::string_view name;
#if __GNUC__ || __clang__
    name = __PRETTY_FUNCTION__;
    std::size_t start = name.find('=') + 2;
    std::size_t end = name.size() - 1;
    name = std::string_view{ name.data() + start, end - start };
    start = name.rfind("::");
#elif _MSC_VER
    name = __FUNCSIG__;
    std::size_t start = name.find('<') + 1;
    std::size_t end = name.rfind(">(");
    name = std::string_view{ name.data() + start, end - start };
    start = name.rfind("::");
#endif
    return start == std::string_view::npos ? name : std::string_view{
            name.data() + start + 2, name.size() - start - 2
    };
}

// 必须是连续的枚举值
template<typename T, std::size_t N = 0>
constexpr auto enum_max() {
    constexpr auto value = static_cast<T>(N);
    if constexpr (enum_name<value>().find(")") == std::string_view::npos)
        return enum_max<T, N + 1>();
    else
        return N;
}

// 屠龙技
template<typename ENUM>
constexpr auto foo(size_t index) {
    static_assert(std::is_enum_v<ENUM>);
    constexpr static size_t count = enum_max<ENUM>();
    // C++20. 模板lambda
    constexpr static std::array<string_view, count> data =
    []<size_t ...N>(index_sequence<N...>) {  // 利用lambda简写
        return std::array<string_view, count>{ enum_name<static_cast<ENUM>(N)>()... };
    }(make_index_sequence<count>{});
    
    // 编译期间生成一个3大小的字符数组
    return data[index];
}

int main(void) {
    // 获取函数签名
    print_fn<int>();  // void __cdecl print_fn<int>(void)
    // 获取枚举类型名
    print_fn<RED>();  // void __cdecl print_fn<RED>(void)
    // 获取枚举字符串
    std::cout << enum_name<RED>() << std::endl;  // RED

    // 不存在的枚举
    constexpr Color color = static_cast<Color>(-1);
    std::cout << enum_name<color>() << std::endl;  // (enum Color)0xffffffffffffffff
    
    cout << foo<Color>(RED) << endl;
    cout << foo<Color>(GREEN) << endl;
    cout << foo<Color>(BLUE) << endl;
}
```



