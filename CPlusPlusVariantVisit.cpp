#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

namespace cplusplus_variant_visit
{
namespace cplusplus_variant_visit_lambda
{
void visitVariant()
{
    using var_t = std::variant<int, long, double, std::string>;
    std::vector<var_t> l_varts = {10, 15l, 1.5, "control plane", 99};
    for (const auto& l_var : l_varts)
    {
        std::visit([](const auto& p_var){std::cout << p_var << std::endl;}, l_var);
    }
    // std::for_each(l_varts.begin(),
                  // l_varts.end(),
                  // [](const auto p_var)
                  // {
                      // std::visit([](const auto& p_var){std::cout << p_var << std::endl;}, p_var);
                  // });
}
}// namespace cplusplus_variant_visit_lambda

namespace cplusplus_variant_visit_functor
{
struct RRCSetupRequest           { int ueInstanceId; };
struct RRCResumeRequest          { int ueInstanceId; };
struct RRCReestablishmentRequest { int ueInstanceId; };
struct RRCSystemInfoRequest      { int ueInstanceId; };

using UlCcchMessage = std::variant<RRCSetupRequest,
                                   RRCResumeRequest,
                                   RRCReestablishmentRequest,
                                   RRCSystemInfoRequest>;

class UlCcchMessageHandler
{
public:
    void process(const RRCSetupRequest& p_rrcSetupRequest)
    {
        std::cout << "process RRCSetupRequest with ueInstanceId = "
                  << p_rrcSetupRequest.ueInstanceId << std::endl;
    }
    void process(const RRCResumeRequest& p_rrcResumeRequest)
    {
        std::cout << "process RRCResumeRequest with ueInstanceId = "
                  << p_rrcResumeRequest.ueInstanceId << std::endl;
    }
    void process(const RRCReestablishmentRequest& p_rrcReestablishmentRequest)
    {
        std::cout << "process RRCReestablishmentRequest with ueInstanceId = "
                  << p_rrcReestablishmentRequest.ueInstanceId << std::endl;
    }
    void process(const RRCSystemInfoRequest& p_rrcSystemInfoRequest)
    {
        std::cout << "process RRCSystemInfoRequest with ueInstanceId = "
                  << p_rrcSystemInfoRequest.ueInstanceId << std::endl;
    }
};

class MessageVisitor
{
public:
    template <typename T>
    void operator()(const T& p_message)
    {
        m_ulCcchMessageHandler.process(p_message);
    }
public:
    UlCcchMessageHandler m_ulCcchMessageHandler{};
};

void visitVariant()
{
    std::list<UlCcchMessage> l_ulCcchMessages = {
        RRCSetupRequest{1},
        RRCResumeRequest{2},
        RRCReestablishmentRequest{3},
        RRCSystemInfoRequest{5},
        RRCResumeRequest{8}};
    MessageVisitor l_messageVisitor{};
    for (const auto& l_ulCcchMessage : l_ulCcchMessages)
    {
        std::visit(l_messageVisitor, l_ulCcchMessage);
    }
}
}// namespace cplusplus_variant_visit_functor

void visitVariant()
{
    cplusplus_variant_visit_lambda::visitVariant();
    cplusplus_variant_visit_functor::visitVariant();
}

} //namespace cplusplus_variant_visit

int main()
{
    cplusplus_variant_visit::visitVariant();
    return 0;
}
