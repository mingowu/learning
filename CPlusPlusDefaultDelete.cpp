#include <iostream>
#include <string>
#include <memory>

namespace cplusplus_default_delete
{
class X
{
public:
    X() = default;
    X(int p_i) : m_i(p_i)
    {}
    X(const X&) = delete;
    X& operator = (const X &) = delete;
    ~X() = default;

    void doSomething() {}
private:
    int m_i;
};

void useDefault()
{
    X l_x;
    l_x.doSomething();
    
    // X l_x2 = l_x;
    // l_x2.doSomething();
}

void useDelete()
{
    // X l_x;
    // X l_x2 = l_x;
    // l_x2.doSomeThing();
}

} //namespace cplusplus_default_delete


int main()
{
    cplusplus_default_delete::useDefault();
    cplusplus_default_delete::useDelete();
    return 0;
}
