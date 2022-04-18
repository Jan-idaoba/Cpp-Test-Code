#include <iostream>
#include <map>
using namespace std;

template<typename Key,typename Value,typename F>
void update(map<Key, Value>& m, F foo)
{
	for (auto&& [key, value] : m)
		value = foo(key);
}

template<typename ...T>
auto average(T ...t)
{
	return (t + ...) / sizeof...(t);
}

int main()
{
	map<string, long long int>m{ 
		{"a",1},
		{"b",2}, 
		{"c",3}
	};

	update(m, [](string key)->long long int
		{
			return hash<string>{}(key);
		});

	for (auto&& [key,value] : m)
	{
		cout << key << ":" << value << endl;
	}

	cout << average(1, 2, 3, 4, 5, 6, 7, 8, 9) << endl;
	system("puase");
}
