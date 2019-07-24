#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <variant>
#include <list>
#include <iostream>

struct SgnbAdditionRequest {};
struct SgnbReconfigurationComplete {};
struct SgnbReleaseRequest {};
struct UeContextRelease {};
struct SgnbModificationRequest {};

using X2Message = std::variant<SgnbAdditionRequest,
                               SgnbReconfigurationComplete,
                               SgnbReleaseRequest,
                               UeContextRelease,
                               SgnbModificationRequest>;

struct Idle : public boost::msm::front::state<>
{
    struct handleSgnbAdditionRequest
    {
        template <class Fsm, class SourceState, class TargetState>
        void operator()(const SgnbAdditionRequest& p_event, Fsm& p_fsm, SourceState&, TargetState&)
        {
            p_fsm.processEvent(p_event);
        }
    };
    struct handleUnexpectedMessage
    {
        template <class Event, class Fsm, class SourceState, class TargetState>
        void operator()(const Event&, Fsm&, SourceState&, TargetState&)
        {
            std::cout << "unexpected Message\n";
        }
    };
};

struct WaitSgnbReconfComp : public boost::msm::front::state<>
{
    struct handleSgnbReconfComp
    {
        template <class Fsm, class SourceState, class TargetState>
        void operator()(const SgnbReconfigurationComplete& p_event, Fsm& p_fsm, SourceState&, TargetState&)
        {
            p_fsm.processEvent(p_event);
        }
    };
};

struct ScgActive : public boost::msm::front::state<>
{
    struct handleSgnbReleaseRequest
    {
        template <class Fsm, class SourceState, class TargetState>
        void operator()(const SgnbReleaseRequest& p_event, Fsm& p_fsm, SourceState&, TargetState&)
        {
            p_fsm.processEvent(p_event);
        }
    };

    struct handleSgnbModificationRequest
    {
        template <class Fsm, class SourceState, class TargetState>
        void operator()(const SgnbModificationRequest& p_event, Fsm& p_fsm, SourceState&, TargetState&)
        {
            p_fsm.processEvent(p_event);
        }
    };
};

struct WaitUeContextRelease : public boost::msm::front::state<>
{
    struct handleUeContextRelease
    {
        template <class Fsm, class SourceState, class TargetState>
        void operator()(const UeContextRelease& p_event, Fsm& p_fsm, SourceState&, TargetState&)
        {
            p_fsm.processEvent(p_event);
        }
    };
};

struct EndcService : public boost::msm::front::state_machine_def<EndcService>
{
    using initial_state = Idle;

    struct transition_table : boost::mpl::vector<
        //                     Start                 Event                        Target                Action                                             Guard
        boost::msm::front::Row<Idle,                 SgnbAdditionRequest,         WaitSgnbReconfComp,   Idle::handleSgnbAdditionRequest,                   boost::msm::front::none>,
        boost::msm::front::Row<WaitSgnbReconfComp,   SgnbReconfigurationComplete, ScgActive,            WaitSgnbReconfComp::handleSgnbReconfComp,          boost::msm::front::none>,
        boost::msm::front::Row<ScgActive,            SgnbReleaseRequest,          WaitUeContextRelease, ScgActive::handleSgnbReleaseRequest,               boost::msm::front::none>,
        boost::msm::front::Row<ScgActive,            SgnbModificationRequest,     WaitSgnbReconfComp,   ScgActive::handleSgnbModificationRequest,          boost::msm::front::none>,
        boost::msm::front::Row<WaitUeContextRelease, UeContextRelease,            Idle,                 boost::msm::front::none,                           boost::msm::front::none>> {};

    template <class FSM, class Event>
    void no_transition(Event const& p_event, FSM&, int p_state)
    {
        std::cout << "no transition from state " << p_state
                  << " on event " << typeid(p_event).name() << std::endl;
    }

   void processEvent(const SgnbAdditionRequest&)
   {
       std::cout << "process SgnbAdditionRequest\n";
   }
   void processEvent(const SgnbReconfigurationComplete&)
   {
       std::cout << "process SgnbReconfigurationComplete\n";
   }
   void processEvent(const SgnbReleaseRequest&)
   {
       std::cout << "process SgnbReleaseRequest\n";
   }
   void processEvent(const SgnbModificationRequest&)
   {
       std::cout << "process SgnbModificationRequest\n";
   }
   void processEvent(const UeContextRelease&)
   {
       std::cout << "process UeContextRelease\n";
   }
};

class X2MessageVisitor
{
public:
    X2MessageVisitor() { m_endcService.start(); }

    template <typename T>
    void operator()(const T& p_message)
    {
        m_endcService.process_event(p_message);
    }
private:
    boost::msm::back::state_machine<EndcService> m_endcService{};
};

void testEndcService()
{
    std::list<X2Message> l_X2Messages = {
        SgnbAdditionRequest{},
        UeContextRelease{},
        SgnbReconfigurationComplete{},
        SgnbModificationRequest{},
        SgnbReconfigurationComplete{},
        SgnbReleaseRequest{},
        UeContextRelease{},
        UeContextRelease{}};
    X2MessageVisitor l_X2MessageVisitor{};
    for (const auto& l_X2Message : l_X2Messages)
    {
        std::visit(l_X2MessageVisitor, l_X2Message);
    }
}

int main()
{
    testEndcService();
    return 0;
}
