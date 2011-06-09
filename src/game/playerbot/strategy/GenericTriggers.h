#pragma once
#include "Trigger.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : BuffTrigger(ai, spell) {} \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : BuffOnPartyTrigger(ai, spell) {}  \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : DebuffTrigger(ai, spell) {} \
    };

namespace ai
{
	class StatAvailable : public Trigger
	{
	public:
		StatAvailable(AiManagerRegistry* const ai, int amount) : Trigger(ai)
		{
			this->amount = amount;
		}

	protected:
		int amount;
	};

	class RageAvailable : public StatAvailable
    {
    public:
        RageAvailable(AiManagerRegistry* const ai, int amount) : StatAvailable(ai, amount) {}
        virtual bool IsActive();
    };

    class LightRageAvailableTrigger : public RageAvailable
    {
    public:
        LightRageAvailableTrigger(AiManagerRegistry* const ai) : RageAvailable(ai, 20) {}
    };

    class MediumRageAvailableTrigger : public RageAvailable
    {
    public:
        MediumRageAvailableTrigger(AiManagerRegistry* const ai) : RageAvailable(ai, 40) {}
    };

    class HighRageAvailableTrigger : public RageAvailable
    {
    public:
        HighRageAvailableTrigger(AiManagerRegistry* const ai) : RageAvailable(ai, 60) {}
    };

	class EnergyAvailable : public StatAvailable
	{
	public:
		EnergyAvailable(AiManagerRegistry* const ai, int amount) : StatAvailable(ai, amount) {}
		virtual bool IsActive();
	};

