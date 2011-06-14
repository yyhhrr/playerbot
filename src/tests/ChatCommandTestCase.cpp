#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "MockedAiObjectContextTestCase.h"
#include "../game/playerbot/strategy/ChatCommandHandlerStrategy.h"

using namespace ai;


class ChatCommandTestCase : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( ChatCommandTestCase );
      CPPUNIT_TEST( stats );
      CPPUNIT_TEST( leave );
      CPPUNIT_TEST( quests );
      CPPUNIT_TEST( reputation );
      CPPUNIT_TEST( log );
      CPPUNIT_TEST( los );
      CPPUNIT_TEST( drop );
      CPPUNIT_TEST( query );
      CPPUNIT_TEST( ll );
      CPPUNIT_TEST( loot_all );
      CPPUNIT_TEST( release );
      CPPUNIT_TEST( teleport );
      CPPUNIT_TEST( taxi );
      CPPUNIT_TEST( repair );
      CPPUNIT_TEST( use );
      CPPUNIT_TEST( item_count );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "chat", NULL);
    }

protected:
 	void stats()
	{
        assertCommand("stats");
	}

    void leave()
    {
        assertCommand("leave");
    }

    void reputation()
    {
        assertCommand("rep", "reputation");
        assertCommand("reputation");
    }

    void quests()
    {
        assertCommand("quests");
        assertParametrizedCommand("quests", "summary");
        assertParametrizedCommand("quests", "completed");
        assertParametrizedCommand("quests", "incompleted");
    }

    void log()
    {
        assertCommand("log");
        assertParametrizedCommand("log", "debug");
    }

    void los()
    {
        assertCommand("los");
        assertParametrizedCommand("los", "targets");
        assertParametrizedCommand("los", "npcs");
        assertParametrizedCommand("los", "gos");
        assertParametrizedCommand("los", "game objects");
        assertParametrizedCommand("los", "corpses");
    }

    void drop()
    {
        assertCommand("drop");
    }

    void query()
    {
        trigger("q");
        tick();
        tick();
        tick();

        assertActions(">S:query quest>S:query quest item>S:query item usage");
    }

    void ll()
    {
        assertCommand("ll");
        assertParametrizedCommand("ll", "?");
        assertParametrizedCommand("ll", "[item]");
        assertParametrizedCommand("ll", "-[item]");
        assertParametrizedCommand("ll", "all");
    }

    void loot_all()
    {
        trigger("add all loot");
        tick();
        tick();

        assertActions(">S:add all loot>S:loot");
    }

    void release()
    {
        assertCommand("release");
    }
    
    void teleport()
    {
        assertCommand("teleport");
    }

    void taxi()
    {
        assertCommand("taxi");
    }

    void repair()
    {
        assertCommand("repair");
    }

    void use()
    {
        trigger("u");
        tick();

        assertActions(">S:use");
    }

    void item_count()
    {
        trigger("c");
        tick();

        assertActions(">S:item count");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ChatCommandTestCase );
