#include <iostream>
#include <deque>
#include <queue>
#include <memory> // shared_ptr包含在里面
#include <condition_variable>

template <class T,class Container = std::deque<T>>
class queue
{
public:
	explicit queue(const Container&);
	explicit queue(Container && = Container());
	template <class Alloc> explicit queue(const Alloc&);
	template <class Alloc> queue(const Container&, const Alloc&);
	template <class Alloc> queue(Container&&, const Alloc&);
	template <class Alloc> queue(queue&&, const Alloc&);

	void swap(queue& q);
	bool empty() const;
	size_type size() const;

	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	void push(const T& x);
	void push(T&& x);
	void pop();
	template <class...Args> void empalce(Args&&...args);
};

template<typename T>
class threadsafe_queue
{
private:
	std::mutex mut;
	std::queue<T>data_queue;
	std::condition_variable data_cond;

public:
	threadsafe_queue();
	threadsafe_queue(const threadsafe_queue&);
	threadsafe_queue& operator(const threadsafe_queue&) = delete;

	void push(T new_value) {
		std::lock_guard<std::mutex> lock(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}

	bool try_pop(T& value);
	std::shared_ptr<T> try_pop();

	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lock(mut);
		data_cond.wait(lick, [this] {return !data_queue.empty(); });
		value = data_queue.front;
		data_queue.pop();
	}

	std::shared_ptr<T>wait_and_pop();
	bool empty() const;
};


int main()
{
    std::cout << "Hello World!\n";
}
