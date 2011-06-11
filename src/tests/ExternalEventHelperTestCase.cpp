#include "pch.h"

#include "aitest.h"
#include "MockAiManagerRegistry.h"
#include "../game/playerbot/strategy/ChatCommandTrigger.h"
#include "../game/playerbot/strategy/ExternalEventHelper.h"

using namespace ai;

class ExternalEventTestTriggerContext : public NamedObjectContext<Trigger>
{
public:
    ExternalEventTestTriggerContext()
    {
        creators["message"] = &ExternalEventTestTriggerContext::message;
        creators["message from"] = &ExternalEventTestTriggerContext::message_from;
    }

private:
    static Trigger* message(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "message"); }
    static Trigger* message_from(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "message from"); }
};



class ExternalEventTestAiObjectContext : public AiObjectContext
{
public:
    ExternalEventTestAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
    {
        triggerContexts.Add(new ExternalEventTestTriggerContext());
    }
};


class ExternalEventHelperTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( ExternalEventHelperTestCase );
      CPPUNIT_TEST( externalEvent );
      CPPUNIT_TEST( emptyExternalEvent );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void externalEvent()
	{
        MockAiManagerRegistry ai;
        ExternalEventTestAiObjectContext aiObjectContext(&ai);
        ExternalEventHelper helper(&aiObjectContext);
        
        helper.ParseChatCommand("message from chat");
        
        Event event = aiObjectContext.GetTrigger("message from")->Check();
        CPPUNIT_ASSERT(event);
        CPPUNIT_ASSERT(event.getParam() == "chat");
	
        event = aiObjectContext.GetTrigger("message")->Check();
        CPPUNIT_ASSERT(!event);
    }

    void emptyExternalEvent()
    {
        MockAiManagerRegistry ai;
        ExternalEventTestAiObjectContext aiObjectContext(&ai);
        ExternalEventHelper helper(&aiObjectContext);

        helper.ParseChatCommand("message from");

        Event event = aiObjectContext.GetTrigger("message from")->Check();
        CPPUNIT_ASSERT(event);
        CPPUNIT_ASSERT(event.getParam() == "");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ExternalEventHelperTestCase );