    class LightEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        LightEnergyAvailableTrigger(AiManagerRegistry* const ai) : EnergyAvailable(ai, 20) {}
    };

    class MediumEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        MediumEnergyAvailableTrigger(AiManagerRegistry* const ai) : EnergyAvailable(ai, 40) {}
    };

    class HighEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        HighEnergyAvailableTrigger(AiManagerRegistry* const ai) : EnergyAvailable(ai, 60) {}
    };

	class ComboPointsAvailableTrigger : public StatAvailable
	{
	public:
	    ComboPointsAvailableTrigger(AiManagerRegistry* const ai, int amount = 5) : StatAvailable(ai, amount) {}
		virtual bool IsActive();
	};

	class LoseAggroTrigger : public Trigger {
	public:
		LoseAggroTrigger(AiManagerRegistry* const ai) : Trigger(ai, "lose aggro") {}
		virtual bool IsActive();
	};

	class SpellTrigger : public Trigger
	{
	public:
		SpellTrigger(AiManagerRegistry* const ai, const char* spell, int checkInterval = 1) : Trigger(ai, spell, checkInterval)
		{
			this->spell = spell;
		}

		virtual Unit* GetTarget();
		virtual const char* getName() { return spell; }
		virtual bool IsActive();

	protected:
		const char* spell;
	};

	class SpellCanBeCastTrigger : public SpellTrigger
	{
	public:
		SpellCanBeCastTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell) {}
		virtual bool IsActive();
	};

	// TODO: check other targets
    class InterruptSpellTrigger : public SpellTrigger
	{
    public:
        InterruptSpellTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell) {}
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };


    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(AiManagerRegistry* const ai, int amount, float distance = BOT_REACT_DISTANCE) : Trigger(ai)
        {
            this->amount = amount;
            this->distance = distance;
        }
    public:
        virtual bool IsActive()
		{
            return statsManager->GetAttackerCount(distance) >= amount;
        }
        virtual const char* getName() { return "attacker count"; }

    protected:
        int amount;
        float distance;
    };

    class HasAttackersTrigger : public AttackerCountTrigger
    {
    public:
        HasAttackersTrigger(AiManagerRegistry* const ai) : AttackerCountTrigger(ai, 1) {}
    };

    class MyAttackerCountTrigger : public AttackerCountTrigger
    {
    public:
        MyAttackerCountTrigger(AiManagerRegistry* const ai, int amount) : AttackerCountTrigger(ai, amount) {}
    public:
        virtual bool IsActive();
        virtual const char* getName() { return "my attacker count"; }
    };

    class MediumThreatTrigger : public MyAttackerCountTrigger
    {
    public:
        MediumThreatTrigger(AiManagerRegistry* const ai) : MyAttackerCountTrigger(ai, 2) {}
    };

    class AoeTrigger : public AttackerCountTrigger
    {
    public:
        AoeTrigger(AiManagerRegistry* const ai, int amount = 3, float range = 15.0f) : AttackerCountTrigger(ai, amount)
        {
            this->range = range;
        }
    public:
        virtual bool IsActive();
        virtual const char* getName() { return "aoe"; }

    private:
        float range;
    };

    class NoFoodTrigger : public Trigger {
    public:
        NoFoodTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no food trigger") {}
        virtual bool IsActive() { return !ai->GetInventoryManager()->HasFood(); }
    };

    class NoDrinkTrigger : public Trigger {
    public:
        NoDrinkTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no drink trigger") {}
        virtual bool IsActive() { return !ai->GetInventoryManager()->HasDrink(); }
    };

    class LightAoeTrigger : public AoeTrigger
    {
    public:
        LightAoeTrigger(AiManagerRegistry* const ai) : AoeTrigger(ai, 2, 15.0f) {}
    };

    class MediumAoeTrigger : public AoeTrigger
    {
    public:
        MediumAoeTrigger(AiManagerRegistry* const ai) : AoeTrigger(ai, 3, 17.0f) {}
    };

    class HighAoeTrigger : public AoeTrigger
    {
    public:
        HighAoeTrigger(AiManagerRegistry* const ai) : AoeTrigger(ai, 4, 20.0f) {}
    };

    class BuffTrigger : public SpellTrigger
    {
    public:
        BuffTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell, 5) {}
    public:
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };

    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {}
    public:
		virtual Unit* GetTarget();
    };

    BEGIN_TRIGGER(NoAttackersTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(NoTargetTrigger, Trigger)
    END_TRIGGER()

    class DebuffTrigger : public BuffTrigger
    {
    public:
        DebuffTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {
			checkInterval = 1;
		}
    public:
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };

    BEGIN_TRIGGER(LootAvailableTrigger, Trigger)
    END_TRIGGER()


	class BoostTrigger : public BuffTrigger
	{
	public:
		BoostTrigger(AiManagerRegistry* const ai, const char* spell, float balance = 50) : BuffTrigger(ai, spell)
		{
			this->balance = balance;
		}
	public:
		virtual bool IsActive();

	protected:
		float balance;
	};

    class RandomTrigger : public Trigger
    {
    public:
        RandomTrigger(AiManagerRegistry* const ai, int probability = 20) : Trigger(ai)
        {
            this->probability = probability;
        }
    public:
        virtual bool IsActive();
        virtual const char* getName() { return "random"; }

    protected:
        int probability;
    };

    class AndTrigger : public Trigger
    {
    public:
        AndTrigger(AiManagerRegistry* const ai, Trigger* ls, Trigger* rs) : Trigger(ai)
        {
            this->ls = ls;
            this->rs = rs;
        }
        virtual ~AndTrigger()
        {
            delete ls;
            delete rs;
        }
    public:
        virtual bool IsActive();
        virtual const char* getName();

    protected:
        Trigger* ls;
        Trigger* rs;
    };

    class SnareTargetTrigger : public DebuffTrigger
    {
    public:
        SnareTargetTrigger(AiManagerRegistry* const ai, const char* aura) : DebuffTrigger(ai, aura) {}
    public:
        virtual bool IsActive();
        virtual const char* getName() { return "target is moving"; }
    };

	class LowManaTrigger : public Trigger
	{
	public:
		LowManaTrigger(AiManagerRegistry* const ai) : Trigger(ai, "low mana", 5) {}

		virtual bool IsActive();
	};

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
    END_TRIGGER()


	class NoPetTrigger : public Trigger
	{
	public:
		NoPetTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no pet", 5) {}

		virtual bool IsActive() {
			return !targetManager->GetPet() && !ai->GetStatsManager()->IsMounted();
		}
	};

	class ItemCountTrigger : public Trigger {
	public:
		ItemCountTrigger(AiManagerRegistry* const ai, const char* item, int count) : Trigger(ai, item, 5) {
			this->item = item;
			this->count = count;
		}
	public:
		virtual bool IsActive();
		virtual const char* getName() { return "item count"; }

	protected:
		const char* item;
		int count;
	};

	class HasAuraTrigger : public Trigger {
	public:
		HasAuraTrigger(AiManagerRegistry* const ai, const char* spell) : Trigger(ai, spell) {
			this->spell = spell;
		}

		virtual Unit* GetTarget();
		virtual bool IsActive();

	protected:
		const char* spell;
	};

    class TimerTrigger : public Trigger
    {
    public:
        TimerTrigger(AiManagerRegistry* const ai, int checkInterval = 5) : Trigger(ai, "timer", checkInterval) {}

    public:
        virtual bool IsActive() { return true; }
    };

	class TankAoeTrigger : public NoAttackersTrigger
	{
	public:
		TankAoeTrigger(AiManagerRegistry* const ai) : NoAttackersTrigger(ai) {}

	public:
		virtual bool IsActive();

	};

    class IsBehindTargetTrigger : public Trigger
    {
    public:
        IsBehindTargetTrigger(AiManagerRegistry* const ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTargetTrigger : public Trigger
    {
    public:
        HasCcTargetTrigger(AiManagerRegistry* const ai, const char* name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

	class NoMovementTrigger : public Trigger
	{
	public:
		NoMovementTrigger(AiManagerRegistry* const ai, const char* name) : Trigger(ai, name, 5) {}

	public:
		virtual bool IsActive();
	};
}

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"
