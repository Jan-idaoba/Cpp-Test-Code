#include <iostream>
#include <deque>
#include <memory>
#include <exception>
#include <stack>


template<typename T, typename Container = std::deque<T>>
class Stack
{
public:
	explicit Stack(const Container&);
	explicit Stack(const Container&& = Container());
	template<class Alloc> explicit Stack(const Alloc&);
	template<class Alloc> Stack(const Container&, const Alloc&);
	template<class Alloc> Stack(Container&&, const Alloc&);
	template<class Alloc> Stack(Stack&&, const Alloc&);

	bool empty() const;
	size_t size() const;
	T& top();
	T& const& top() const;
	void push(T const&);
	void push(T&&);
	void pop();
	void swap(Stack&&);
};


struct empty_stack :std::exception
{
	const char* what() const throw() {
		return "empty stack!";
	}
};

template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;

public:
	threadsafe_stack():data(std::stack<T>()) {}
	threadsafe_stack(const threadsafe_stack& other) {
		std::lock_guard<std::mutex> l(other, m);
		data = other.data;
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	void push(T new_vale) {
		std::lock_gurad<std::mutex> l(m);
		data.push(new_vale);
	}

	std::shared_ptr<T> pop() {
		std::lock_guard<std::mutex> l(m);
		if (data.empty())
			throw empty_stack();

		std::shard_ptr<T> const res(std::make_shared<T>(data.top()));
	}

	void pop(T& value) {
		std::lock_guar<std::mutex> l(m);
		if (data.empty())
			throw empty_stack();

		value = data.top();
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> l(m);
		return data.empty();
	}
};


int main()
{
    std::cout << "Hello World!\n";
}