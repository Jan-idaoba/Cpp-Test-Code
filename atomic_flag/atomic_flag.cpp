#include <iostream>
#include <atomic>
#include <vector>
#include <thread>


// ×ÔÐý»¥³âËø
//class spinlock_mutex
//{
//private:
//	std::atomic_flag flag;
//public:
//	spinlock_mutex() :
//		flag(ATOMIC_FLAG_INIT) {}
//
//	void lock() {
//		while (flag.test_and_set(std::memory_order_release));
//	}
//
//	void unlock() {
//		flag.clear(std::memory_order_release);
//	}
//};

// È«Ðò----ÐòÁÐÒ»ÖÂ
std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst))
    {
        ++z;
        std::cout << z << std::endl;
    }    
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst))
    {
        ++z;
        std::cout << z << std::endl;
    }    
}

int main()
{
	// atomic_flag
    //std::atomic_flag f = ATOMIC_FLAG_INIT;
    //f.test_and_set(std::memory_order_release);
    //f.clear(std::memory_order_release);
    //bool x = f.test_and_set();

    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();


    system("pause");


	// atomic_bool
	//std::atomic<bool> b(false);

    return 0;

}