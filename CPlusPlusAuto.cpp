#include <iostream>
#include <type_traits>
#include <vector>

namespace cplusplus_auto
{
void print(int p_i)
{
    std::cout << "This integral value is "<< p_i << std::endl;
}

void print(float p_f)
{
    std::cout << "This float value is "<< p_f << std::endl;
}

void print(const std::vector<int>::iterator& p_iter)
{
    std::cout << "The content value in this iterator is "<< *p_iter << std::endl;
}

void deduceVariantType()
{
    auto l_auto1 = 3;
    print(l_auto1);

    auto l_auto2 = 3.1f;
    print(l_auto2);

    std::vector<int> l_container = {1, 2, 3, 5, 8, 11};
    std::vector<int>::iterator l_iter = l_container.begin();
    print(l_iter);
    auto l_auto3 = std::next(l_iter, 2);
    print(l_auto3);
}

} //namespace cplusplus_auto

int main()
{
    cplusplus_auto::deduceVariantType();
    return 0;
}
