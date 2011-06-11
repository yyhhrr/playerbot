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
    MockAction(string *buffer, const char* name) : Action(NULL, name), buffer(buffer)
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
    Trigger* trigger = triggers[name];
    if (trigger)
        return trigger;
    
    return triggers[name] = new MockTrigger(ai);
}

Action* MockAiObjectContext::GetAction(const char* name)
{
    Action* action = actions[name];
    if (action)
        return action;

    return actions[name] = new MockAction(buffer, name);
}
