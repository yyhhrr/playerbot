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
    class Value
    {
    public:
        virtual const char* getName() = NULL;
        virtual T Get() = NULL;
        virtual void Set(T value) = NULL;
        operator T() { return Get(); }
    };
    
    template<class T>
    class CalculatedValue : public UntypedValue, public Value<T>
	{
	public:
        CalculatedValue(AiManagerRegistry* const ai, T defaultValue, const char* name = "value", int checkInterval = 1) : UntypedValue(ai),
            name(name), checkInterval(checkInterval), ticksElapsed(0), value(defaultValue) 
        { }
        virtual ~CalculatedValue() {}

	public:
        virtual const char* getName() { return name.c_str(); }
        virtual T Get()
        {
            if (ticksElapsed >= checkInterval) {
                ticksElapsed = 0;
                value = Calculate();
            }
            return value; 
        }
        virtual void Set(T value) { this->value = value; }
        virtual void Update()
        {
            if (ticksElapsed < checkInterval) {
                ticksElapsed++;
            }
        }

    protected:
        virtual T Calculate() = NULL;

    protected:
        string name;
		int checkInterval;
		int ticksElapsed;
        T value;
	};

    template<class T>
    class ManualSetValue : public UntypedValue, public Value<T>
    {
    public:
        ManualSetValue(AiManagerRegistry* const ai, T defaultValue, const char* name = "value") : 
            UntypedValue(ai), name(name), value(defaultValue) {}
        virtual ~ManualSetValue() {}

    public:
        virtual const char* getName() { return name.c_str(); }
        virtual T Get() { return value; }
        virtual void Set(T value) { this->value = value; }
        virtual void Update() { }

    protected:
        string name;
        T value;
    };
}
