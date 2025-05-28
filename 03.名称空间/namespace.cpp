#include <iostream>
// using namespace std; 指定使用的名称空间
// 名称空间的作用是尽量避免导入库中函数的名称和 用户自定义名称冲突

void cout(){
	std::cout << "虽然这样做很蠢, 但是我们可以看到对同名函数进行了区分" << std::endl;
}

int main(void){
	std::cout << "指定详细的名称空间下的函数" << std::endl;
	cout();
	return 0;
}
