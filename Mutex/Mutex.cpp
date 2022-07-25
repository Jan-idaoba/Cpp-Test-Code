#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int iVal)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(iVal);
}

bool list_contains(int iVal)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), iVal) != some_list.end();
}

int main()
{
    std::cout << "Hello World!\n";
    return 0;
}
