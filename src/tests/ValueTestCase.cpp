#include "pch.h"

#include "aitest.h"
#include "MockAiManagerRegistry.h"

using namespace ai;

class TestValue : public Value<int>
{
public:
    TestValue() : Value<int>(NULL, "name", 2), increment(0) {}
    virtual int Calculate() { return ++increment; }

private:
    int increment;
};

class ValueTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( ValueTestCase );
      CPPUNIT_TEST( empty );
      CPPUNIT_TEST( calculate );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
    void empty()
	{
        TestValue value;
        CPPUNIT_ASSERT(!value);
	}
    
    void calculate()
    {
        TestValue value;

        value.Update();
        CPPUNIT_ASSERT(!value);
        
        value.Update();
        CPPUNIT_ASSERT(value == 1);
    
        value.Update();
        CPPUNIT_ASSERT(value == 1);
    
        value.Update();
        CPPUNIT_ASSERT(value == 2);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ValueTestCase );
