#include <iostream>
#include <list>
#include <algorithm>
#include <future>

// 快速排序---顺序实现

template<class T>
std::list<T> sequential_quick_sort(std::list<T>input)
{
    if (input.empty())
    {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const& pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(),
        [&](T const& t) {return t < pivot; });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    auto new_lower(sequential_quick_sort(std::move(lower_part)));
    auto new_highter(sequential_quick_sort(std::move(input)));

    result.splice(result.end(), new_highter);
    result.splice(result.begin(), new_lower);

    return result;
}



template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if (input.empty())
        return input;

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());    
    T const& pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(), 
                        [&](T const& t) {return t < pivot; });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    std::future<std::list<T>>
        new_lower(std::async(&parallel_quick_sort<T>, std::move(input)));

    auto new_height(parallel_quick_sort(std::move(lower_part)));

    result.splice(result.end(), new_height);
    result.splice(result.begin(), new_lower.get());

    return result;

}

int main()
{
    std::list<int> l{ 5,8,4,9,6,3,1,7,2 };
    auto res = sequential_quick_sort(l);
    auto result = parallel_quick_sort(l);

    return 0;
}
