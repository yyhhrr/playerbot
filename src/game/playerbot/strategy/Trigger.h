#pragma once
#include "Action.h"
#include "Event.h"
#include "../PlayerbotAIAware.h"

#define NEXT_TRIGGERS(name, relevance) \
    virtual NextAction* getNextAction() { return new NextAction(name, relevance); }

#define BEGIN_TRIGGER(clazz, super) \
class clazz : public super \
    { \
    public: \
        clazz(PlayerbotAI* ai) : super(ai) {} \
    public: \
        virtual bool IsActive();

#define END_TRIGGER() \
    };

namespace ai
{
    class Trigger : public PlayerbotAIAware
	{
	public:
        Trigger(PlayerbotAI* ai, const char* name = "trigger", int checkInterval = 1) : PlayerbotAIAware(ai) {
            this->name = name;
			this->checkInterval = checkInterval;
			ticksElapsed = 0;
        }
        virtual ~Trigger() {}

	public:
        virtual Event Check();
        virtual void ExternalEvent(string param) {}
        virtual void ExternalEvent(WorldPacket &packet) {}
        virtual bool IsActive() { return false; }
        virtual NextAction** getHandlers() { return NULL; }
        virtual const char* getName() { return name.c_str(); }
        void Update() {}
        virtual Unit* GetTarget();
        virtual Value<Unit*>* GetTargetValue();
        virtual const char* GetTargetName() { return "self target"; }

		bool needCheck() {
			if (++ticksElapsed >= checkInterval) {
				ticksElapsed = 0;
				return true;
			}
			return false;
		}

    protected:
        string name;
		int checkInterval;
		int ticksElapsed;
	};


    class TriggerNode
    {
    public:
        TriggerNode(const char* name, NextAction** handlers = NULL)
        {
            this->name = name; 
            this->handlers = handlers;
            this->trigger = NULL;
        }
        virtual ~TriggerNode() 
        { 
            NextAction::destroy(handlers); 
        }

    public:
        Trigger* getTrigger() { return trigger; }
        void setTrigger(Trigger* trigger) { this->trigger = trigger; }
        const char* getName() { return name.c_str(); }

    public:
        NextAction** getHandlers() { return NextAction::merge(NextAction::clone(handlers), trigger->getHandlers()); }

    private:
        Trigger* trigger;
        NextAction** handlers;
        std::string name;
    };
}
