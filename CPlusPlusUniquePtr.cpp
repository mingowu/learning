#include <iostream>
#include <memory>

namespace cplusplus_unique_ptr
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

void processByRawPointer()
{
    MessageHandler* l_messageHandler = new MessageHandler();
    l_messageHandler->handle();
    delete l_messageHandler;
}

void processByUniquePointer()
{
    auto l_messageHandler = std::make_unique<MessageHandler>();
    l_messageHandler->handle();
}

void process()
{
    processByRawPointer();
    processByUniquePointer();
}

} //namespace cplusplus_unique_ptr

int main()
{
    cplusplus_unique_ptr::process();
    return 0;
}
