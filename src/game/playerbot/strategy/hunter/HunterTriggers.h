#pragma once

#include "../GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheHawkTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "aspect of the hawk") {
			checkInterval = 1;
		}
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !spellManager->HasAura("aspect of the viper", GetTarget());
        };
    };

	class HunterAspectOfTheWildTrigger : public BuffTrigger
	{ 
	public: 
		HunterAspectOfTheWildTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "aspect of the wild") {
			checkInterval = 1;
		}
		virtual bool IsActive() {
			return BuffTrigger::IsActive() && !spellManager->HasAura("aspect of the viper", GetTarget());
		};
	};

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheViperTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "aspect of the viper") {}
        virtual bool IsActive() 
		{
			Unit* target = GetTarget();
            return !spellManager->HasAura(spell, target) && 
				spellManager->CanCastSpell(spell, target) && 
				AI_VALUE2(uint8, "mana", "self target") < 50; 
        };
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfThePackTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "aspect of the pack") {}
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !spellManager->HasAura("aspect of the cheetah", GetTarget());
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

    class BlackArrowTrigger : public DebuffTrigger
    { 
    public: 
        BlackArrowTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "black arrow") {}
    };

    class HuntersMarkTrigger : public DebuffTrigger
    { 
    public: 
        HuntersMarkTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "hunter's mark") {}
    };
    
    class FreezingTrapTrigger : public HasCcTargetTrigger
    { 
    public: 
        FreezingTrapTrigger(AiManagerRegistry* const ai) : HasCcTargetTrigger(ai, "freezing trap") {}
    };

    class RapidFireTrigger : public BoostTrigger
    { 
    public: 
        RapidFireTrigger(AiManagerRegistry* const ai) : BoostTrigger(ai, "rapid fire") {}
    };
    
}