#include <iostream>
#include <mutex>

class some_big_object
{

};

void swap(some_big_object& lhs, some_big_object& rhs);

class X
{
private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const& sd) :some_detail(sd) {}

    friend void swap(X& lhs, X& rhs)
    {
        if (&lhs == &rhs)
            return;
        
        std::lock(lhs.m, rhs.m);
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail);
    }
};


class Y
{
private:
    some_big_object some_detail;
    std::mutex  m;

public:
    Y(some_big_object const& sd) :some_detail(sd) {}
    friend void swap(Y& lhs, Y& rhs)
    {
        if (&lhs == &rhs) {
            return;
        }

        std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(lhs.m, std::defer_lock);
        std::lock(lock_a, lock_b);
        swap(lhs.some_detail, rhs.some_detail);
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
