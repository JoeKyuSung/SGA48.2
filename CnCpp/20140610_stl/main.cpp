#include <iostream>
#include <conio.h>
#include <vector>
#include <list>
#include <new>

using namespace std;

#pragma push_macro("new")
void* operator new (size_t s)
{
	void* ptr = ::malloc(s);

	cout << "new addr : " << ptr << ", size(byte) : " << s;
	cout << ", size : " << s/4 << endl;

	return ptr;
}
#pragma pop_macro("new")
#pragma push_macro("delete")
void operator delete (void* ptr)
{
	cout << "del addr : " << ptr << endl;

	::free(ptr);
}
#pragma pop_macro("delete")

void foo()
{
	list<int> a;

	_getch();

	for (int i = 0; i < 10; i++)
	{
		a.push_back(i);
	}

	list<int>::iterator it;
	for (it = a.begin(); it != a.end(); it++)
	{
		cout << *it << endl;
	}

	_getch();

	it = a.begin();
	advance(it, 5);

	a.erase(it);

	for (it = a.begin(); it != a.end(); it++)
	{
		cout << *it << endl;
	}

}

int main(void)
{
	foo();

	_getch();
	return 0;
}