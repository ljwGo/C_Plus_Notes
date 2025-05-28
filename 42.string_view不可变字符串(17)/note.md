[toc]

# 1. string_view使用

string_view把他看作是**const string \* **就好

它不进行拷贝, 它是只读的.

## 1.1 例子

```c++
string_view foo() {
    string str;
    return string_view(str);  // 指向栈内局部变量
}
```

```c++
string str = "hello";
string_view sv1(str);
string_view sv2 = sv1;

str[2] = 'e';
cout << sv1 << endl;
cout << sv2 << endl;
```

