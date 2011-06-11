#include "pch.h"

#include "aitest.h"
#include "MockAiManagerRegistry.h"

using namespace ai;

class TestValue : public CalculatedValue<int>
{
public:
    TestValue() : CalculatedValue<int>(NULL, "name", 2), increment(0) {}
    virtual int Calculate() { return ++increment; }

private:
    int increment;
};

class TestManualValue : public ManualSetValue<int>
{
public:
    TestManualValue() : ManualSetValue<int>(NULL, 0, "name") {}
};

class TestValueContext : public NamedObjectContext<UntypedValue>
{
public:
    TestValueContext()
    {
        creators["value"] = &TestValueContext::value;
        creators["manual value"] = &TestValueContext::manual_value;
    }

private:
    static UntypedValue* value(AiManagerRegistry* ai) { return new TestValue(); }
    static UntypedValue* manual_value(AiManagerRegistry* ai) { return new TestManualValue(); }
};

class TestValueAiObjectContext : public AiObjectContext
{
public:
    TestValueAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
    {
        valueContexts.Add(new TestValueContext());
    }
};


class ValueTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( ValueTestCase );
      CPPUNIT_TEST( empty );
      CPPUNIT_TEST( calculate );
      CPPUNIT_TEST( manual );
      CPPUNIT_TEST( fromContext );
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
        CPPUNIT_ASSERT(value == 1);
	}
    
    void calculate()
    {
        TestValue value;

        value.Update();
        CPPUNIT_ASSERT(value == 1);
        
        value.Update();
        CPPUNIT_ASSERT(value == 1);
    
        value.Update();
        CPPUNIT_ASSERT(value == 2);
    
        value.Update();
        CPPUNIT_ASSERT(value == 2);
    }

    void manual()
    {
        TestManualValue value;
        CPPUNIT_ASSERT(value == 0);

        value.Set(3);
        CPPUNIT_ASSERT(value == 3);

        value.Update();
        CPPUNIT_ASSERT(value == 3);
    }

    void fromContext()
    {
        TestValueAiObjectContext context(NULL);
        Value<int> *value = context.GetValue<int>("manual value");
        CPPUNIT_ASSERT(value);

        value->Set(3);
        CPPUNIT_ASSERT(3 == value->Get());

        value = context.GetValue<int>("value");
        context.Update();
        context.Update();
        CPPUNIT_ASSERT(1 == value->Get());
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( ValueTestCase );
