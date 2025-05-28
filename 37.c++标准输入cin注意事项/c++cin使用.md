# cin标准输入的注意事项

## 1. cin的基本使用

参考[C++中cin的详细用法_大大大大大大旭的博客-CSDN博客_c++ cin](https://blog.csdn.net/bravedence/article/details/77282039)



## 2. cin读取字符后, 会有状态标记

cin在每次读取完字符后, 会根据情况设置**状态码**, 具体状态码类型参考1.cin的基本使用

这里说一个常见的导致错误的情况, 就是**输入类型与存储变量类型不一致, 导致缓冲区剩余字符未被读取导致的错误**

```c++
	int choice;
	string str;
	
	// 这里输入不是整形的数据, 比如输入 cin字符串
	cin >> choice;
	cin >> str;
	
	cout << "choice: " << choice << endl;
	cout << "str: " << str << endl;

	// 结果
    choice: 0
    str:
```

可见, 第一次输入时, 给int类型赋值string, int变量无法接收, 被**默认值为0**,; 第二次cin输入**被直接跳过**, 也没有接收缓冲区, 剩余的cin\n字符



### 2.1 查看状态标记

```c++
	int choice;
	string str;
	
	// 这里输入不是整形的数据, 比如输入 cin字符串
	cin >> choice;

	cout << "good: " << cin.good() << endl;  // 读取是否成功, 1表示成功, 0表示失败
	cout << "bad: " << cin.bad() << endl;  // 读取是否发生不可挽回错误, 1发生, 0未发生
	cout << "fail: " << cin.fail() << endl;  // 读取是否发生可挽回错误, 1发生, 0未发生

	// 结果
    good: 0
    bad: 0
    fail: 1
```



### 2.2 clear清除状态标记

cin的错误不是硬性的, 不像报错后程序就停止了; 

使用clear()就可以清除状态标记了, 默认清除的是ios::gootbit

**清除之后cin就能被使用了**

```c++
	cin >> choice;
	cin.clear();
	cin >> str;

	cout << "choice: " << choice << endl;
	cout << "str: " << str << endl;

	// 结果
	choice: 0
    str: cin
```

很明显, 第二次cin没有阻塞, 第一次cin错误的输入被第二次cin直接接收了

**如果, 不想让上一次的输入影响到下一次, 最后在执行cin后, 对缓冲区进行清空**



**注意:**

> (1) clear是将**其它所有状态置为0, 将参数指定的当前状态码值为1**



### 2.3 ignore清空缓冲区

```c++
	// 这里输入不是整形的数据, 比如输入 cin字符串
	cin >> choice;
	cin.clear();
	cin.ignore(1000, '\n');
	cin >> str;

	cout << "choice: " << choice << endl;
	cout << "str: " << str << endl;

	// 结果
    cin
    success
    choice: 0
    str: success
```



**注意:**

> (1) 网上的**std::numeric_limits< streamsize >::max()**提示未定义, 不知道是不是被删除了, 还是改名了



## 3.是否处理缓冲区中的\n

### 3.1 >>不处理\n

```c++
	string str;
	char word02;

	cin >> str;
	cin.get(word02);

	cout << "str: " << str << endl;
	cout << "word02: " << word02 << endl;

	// 结果
    cin
    str: cin
    word02:
```

### 3.2 get不处理\n

```c++
    char word01;
	char word02;

    cin.get(word01);
	cin.get(word02);

	cout << "word01: " << word01 << endl;
	cout << "word02: " << word02 << endl;

	// 结果
    a
    word01: a
    word02:
```

### 3.3getline读取到\n时会处理掉

```c++
	char cArray[20] = {NULL};
	char word02;

    cin.getline(cArray, 5);
	cin.get(word02);

	cout << "cArray: " << cArray << endl;
	cout << "word02: " << word02 << endl;

	// 情况一: 行字符数大于读取数, \n为被getline处理
	too long
    cArray: too
    word02:

	// 情况二: 行字节数小于读取书, \n被处理
    abc
    a
    cArray: abc
    word02: a
```

**注意:**

> (1)getline会读取一行数据, 截取其中一部分字符, 并将输入流中多余的字符丢弃, 末尾\n将被保留; 如果全部接收, 包括\n, 将会把\n替换为\0