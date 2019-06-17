#include <iostream>

namespace cplusplus_decltype
{
namespace cplusplus_decltype_expression
{
void print(int p_i)
{
    std::cout << "This integral value is "<< p_i << std::endl;
}

void print(float p_f)
{
    std::cout << "This float value is "<< p_f << std::endl;
}

void deduceVariantFromExpression()
{
    auto l_auto1 = 3;
    print(l_auto1);

    decltype(l_auto1) l_auto2 = l_auto1 * 2 + 100;
    print(l_auto2);

    decltype(l_auto1 + l_auto2) l_auto3 = l_auto1 * 3 + l_auto2 * 4;
    print(l_auto3);
}
} //namespace cplusplus_decltype_expression

namespace cplusplus_decltype_template
{
struct RRCRej {};
struct RRCSetup {};

class RRCRejFactory
{
public:
    RRCRej create() const
    {
        std::cout << "an RRCRej Message will be created in RRCRejFactory" << std::endl;
        return RRCRej{};
    }
};

class RRCSetupFactory
{
public:
    RRCSetup create() const
    {
        std::cout << "an RRCSetup Message will be created in RRCSetupFactory" << std::endl;
        return RRCSetup{};
    }
};

template<typename Factory>
auto createDlCcchMessage(const Factory& p_factory) -> decltype(p_factory.create())
{
    return p_factory.create();
}

void process()
{
    createDlCcchMessage(RRCRejFactory{});
    createDlCcchMessage(RRCSetupFactory{});
}

} //namespace cplusplus_decltype_template
} //namespace cplusplus_decltype

int main()
{
    cplusplus_decltype::cplusplus_decltype_expression::deduceVariantFromExpression();
    cplusplus_decltype::cplusplus_decltype_template::process();
    return 0;
}
