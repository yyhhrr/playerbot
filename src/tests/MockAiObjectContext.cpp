#include "pch.h"
#include "aitest.h"
#include "MockAiObjectContext.h"

using namespace std;
using namespace ai;

class MockTrigger : public Trigger
{
public:
    MockTrigger(AiManagerRegistry* const ai) : Trigger(ai)
    {
    }

public:
    virtual Event Check()
    {
        return event;
    }

    virtual void ExternalEvent(string param)
    {
        this->event = Event("mock", param);
    }

private:
    Event event;
};

class MockAction : public Action
{
public:
    MockAction(AiManagerRegistry* const ai, string *buffer, const char* name) : Action(ai, name), buffer(buffer)
    {

    }

    virtual bool Execute(Event event)
    {
        buffer->append(">");
        buffer->append(getName());
        if (event.getParam().empty())
            return true;

        buffer->append("(");
        buffer->append(event.getParam());
        buffer->append(")");
        return true;
    }

    virtual bool ExecuteResult()
    {
        buffer->append(getName());
        return true;
    }

private:
    string *buffer;
};

MockAiObjectContext::MockAiObjectContext(AiManagerRegistry* const ai, AiObjectContext *realContext, string *buffer) : 
    AiObjectContext(ai), buffer(buffer), realContext(realContext)
{
}

Strategy* MockAiObjectContext::GetStrategy(const char* name)
{
    return realContext->GetStrategy(name);
}

Trigger* MockAiObjectContext::GetTrigger(const char* name)
{
    if (!realContext->GetTrigger(name))
        CPPUNIT_ASSERT(false);

    Trigger* trigger = triggers[name];
    if (trigger)
        return trigger;
    
    return triggers[name] = new MockTrigger(ai);
}

Action* MockAiObjectContext::GetAction(const char* name)
{
    CPPUNIT_ASSERT(realContext->GetAction(name) != NULL);

    Action* action = actions[name];
    if (action)
        return action;

    return actions[name] = new MockAction(ai, buffer, name);
}
