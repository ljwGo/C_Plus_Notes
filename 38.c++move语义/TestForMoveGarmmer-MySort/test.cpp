#include "pch.h"-
#include "gtest/gtest.h"
// 必须指定文件夹
#include "../TestForMoveGarmmer/MySort.h"
#include <iostream>

TEST(MySort, SpeedSort) {

	int a[10] = {
		9, 5, 3, 6, 7, 1, 0, 2, 8, 4
	};

	SpeedSort(a, a + 10);

	for (int i = 0; i < 10; i++) {
		std::cout << a[i] << std::endl;
		EXPECT_EQ(a[i], i);
	}
}