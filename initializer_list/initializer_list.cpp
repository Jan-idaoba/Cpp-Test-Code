#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

class MyClass
{
public:
	MyClass(initializer_list<int> list);
	~MyClass();


	vector<int>	m_vecint;
};

MyClass::MyClass(initializer_list<int> list)
{
	for (auto it = list.begin();it != list.end(); ++it)
	{
		m_vecint.push_back(*it);
	}
}

MyClass::~MyClass()
{
}

int main()
{
	MyClass mc = { 0,1,2,3,4,5 };
	for (auto it = mc.m_vecint.begin();it!=mc.m_vecint.end();++it)
	{
		cout << *it << endl;
	}
	system("pause");
}
