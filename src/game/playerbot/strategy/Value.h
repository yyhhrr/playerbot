#pragma once
#include "Action.h"
#include "Event.h"
#include "../ai/AiManagerRegistryAware.h"

namespace ai
{
    class UntypedValue : public AiManagerRegistryAware
    {
    public:
        UntypedValue(AiManagerRegistry* const ai) : AiManagerRegistryAware(ai) {}
        virtual void Update() {}
    };

    template<class T>
    class Value : public UntypedValue
	{
	public:
        Value(AiManagerRegistry* const ai, const char* name = "value", int checkInterval = 1) : UntypedValue(ai),
            name(name), checkInterval(checkInterval), ticksElapsed(0), calculated(false) 
        { }
        virtual ~Value() {}

	public:
        virtual const char* getName() { return name.c_str(); }
        T Get()
        {
            if (ticksElapsed >= checkInterval) {
                ticksElapsed = 0;
                value = Calculate();
                calculated = true;
            }
            return value; 
        }
        void Set(T value) { this->value = value; calculated = true; }
        virtual void Update()
        {
            if (ticksElapsed < checkInterval) {
                ticksElapsed++;
            }
        }
        void Reset() { calculated = false; }
        bool operator! () const { return !calculated; }
        operator T() { return Get(); }

    protected:
        virtual T Calculate() = NULL;

    protected:
        bool calculated;
        string name;
		int checkInterval;
		int ticksElapsed;
        T value;
	};
}
