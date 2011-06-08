#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageActions.h"
#include "MageActionFactory.h"
#include "FrostMageStrategy.h"
#include "GenericMageNonCombatStrategy.h"
#include "FireMageStrategy.h"
#include "../PullStrategy.h"
#include "MageTriggers.h"
#include "../NamedObjectFactory.h"

using namespace ai;


namespace ai
{
    namespace mage
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, mage::StrategyFactoryInternal>
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
            Strategy* frost(AiManagerRegistry* ai) { return new FrostMageStrategy(ai); }
            Strategy* fire(AiManagerRegistry* ai) { return new FireMageStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericMageNonCombatStrategy(ai); }
            Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        }
        strategyFactoryInternal;
    };
};

Strategy* MageActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::mage::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace mage
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
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
            Trigger* fireball(AiManagerRegistry* ai) { return new FireballTrigger(ai); }
            Trigger* pyroblast(AiManagerRegistry* ai) { return new PyroblastTrigger(ai); }
            Trigger* combustion(AiManagerRegistry* ai) { return new CombustionTrigger(ai); }
            Trigger* icy_veins(AiManagerRegistry* ai) { return new IcyVeinsTrigger(ai); }
            Trigger* arcane_intellect(AiManagerRegistry* ai) { return new ArcaneIntellectTrigger(ai); }
            Trigger* arcane_intellect_on_party(AiManagerRegistry* ai) { return new ArcaneIntellectOnPartyTrigger(ai); }
            Trigger* mage_armor(AiManagerRegistry* ai) { return new MageArmorTrigger(ai); }
            Trigger* remove_curse(AiManagerRegistry* ai) { return new RemoveCurseTrigger(ai); }
            Trigger* remove_curse_on_party(AiManagerRegistry* ai) { return new PartyMemberRemoveCurseTrigger(ai); }
            Trigger* counterspell(AiManagerRegistry* ai) { return new CounterspellInterruptSpellTrigger(ai); }
            Trigger* polymorph(AiManagerRegistry* ai) { return new PolymorphTrigger(ai); }
            Trigger* spellsteal(AiManagerRegistry* ai) { return new SpellstealTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* MageActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::mage::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace mage
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["frostbolt"] = &ActionFactoryInternal::frostbolt;
                creators["blizzard"] = &ActionFactoryInternal::blizzard;
                creators["frost nova"] = &ActionFactoryInternal::frost_nova;
                creators["arcane intellect"] = &ActionFactoryInternal::arcane_intellect;
                creators["arcane intellect on party"] = &ActionFactoryInternal::arcane_intellect_on_party;
                creators["conjure water"] = &ActionFactoryInternal::conjure_water;
                creators["conjure food"] = &ActionFactoryInternal::conjure_food;
                creators["mage armor"] = &ActionFactoryInternal::mage_armor;
                creators["ice armor"] = &ActionFactoryInternal::ice_armor;
                creators["frost armor"] = &ActionFactoryInternal::frost_armor;
                creators["fireball"] = &ActionFactoryInternal::fireball;
                creators["pyroblast"] = &ActionFactoryInternal::pyroblast;
                creators["flamestrike"] = &ActionFactoryInternal::flamestrike;
                creators["fire blast"] = &ActionFactoryInternal::fire_blast;
                creators["scorch"] = &ActionFactoryInternal::scorch;
                creators["counterspell"] = &ActionFactoryInternal::counterspell;
                creators["remove curse"] = &ActionFactoryInternal::remove_curse;
                creators["remove curse on party"] = &ActionFactoryInternal::remove_curse_on_party;
                creators["icy veins"] = &ActionFactoryInternal::icy_veins;
                creators["combustion"] = &ActionFactoryInternal::combustion;
                creators["ice block"] = &ActionFactoryInternal::ice_block;
                creators["polymorph"] = &ActionFactoryInternal::polymorph;
                creators["spellsteal"] = &ActionFactoryInternal::spellsteal;
            }

        private:
            Action* frostbolt(AiManagerRegistry* ai) { return new CastFrostboltAction(ai); }
            Action* blizzard(AiManagerRegistry* ai) { return new CastBlizzardAction(ai); }
            Action* frost_nova(AiManagerRegistry* ai) { return new CastFrostNovaAction(ai); }
            Action* arcane_intellect(AiManagerRegistry* ai) { return new CastArcaneIntellectAction(ai); }
            Action* arcane_intellect_on_party(AiManagerRegistry* ai) { return new CastArcaneIntellectOnPartyAction(ai); }
            Action* conjure_water(AiManagerRegistry* ai) { return new CastConjureWaterAction(ai); }
            Action* conjure_food(AiManagerRegistry* ai) { return new CastConjureFoodAction(ai); }
            Action* mage_armor(AiManagerRegistry* ai) { return new CastMageArmorAction(ai); }
            Action* ice_armor(AiManagerRegistry* ai) { return new CastIceArmorAction(ai); }
            Action* frost_armor(AiManagerRegistry* ai) { return new CastFrostArmorAction(ai); }
            Action* fireball(AiManagerRegistry* ai) { return new CastFireballAction(ai); }
            Action* pyroblast(AiManagerRegistry* ai) { return new CastPyroblastAction(ai); }
            Action* flamestrike(AiManagerRegistry* ai) { return new CastFlamestrikeAction(ai); }
            Action* fire_blast(AiManagerRegistry* ai) { return new CastFireBlastAction(ai); }
            Action* scorch(AiManagerRegistry* ai) { return new CastScorchAction(ai); }
            Action* counterspell(AiManagerRegistry* ai) { return new CastCounterspellAction(ai); }
            Action* remove_curse(AiManagerRegistry* ai) { return new CastRemoveCurseAction(ai); }
            Action* remove_curse_on_party(AiManagerRegistry* ai) { return new CastRemoveCurseOnPartyAction(ai); }
            Action* icy_veins(AiManagerRegistry* ai) { return new CastIcyVeinsAction(ai); }
            Action* combustion(AiManagerRegistry* ai) { return new CastCombustionAction(ai); }
            Action* ice_block(AiManagerRegistry* ai) { return new CastIceBlockAction(ai); }
            Action* polymorph(AiManagerRegistry* ai) { return new CastPolymorphAction(ai); }
            Action* spellsteal(AiManagerRegistry* ai) { return new CastSpellstealAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* MageActionFactory::createAction(const char* name)
{
    Action* action = ai::mage::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
