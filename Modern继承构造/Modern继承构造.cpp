#include <iostream>
using namespace std;

class Base
{
public:
    int iVal;
    int iVal2;

    Base() : iVal(1)
    {

    }

    Base(int ival)
        : Base()
    {
        iVal2 = ival;
    }
};

class Subclass : public Base
{
public:
    using Base::Base;
};

int main()
{
    Subclass s(6);
    cout << s.iVal << endl;
    cout << s.iVal2 << endl;
    system("pause");
}
