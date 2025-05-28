//#include "LinkAndTemplateInstance.h" // 这是失败的, 原因是自己分析的, 看下面
//#include "LinkAndTemplateInstance.cpp" // 这是成功的, 哎, 真难

#include "LinkAndTemplateInstance.h"

void test(BookShelf<Book *> &bookShelf, string title){
//	bookShelf.getEleByTitle(title);
	bookShelf.display();
}

int main(void){
	return 0;
}