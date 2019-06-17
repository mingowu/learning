#include <iostream>

namespace cplusplus_auto_extension
{
auto distance(int p_first, int p_second)
{
    return p_first > p_second ? p_first - p_second : p_second - p_first;
}

void print(int p_i)
{
    std::cout << "This integral value is "<< p_i << std::endl;
}

void print(float p_f)
{
    std::cout << "This float value is "<< p_f << std::endl;
}

void deduceFunctionReturnType()
{
    print(distance(3, 15));
}

} //namespace cplusplus_auto_extension

int main()
{
    cplusplus_auto_extension::deduceFunctionReturnType();
    return 0;
}
