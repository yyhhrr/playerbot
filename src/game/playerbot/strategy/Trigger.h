#pragma once
#include "Action.h"
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
        Trigger(AiManagerRegistry* const ai, const char* name = NULL, int checkInterval = 1) : AiManagerRegistryAware(ai) {
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
		virtual bool IsActive() = 0;
        virtual NextAction** getHandlers() { return NULL; }
        virtual const char* getName() { return name ? name : "trigger"; }
		
		bool needCheck() {
			if (++ticksElapsed >= checkInterval) {
				ticksElapsed = 0;
				return true;
			}
			return false;
		}

    protected:
        const char* name;
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
            if (trigger) delete trigger; 
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
