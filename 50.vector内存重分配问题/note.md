```c++
#include <vector>
#include <iostream>

using namespace std;

int main(void) {

	std::vector<int> vec;
	cout << "size(): " << vec.size() << endl;
	cout << "capcity(): " << vec.capacity() << endl;

	vec.push_back(0);
	int* pi = &vec[0];
	cout << "size(): " << vec.size() << endl;
	cout << "capcity(): " << vec.capacity() << endl;
	cout << "pi address: " << pi << endl;
	cout << "vec address: " << &vec[0] << endl;

	vec.push_back(1);
	cout << "size(): " << vec.size() << endl;
	cout << "capcity(): " << vec.capacity() << endl;
	cout << "pi address: " << pi << endl;
	cout << "vec address: " << &vec[0] << endl;  // 移动了

	vec.push_back(2);
	cout << "size(): " << vec.size() << endl;
	cout << "capcity(): " << vec.capacity() << endl;
	cout << "pi address: " << pi << endl;
	cout << "vec address: " << &vec[0] << endl;  // 移动了
	return 0;
}
```

