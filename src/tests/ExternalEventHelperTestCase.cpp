#include "pch.h"

#include "aitest.h"
#include "MockAiManagerRegistry.h"
#include "../game/playerbot/strategy/ChatCommandTrigger.h"
#include "../game/playerbot/strategy/ExternalEventHelper.h"

using namespace ai;



class ExternalEventTestActionFactory : public ActionFactory
{
public:
    ExternalEventTestActionFactory(AiManagerRegistry* const ai) : 
      ActionFactory(ai), message(ai, "message"), message_from(ai, "message from") {}
    
    virtual Trigger* createTrigger(const char* name)
    {
        if (!strcmp("message", name))
            return &message;

        if (!strcmp("message from", name))
            return &message_from;

        return NULL;
    }
private:
    ChatCommandTrigger message;
    ChatCommandTrigger message_from;
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
        ExternalEventTestActionFactory actionFactory(&ai);
        ExternalEventHelper helper(&actionFactory);
        
        helper.ParseChatCommand("message from chat");
        
        Event event = actionFactory.createTrigger("message from")->Check();
        CPPUNIT_ASSERT(event);
        CPPUNIT_ASSERT(event.getParam() == "chat");
	
        event = actionFactory.createTrigger("message")->Check();
        CPPUNIT_ASSERT(!event);
    }

    void emptyExternalEvent()
    {
        MockAiManagerRegistry ai;
        ExternalEventTestActionFactory actionFactory(&ai);
        ExternalEventHelper helper(&actionFactory);

        helper.ParseChatCommand("message from");

        Event event = actionFactory.createTrigger("message from")->Check();
        CPPUNIT_ASSERT(event);
        CPPUNIT_ASSERT(event.getParam() == "");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ExternalEventHelperTestCase );
