#include <vector>
#include "ComplexClass.h"
#include "MySort.h"
#include <iostream>
#include <chrono>

using namespace std;

int main(void) {
	std::swap();
	vector<ComplexClass> v(10);
	vector<ComplexClass> v02(v);

	int i = 1;
	for (auto c : v) {
		cout << i++ << ": " << c.sum << endl;
	}

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

	SpeedSort<std::vector<ComplexClass>::iterator>(v.begin(), v.end());

	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	cout << "Speed sort(no move): " << std::endl;

	i = 1;
	for (auto c : v) {
		cout << i++ << ": " << c.sum << endl;
	}

	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "It took me " << time_span.count() << " seconds." << endl << endl;

	//-----------------------------move------------------------------------

	t1 = chrono::steady_clock::now();

	SpeedSortMove<std::vector<ComplexClass>::iterator>(v02.begin(), v02.end());

	t2 = chrono::steady_clock::now();

	cout << "Speed sort(move): " << std::endl;

	i = 1;
	for (auto c : v02) {
		cout << i++ << ": " << c.sum << endl;
	}

	time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "It took me " << time_span.count() << " seconds." << endl << endl;;

	return 0;
}