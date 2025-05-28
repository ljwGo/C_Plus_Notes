#pragma once

template <typename T>
void SpeedSortMove(T first, T end) {
	auto i = first;
	auto j = end - 1;
	auto temp = std::move(*first);
	//auto temp = *first;

	while (i < j) {
		while (*j >= temp && i < j) {
			j--;
		}
		*i = std::move(*j);

		while (*i <= temp && i < j) {
			i++;
		}
		*j = std::move(*i);
	}

	if (i <= j) {
		*i = std::move(temp);
	}

	if (i > first) {
		SpeedSortMove(first, i);
	}

	if (end-1 > j) {
		SpeedSortMove(j+1, end);
	}
}

template <typename T>
void SpeedSort(T first, T end) {
	auto i = first;
	auto j = end - 1;
	auto temp = *first;
	//auto temp = *first;

	while (i < j) {
		while (*j >= temp && i < j) {
			j--;
		}
		*i = *j;

		while (*i <= temp && i < j) {
			i++;
		}
		*j = *i;
	}

	if (i <= j) {
		*i = temp;
	}

	if (i > first) {
		SpeedSort(first, i);
	}

	if (end - 1 > j) {
		SpeedSort(j + 1, end);
	}
}