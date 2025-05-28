#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <random>
#include <iostream>

using namespace Eigen;
using namespace std;

int main(void) {
	std::random_device rd;
	cout << "随机数rd(): " << rd() << endl; // 3731345192 2818651936

	// 根据随机种子, 同样的种子得到相同的随机数列(32位)
	std::mt19937 rng(0); 
	cout << "随机数1: " << rng() << endl;  // 2357136044
	cout << "随机数2: " << rng() << endl;  // 2546248239
	cout << "随机数3: " << rng() << endl;  // 3071714933

	// 必须使用随机序列作为引擎(分布生成的队列也是随机数列)
	std::uniform_int_distribution<int> dist(0, 11);
	cout << "随机数分布1: " << dist(rng) << endl;  
	cout << "随机数分布2: " << dist(rng) << endl;
	cout << "随机数分布3: " << dist(rng) << endl;


	return 0;
}