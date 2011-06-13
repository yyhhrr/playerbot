#include "MockAiObjectContext.h"

using namespace ai;


class MockedAiObjectContextTestCase : public EngineTestBase
{
  
protected:
    MockAiObjectContext* context;


protected:
    void assertCommand(const char* trigger)
    {
        assertCommand(trigger, trigger);
    }

    void assertCommand(const char* trigger, const char* expectedAction)
    {
        ai->buffer.clear();

        context->GetTrigger(trigger)->ExternalEvent("");
        tick();

        assertActions((string(">S:") + expectedAction).c_str());
    }

    void assertParametrizedCommand(const char* trigger, const char* param)
    {
        ai->buffer.clear();

        context->GetTrigger(trigger)->ExternalEvent(param);
        tick();

        assertActions((string(">S:") + trigger + "(" + param + ")").c_str());
    }

    void trigger(const char* name)
    {
        context->GetTrigger(name)->ExternalEvent("");
    }

    void trigger(const char* name, const char* param)
    {
        context->GetTrigger(name)->ExternalEvent(param);
    }

    void tickWithTrigger(const char* name)
    {
        trigger(name);
        tick();
    }
};
