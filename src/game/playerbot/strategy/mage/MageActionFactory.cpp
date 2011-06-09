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

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
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

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
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

        class ActionFactoryInternal : public NamedObjectFactory<Action>
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



MageActionFactory::MageActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::mage::StrategyFactoryInternal());
    actionFactories.push_back(new ai::mage::ActionFactoryInternal());
    triggerFactories.push_back(new ai::mage::TriggerFactoryInternal());    
}