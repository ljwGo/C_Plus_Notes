/*
参考:https://en.cppreference.com/w/cpp/language/sfinae
其他内容查看笔记
*/

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
