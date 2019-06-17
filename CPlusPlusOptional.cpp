#include <iostream>
#include <optional>

namespace cplusplus_optional
{
struct RadioBearerConfig {};
struct LatenonCriticalExtension {};

struct RRCSetupIEs
{
    RadioBearerConfig radioBearerConfig;
    std::optional<LatenonCriticalExtension> latenonCriticalExtension;
};

struct RRCSetup
{
    int rrcTransactionIdentifier;
    RRCSetupIEs rrcSetup;
};

void checkIfLatenonCriticalExtensionAvailable(const std::optional<LatenonCriticalExtension>& p_latenonCriticalExtension)
{
    if (not p_latenonCriticalExtension)
    {
        std::cout << "latenonCriticalExtension is empty\n";
    }
    else
    {
        std::cout << "latenonCriticalExtension is available\n";
    }
}

void buildLatenonCriticalExtension(std::optional<LatenonCriticalExtension>& p_latenonCriticalExtension)
{
    p_latenonCriticalExtension = std::make_optional<LatenonCriticalExtension>();
}

void generateRRCSetup()
{
    RRCSetup l_rrcSetup{};
    checkIfLatenonCriticalExtensionAvailable(l_rrcSetup.rrcSetup.latenonCriticalExtension);
    buildLatenonCriticalExtension(l_rrcSetup.rrcSetup.latenonCriticalExtension);
    checkIfLatenonCriticalExtensionAvailable(l_rrcSetup.rrcSetup.latenonCriticalExtension);
}

} //namespace cplusplus_optional

int main()
{
    cplusplus_optional::generateRRCSetup();
    return 0;
}
