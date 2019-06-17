#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>

namespace cplusplus_lambda
{
void print(int p_i)
{
    std::cout << "This integral value is "<< p_i << std::endl;
}

void storeAsFunction()
{
    std::function<void(int)> l_print = print;
    l_print(5);

    std::function<bool(int, int)> l_isLess = [](int p_lhs, int p_rhs) { return p_lhs < p_rhs;};
    std::cout << std::boolalpha << "l_isLess(30, 50) = " << l_isLess(30, 50) << std::endl;
}

void applyContainer()
{
    std::vector<int> l_container = {1, 2, 3, 5, 8, 11};
    std::for_each(l_container.begin(),
                  l_container.end(),
                  [](const auto p_i){ std::cout << p_i << " ";});
    std::cout << std::endl;

    const auto l_offset = 100;
    std::for_each(l_container.begin(),
                  l_container.end(),
                  [l_offset](auto& p_i){ p_i += l_offset;});
    std::copy(l_container.begin(), l_container.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void useLambda()
{
    storeAsFunction();
    applyContainer();
}

} //namespace cplusplus_lambda

int main()
{
    cplusplus_lambda::useLambda();
    return 0;
}
