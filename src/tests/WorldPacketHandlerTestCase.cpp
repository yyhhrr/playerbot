#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "MockedAiObjectContextTestCase.h"
#include "../game/playerbot/strategy/ChatCommandHandlerStrategy.h"

using namespace ai;


class WorldPacketHandlerTestCase : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( WorldPacketHandlerTestCase );
      CPPUNIT_TEST( groupInvite );
      CPPUNIT_TEST( groupSetLeader );
      CPPUNIT_TEST( notEnoughMoney );
      CPPUNIT_TEST( notEnoughReputation );
      CPPUNIT_TEST( turn_in_quest );
      CPPUNIT_TEST( accept_quest );
      CPPUNIT_TEST( quest_share );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "world packet", NULL);
    }

protected:
    void groupInvite()
    {
        trigger("group invite");
        tick();

        assertActions(">S:accept invitation");
    }
    void groupSetLeader()
    {
        trigger("group set leader");
        tick();

        assertActions(">S:pass leadership to master");
    }
    void notEnoughMoney()
    {
        trigger("not enough money");
        tick();
        assertActions(">S:tell not enough money");
    }
    void notEnoughReputation()
    {
        trigger("not enough reputation");
        tick();
        assertActions(">S:tell not enough reputation");
    }

    void turn_in_quest()
    {
        trigger("use game object");
        tick();

        trigger("complete quest");
        tick();

        trigger("gossip hello");
        tick();
        tick();

        assertActions(">S:turn in quest>S:turn in quest>S:turn in quest>S:gossip hello");
    }

    void accept_quest()
    {
        trigger("accept quest");
        tick();

        assertActions(">S:accept quest");
    }

    void quest_share()
    {
        trigger("quest share");
        tick();

        assertActions(">S:accept quest share");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( WorldPacketHandlerTestCase );
