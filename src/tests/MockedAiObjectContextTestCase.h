
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

        assertActions((string(">") + expectedAction).c_str());
    }

    void assertParametrizedCommand(const char* trigger, const char* param)
    {
        ai->buffer.clear();

        context->GetTrigger(trigger)->ExternalEvent(param);
        tick();

        assertActions((string(">") + trigger + "(" + param + ")").c_str());
    }
};
