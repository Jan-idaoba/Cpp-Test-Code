#include <iostream>
#include <tuple>

using namespace std;

tuple<int, double, string> func() 
{
    return make_tuple(1, 1.2, "test");
}

int main()
{
   tuple<int,double,string> a = func();
   auto [x, y, z] = func();

   cout << x << "," << y << "," << z << endl;
   system("pause");
}

