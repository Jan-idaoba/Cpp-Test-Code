#include <iostream>
#include <mutex>
#include <queue>

std::mutex mut;
std::queue<void*>   data_queue;
std::condition_variable data_cond;


void data_preparation()
{
    while (1)
    {
        void* const data = (void*)2022;
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void data_processing_thread()
{
    while (1)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [] {return !data_queue.empty(); });
        void* data = data_queue.front();
        data_queue.pop();
        lk.unlock();
    }
}


int main()
{
    std::cout << "Hello World!\n";
}
