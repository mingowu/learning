#include <iostream>
#include <variant>
#include <vector>
#include <string>

namespace cplusplus_variant
{
void getVariant()
{
    using var_t = std::variant<int, long, double, std::string>;
    std::vector<var_t> l_varts = {10, 15l, 1.5, "control plane", 99};
    for (const auto& l_var : l_varts)
    {
        if (std::get_if<int>(&l_var) not_eq nullptr)
        {
            std::cout << std::get<int>(l_var) * 2 << std::endl;
        }
        else if (std::get_if<long>(&l_var) not_eq nullptr)
        {
            std::cout << std::get<long>(l_var) * 3 << std::endl;
        }
        else if (std::get_if<double>(&l_var) not_eq nullptr)
        {
            std::cout << std::get<double>(l_var) * 4.5 << std::endl;
        }
        else if (std::get_if<std::string>(&l_var) not_eq nullptr)
        {
            std::cout << "Hello, " + std::get<std::string>(l_var) << std::endl;
        }
    }
}

} //namespace cplusplus_variant

int main()
{
    cplusplus_variant::getVariant();
    return 0;
}
