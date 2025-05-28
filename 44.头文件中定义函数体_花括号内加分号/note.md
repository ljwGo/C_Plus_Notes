[toc]

# 1. 例子

```c++
// test.h
#pragma once

#include <iostream>

using namespace std;

class Test {
public:
	void fn() { cout << "test" << endl; }  // 这个;必须要有
	void fn2() { cout << "test2" << endl; }  // 这个;必须要有
};
```

多个文件同时导入, 不会引起**重定义问题**

```c++
// test2.h
#include "test.h"

class Test2 {};
```

```c++
// test3.h
#include "test.h"
```

