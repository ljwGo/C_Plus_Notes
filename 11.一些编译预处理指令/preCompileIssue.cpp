#include <iostream>
#include "A.h"
//#include "A.h"  重复导入将导致标识符冲突

#define C // ifdef指定的宏必须同一文件中
#ifdef C
#include "A.h"  重复导入将导致标识符冲突
#else
#endif

// 1. #define 设置宏, 在c++中, 宏变量被const变量代替; 带参数的宏被inline内联函数替代
// 2. #undef 删除宏
// 3. #if 常量表达式(表达式非0时编译) 
//    #elif 常量表达式2 
//	  #else 
//    #endif
// 4. ifdef 表示符, 如果该标识符被define定义, 那么执行

using namespace std;

char A::getA(){
	return a;
};
void A::setA(char a){
	this->a = a;
}

int main(void){
	
	return 0;
}
