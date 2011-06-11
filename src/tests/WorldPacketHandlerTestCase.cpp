#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "MockedAiObjectContextTestCase.h"
#include "../game/playerbot/strategy/ChatCommandHandlerStrategy.h"

using namespace ai;


class WorldPacketHandlerTestCase : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( WorldPacketHandlerTestCase );
  CPPUNIT_TEST( gossip_hello );
  CPPUNIT_TEST( groupInvite );
  CPPUNIT_TEST( groupSetLeader );
  CPPUNIT_TEST( notEnoughMoney );
  CPPUNIT_TEST( notEnoughReputation );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "world packet", NULL);
    }

protected:
 	void gossip_hello()
	{
        assertCommand("gossip hello");
	}
    void groupInvite()
    {
        assertCommand("group invite", "accept invitation");
    }
    void groupSetLeader()
    {
        assertCommand("group set leader", "pass leadership to master");
    }
    void notEnoughMoney()
    {
        assertCommand("not enough money", "tell not enough money");
    }
    void notEnoughReputation()
    {
        assertCommand("not enough reputation", "tell not enough reputation");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( WorldPacketHandlerTestCase );
