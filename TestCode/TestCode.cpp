#include <iostream>
#include <string>
#include <mutex>

class some_data
{
private:
	int a;
	std::string b;
public:
	void do_something() {
		std::cout << "do_something()" << std::endl;
	}
};

class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		func(data);
	}
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}

data_wrapper x;
void foo()
{
	x.process_data(malicious_function);
	unprotected->do_something();
}


int main()
{
    std::cout << "Hello World!\n";
}
