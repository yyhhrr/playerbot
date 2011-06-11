#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageActions.h"
#include "MageAiObjectContext.h"
#include "FrostMageStrategy.h"
#include "GenericMageNonCombatStrategy.h"
#include "FireMageStrategy.h"
#include "../PullStrategy.h"
#include "MageTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["frost"] = &mage::StrategyFactoryInternal::frost;
                creators["fire"] = &mage::StrategyFactoryInternal::fire;
                creators["nc"] = &mage::StrategyFactoryInternal::nc;
                creators["pull"] = &mage::StrategyFactoryInternal::pull;
            }

        private:
            static Strategy* frost(AiManagerRegistry* ai) { return new FrostMageStrategy(ai); }
            static Strategy* fire(AiManagerRegistry* ai) { return new FireMageStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericMageNonCombatStrategy(ai); }
            static Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["fireball"] = &TriggerFactoryInternal::fireball;
                creators["pyroblast"] = &TriggerFactoryInternal::pyroblast;
                creators["combustion"] = &TriggerFactoryInternal::combustion;
                creators["icy veins"] = &TriggerFactoryInternal::icy_veins;
                creators["arcane intellect"] = &TriggerFactoryInternal::arcane_intellect;
                creators["arcane intellect on party"] = &TriggerFactoryInternal::arcane_intellect_on_party;
                creators["mage armor"] = &TriggerFactoryInternal::mage_armor;
                creators["remove curse"] = &TriggerFactoryInternal::remove_curse;
                creators["remove curse on party"] = &TriggerFactoryInternal::remove_curse_on_party;
                creators["counterspell"] = &TriggerFactoryInternal::counterspell;
                creators["polymorph"] = &TriggerFactoryInternal::polymorph;
                creators["spellsteal"] = &TriggerFactoryInternal::spellsteal;
                
            }

        private:
            static Trigger* fireball(AiManagerRegistry* ai) { return new FireballTrigger(ai); }
            static Trigger* pyroblast(AiManagerRegistry* ai) { return new PyroblastTrigger(ai); }
            static Trigger* combustion(AiManagerRegistry* ai) { return new CombustionTrigger(ai); }
            static Trigger* icy_veins(AiManagerRegistry* ai) { return new IcyVeinsTrigger(ai); }
            static Trigger* arcane_intellect(AiManagerRegistry* ai) { return new ArcaneIntellectTrigger(ai); }
            static Trigger* arcane_intellect_on_party(AiManagerRegistry* ai) { return new ArcaneIntellectOnPartyTrigger(ai); }
            static Trigger* mage_armor(AiManagerRegistry* ai) { return new MageArmorTrigger(ai); }
            static Trigger* remove_curse(AiManagerRegistry* ai) { return new RemoveCurseTrigger(ai); }
            static Trigger* remove_curse_on_party(AiManagerRegistry* ai) { return new PartyMemberRemoveCurseTrigger(ai); }
            static Trigger* counterspell(AiManagerRegistry* ai) { return new CounterspellInterruptSpellTrigger(ai); }
            static Trigger* polymorph(AiManagerRegistry* ai) { return new PolymorphTrigger(ai); }
            static Trigger* spellsteal(AiManagerRegistry* ai) { return new SpellstealTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["frostbolt"] = &AiObjectContextInternal::frostbolt;
                creators["blizzard"] = &AiObjectContextInternal::blizzard;
                creators["frost nova"] = &AiObjectContextInternal::frost_nova;
                creators["arcane intellect"] = &AiObjectContextInternal::arcane_intellect;
                creators["arcane intellect on party"] = &AiObjectContextInternal::arcane_intellect_on_party;
                creators["conjure water"] = &AiObjectContextInternal::conjure_water;
                creators["conjure food"] = &AiObjectContextInternal::conjure_food;
                creators["mage armor"] = &AiObjectContextInternal::mage_armor;
                creators["ice armor"] = &AiObjectContextInternal::ice_armor;
                creators["frost armor"] = &AiObjectContextInternal::frost_armor;
                creators["fireball"] = &AiObjectContextInternal::fireball;
                creators["pyroblast"] = &AiObjectContextInternal::pyroblast;
                creators["flamestrike"] = &AiObjectContextInternal::flamestrike;
                creators["fire blast"] = &AiObjectContextInternal::fire_blast;
                creators["scorch"] = &AiObjectContextInternal::scorch;
                creators["counterspell"] = &AiObjectContextInternal::counterspell;
                creators["remove curse"] = &AiObjectContextInternal::remove_curse;
                creators["remove curse on party"] = &AiObjectContextInternal::remove_curse_on_party;
                creators["icy veins"] = &AiObjectContextInternal::icy_veins;
                creators["combustion"] = &AiObjectContextInternal::combustion;
                creators["ice block"] = &AiObjectContextInternal::ice_block;
                creators["polymorph"] = &AiObjectContextInternal::polymorph;
                creators["spellsteal"] = &AiObjectContextInternal::spellsteal;
            }

        private:
            static Action* frostbolt(AiManagerRegistry* ai) { return new CastFrostboltAction(ai); }
            static Action* blizzard(AiManagerRegistry* ai) { return new CastBlizzardAction(ai); }
            static Action* frost_nova(AiManagerRegistry* ai) { return new CastFrostNovaAction(ai); }
            static Action* arcane_intellect(AiManagerRegistry* ai) { return new CastArcaneIntellectAction(ai); }
            static Action* arcane_intellect_on_party(AiManagerRegistry* ai) { return new CastArcaneIntellectOnPartyAction(ai); }
            static Action* conjure_water(AiManagerRegistry* ai) { return new CastConjureWaterAction(ai); }
            static Action* conjure_food(AiManagerRegistry* ai) { return new CastConjureFoodAction(ai); }
            static Action* mage_armor(AiManagerRegistry* ai) { return new CastMageArmorAction(ai); }
            static Action* ice_armor(AiManagerRegistry* ai) { return new CastIceArmorAction(ai); }
            static Action* frost_armor(AiManagerRegistry* ai) { return new CastFrostArmorAction(ai); }
            static Action* fireball(AiManagerRegistry* ai) { return new CastFireballAction(ai); }
            static Action* pyroblast(AiManagerRegistry* ai) { return new CastPyroblastAction(ai); }
            static Action* flamestrike(AiManagerRegistry* ai) { return new CastFlamestrikeAction(ai); }
            static Action* fire_blast(AiManagerRegistry* ai) { return new CastFireBlastAction(ai); }
            static Action* scorch(AiManagerRegistry* ai) { return new CastScorchAction(ai); }
            static Action* counterspell(AiManagerRegistry* ai) { return new CastCounterspellAction(ai); }
            static Action* remove_curse(AiManagerRegistry* ai) { return new CastRemoveCurseAction(ai); }
            static Action* remove_curse_on_party(AiManagerRegistry* ai) { return new CastRemoveCurseOnPartyAction(ai); }
            static Action* icy_veins(AiManagerRegistry* ai) { return new CastIcyVeinsAction(ai); }
            static Action* combustion(AiManagerRegistry* ai) { return new CastCombustionAction(ai); }
            static Action* ice_block(AiManagerRegistry* ai) { return new CastIceBlockAction(ai); }
            static Action* polymorph(AiManagerRegistry* ai) { return new CastPolymorphAction(ai); }
            static Action* spellsteal(AiManagerRegistry* ai) { return new CastSpellstealAction(ai); }
        };
    };
};



MageAiObjectContext::MageAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::mage::StrategyFactoryInternal());
    actionContexts.Add(new ai::mage::AiObjectContextInternal());
    triggerContexts.Add(new ai::mage::TriggerFactoryInternal());    
}