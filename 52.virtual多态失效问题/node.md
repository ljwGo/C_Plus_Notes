```c++
struct Base {
	virtual void fn() {
		cout << "base fn" << endl;
	}
};

struct Derive : public Base
{
	virtual void fn() {
		cout << "derive fn" << endl;
    Base::fn();
	}
};



Base* base = new Derive();

std::vector<Base> vec;
vec.push_back(std::move(*base));

// 赋值导致多态失效(derive赋值为base类型)
base->fn();  // derive fn
vec[0].fn();  // base fn

delete base;
```

