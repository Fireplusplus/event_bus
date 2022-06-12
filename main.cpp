#include <stdio.h>
#include "events.h"

class Base {
public:
	virtual void print(int a) = 0;
};

class Test_One : public std::enable_shared_from_this<Test_One>,
				public Base {
public:
	virtual void print(int a) override {
		printf("This Is Test Print: %d !\n", a);
	}
};

class Test_Two : public std::enable_shared_from_this<Test_Two>,
				public Base {
public:
	virtual void print(int a) override {
		printf("This Is Test2 Print: %d !\n", a);
	}
};


int main(int argc, char *argv[])
{
	auto ptr1 = std::make_shared<Test_One>();
	auto weak_ptr1 = std::weak_ptr<Base>(ptr1);
	auto ptr2 = std::make_shared<Test_Two>();
	auto weak_ptr2 = std::weak_ptr<Base>(ptr2);
	
	EventBus<Base>::Register(weak_ptr1);
	EventBus<Base>::Register(weak_ptr2);
	
	EventBus<Base>::OnEvent(&Base::print, 123);

	INFO("unregister ptr1");
	EventBus<Base>::Unregister(weak_ptr1);
	EventBus<Base>::OnEvent(&Base::print, 123);

	INFO("unregister ptr2");
	EventBus<Base>::Unregister(weak_ptr2);
	EventBus<Base>::OnEvent(&Base::print, 123);

	return 0;
}

