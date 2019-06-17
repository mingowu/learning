#include <iostream>
#include <memory>

namespace cplusplus_shared_ptr
{
class MessageHandler
{
public:
    MessageHandler()
    {
        std::cout << "MessageHandler::MessageHandler()\n";
    }
    ~MessageHandler()
    {
        std::cout << "MessageHandler::~MessageHandler()\n";
    }
    void handle() const
    {
    }
};

void processByUniquePointer()
{
    auto l_messageHandler = std::make_unique<MessageHandler>();
    l_messageHandler->handle();
}

void processBySharedPointer()
{
    auto l_messageHandler1 = std::make_shared<MessageHandler>();
    l_messageHandler1->handle();
    std::cout << "use_count : " << l_messageHandler1.use_count() << std::endl;

    auto l_messageHandler2 = l_messageHandler1;
    l_messageHandler2->handle();
    std::cout << "use_count : " << l_messageHandler2.use_count() << std::endl;
}

void process()
{
    processByUniquePointer();
    processBySharedPointer();
}

} //namespace cplusplus_shared_ptr

int main()
{
    cplusplus_shared_ptr::process();
    return 0;
}
