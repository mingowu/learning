#include <iostream>
#include <string>
#include <memory>

namespace cplusplus_rvalue_reference
{
namespace cplusplus_rvalue_reference_x
{
class X
{
public:
    X()
    {
        std::cout << "X::X()\n";
    }
    X(const X&)
    {
        std::cout << "X::X(const X&)\n";
    }
    X(const X&&)
    {
        std::cout << "X::X(const X&&)\n";
    }
    X& operator=(const X&)
    {
        std::cout << "X::operator=(const X&)\n";
        return *this;
    }
    X& operator=(const X&&)
    {
        std::cout << "X::operator=(const X&&)\n";
        return *this;
    }
    ~X()
    {
        std::cout << "X::~X()\n";
    }
    void doSomething() const
    {}
};

X createX()
{
    const auto l_x = X{};
    std::cout << "createX." << std::endl;
    return l_x;
}

void constructByCreateX()
{
    const X l_createdX = createX();
    l_createdX.doSomething();
}

void constructByMove()
{
    X l_x{};
    auto l_movedX = std::move(l_x);
    l_movedX.doSomething();
}

void useRvalueReference()
{
    constructByCreateX();
    constructByMove();
}
} //namespace cplusplus_rvalue_reference_x

namespace cplusplus_rvalue_reference_service
{
class RRCSetupRequestProcedure {};
class RRCSetupProcedure {};
class RRCSetupCompleteProcedure {};

class SrbSetupService
{
public:
    SrbSetupService(const RRCSetupRequestProcedure p_rrcSetupRequestProcedure,
                    const RRCSetupProcedure p_rrcSetupProcedure,
                    const RRCSetupCompleteProcedure p_rrcSetupCompleteProcedure)
        : m_rrcSetupRequestProcedure(std::move(p_rrcSetupRequestProcedure)),
          m_rrcSetupProcedure(std::move(p_rrcSetupProcedure)),
          m_rrcSetupCompleteProcedure(std::move(p_rrcSetupCompleteProcedure))
    {}

    void start()
    {}
private:
    RRCSetupRequestProcedure m_rrcSetupRequestProcedure;
    RRCSetupProcedure m_rrcSetupProcedure;
    RRCSetupCompleteProcedure m_rrcSetupCompleteProcedure;
};

void constructServiceByCopied()
{
    RRCSetupRequestProcedure l_rrcSetupRequestProcedure{};
    RRCSetupProcedure l_rrcSetupProcedure{};
    RRCSetupCompleteProcedure l_rrcSetupCompleteProcedure{};

    SrbSetupService l_srbSetupService{l_rrcSetupRequestProcedure,
                                      l_rrcSetupProcedure,
                                      l_rrcSetupCompleteProcedure};
    l_srbSetupService.start();
}

void constructServiceByMoved()
{
    RRCSetupRequestProcedure l_rrcSetupRequestProcedure{};
    RRCSetupProcedure l_rrcSetupProcedure{};
    RRCSetupCompleteProcedure l_rrcSetupCompleteProcedure{};

    SrbSetupService l_srbSetupService{std::move(l_rrcSetupRequestProcedure),
                                      std::move(l_rrcSetupProcedure),
                                      std::move(l_rrcSetupCompleteProcedure)};
    l_srbSetupService.start();
}

void useRvalueReference()
{
    constructServiceByCopied();
    constructServiceByMoved();
}
} //namespace cplusplus_rvalue_reference_service
} //namespace cplusplus_rvalue_reference

int main()
{
    cplusplus_rvalue_reference::cplusplus_rvalue_reference_x::useRvalueReference();
    cplusplus_rvalue_reference::cplusplus_rvalue_reference_service::useRvalueReference();
    return 0;
}
