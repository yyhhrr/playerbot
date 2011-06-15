#include "pch.h"

#include "aitest.h"
#include "MockPlayerbotAIBase.h"

using namespace ai;

class EventTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( EventTestCase );
      CPPUNIT_TEST( emptyEvent );
      CPPUNIT_TEST( eventHandling );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void emptyEvent()
	{
        Event event;
        CPPUNIT_ASSERT(!event);
	}

    void eventHandling()
    {
        Event event("source", "param");

        Event event2 = event;

        CPPUNIT_ASSERT(!!event2);
        CPPUNIT_ASSERT(event2.getParam() == "param");
        CPPUNIT_ASSERT(event2.getSource() == "source");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( EventTestCase );
