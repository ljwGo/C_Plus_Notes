#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
	hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&... args)
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}

// �����hashȡֵ�����Խṹ����˵�ǱȽ������
template<typename... Types>
inline std::size_t hash_val(const Types& ...args)
{
	std::size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

struct A {
	int a;
	float b;
	string str;

	bool operator==(const A& other) const {
		return true;
	}
};

// �����ж���������һ����(��Ϊunordered_map�ײ���ʹ��hashֵ��������ķ�ʽ�洢��, �������key��hashֵ��ͬ, ����Ҫ�����ж���������ͬ��Ԫ��)
bool operator== (const A& a, const A& b) {
	return true;
}

struct B {
	bool operator()(const A& a, const A& b) const {
		return 0;
	}
};

struct MyHash {
	size_t operator()(const A& a) const {
		return hash_val(a.a, a.b, a.str);
	}
};

template <typename T>
struct C {
	T value;
};

int main(void) {

	// ��ʾ��֪����ν�A�ṹ��ӳ��Ϊhashֵ
	//unordered_map<A, int> map;	// std::_Uhash_compare<_Kty, _Hasher, _Keyeq>::_Uhash_compare(const std::_Uhash_compare<_Kty, _Hasher, _Keyeq> &)":����������ɾ���ĺ���

	// Key����, value����, ��ȡhashֵ��α��, �ж�key��ȵ�α��
	unordered_map<A, int, MyHash, B> map2;
	unordered_map<A*, int> map3;
	unordered_map<C<A>*, int> map4;

	//map.insert(pair<A, int>(A(), 10));
	map2.insert(pair<A, int>(A(), 10));

	A a;
	map3.insert(pair<A*, int>(&a, 5));

	C<A> c;
	map4.insert(pair<C<A>*, int>(&c, 20));

	// atʹ��
	int a = 0, b = 0, c = 0;
	int* pa = &a, *pb = &b, *pc = &c;

	unordered_map<int*, size_t> map;

	map.insert(std::pair<int*, size_t>(pa, 10));
	cout << map.at(pa) << endl;

	// ������
	cout << map.at(pb) << endl;

	return 0;
}
