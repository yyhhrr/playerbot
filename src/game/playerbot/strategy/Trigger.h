#pragma once
#include "Action.h"
#include "Event.h"
#include "../ai/AiManagerRegistryAware.h"

#define NEXT_TRIGGERS(name, relevance) \
    virtual NextAction* getNextAction() { return new NextAction(name, relevance); }

#define BEGIN_TRIGGER(clazz, super) \
class clazz : public super \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : super(ai) {} \
    public: \
        virtual bool IsActive();

#define END_TRIGGER() \
    };

namespace ai
{
    class Trigger : public AiManagerRegistryAware
	{
	public:
        Trigger(AiManagerRegistry* const ai, const char* name = "trigger", int checkInterval = 1) : AiManagerRegistryAware(ai) {
            this->name = name;
			this->checkInterval = checkInterval;
			ticksElapsed = 0;
			this->spellManager = ai->GetSpellManager();
			this->targetManager = ai->GetTargetManager();
			this->statsManager = ai->GetStatsManager();
			this->moveManager = ai->GetMoveManager();
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
		AiSpellManager* spellManager;
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
		AiMoveManager* moveManager;
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
