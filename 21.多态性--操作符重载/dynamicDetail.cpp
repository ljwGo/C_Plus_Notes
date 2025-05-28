#include <iostream>
using namespace std;
// 一维数组可以
void func(int n){
	int *a = new int[n];
};
// 二维数组不可以
void func(int n, int m){
	int *a = (int *)new int[n][m];
}
int main(void){
	int n = 10;
	func(n);
	return 0;
}
