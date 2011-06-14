#pragma once;

#include "NearestGameObjects.h"
#include "LogLevelValue.h"
#include "NearestNpcsValue.h"
#include "PossibleTargetsValue.h"
#include "NearestCorpsesValue.h"
#include "PartyMemberWithoutAuraValue.h"
#include "PartyMemberToHeal.h"
#include "PartyMemberToResurrect.h"
#include "CurrentTargetValue.h"
#include "SelfTargetValue.h"
#include "MasterTargetValue.h"
#include "LineTargetValue.h"
#include "TankTargetValue.h"
#include "DpsTargetValue.h"
#include "CcTargetValue.h"
#include "CurrentCcTargetValue.h"
#include "PetTargetValue.h"
#include "GrindTargetValue.h"
#include "PartyMemberToDispel.h"
#include "StatsValues.h"
#include "AttackerCountValues.h"
#include "AttackersValue.h"
#include "AvailableLootValue.h"
#include "AlwaysLootListValue.h"
#include "LootStrategyValue.h"
#include "HasAvailableLootValue.h"
#include "LastMovementValue.h"
#include "DistanceValue.h"
#include "IsMovingValue.h"
#include "IsBehindValue.h"
#include "ItemCountValue.h"

namespace ai
{
    class ValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        ValueContext()
        {
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
            creators["nearest npcs"] = &ValueContext::nearest_npcs;
            creators["possible targets"] = &ValueContext::possible_targets;
            creators["nearest corpses"] = &ValueContext::nearest_corpses;
            creators["log level"] = &ValueContext::log_level;
            creators["party member without aura"] = &ValueContext::party_member_without_aura;
            creators["party member to heal"] = &ValueContext::party_member_to_heal;
            creators["party member to resurrect"] = &ValueContext::party_member_to_resurrect;
            creators["current target"] = &ValueContext::current_target;
            creators["self target"] = &ValueContext::self_target;
            creators["master"] = &ValueContext::master;
            creators["line target"] = &ValueContext::line_target;
            creators["tank target"] = &ValueContext::tank_target;
            creators["dps target"] = &ValueContext::dps_target;
            creators["cc target"] = &ValueContext::cc_target;
            creators["current cc target"] = &ValueContext::current_cc_target;
            creators["pet target"] = &ValueContext::pet_target;
            creators["grind target"] = &ValueContext::grind_target;
            creators["party member to dispel"] = &ValueContext::party_member_to_dispel;
            creators["health"] = &ValueContext::health;
            creators["rage"] = &ValueContext::rage;
            creators["energy"] = &ValueContext::energy;
            creators["mana"] = &ValueContext::mana;
            creators["combo"] = &ValueContext::combo;
            creators["dead"] = &ValueContext::dead;
            creators["has mana"] = &ValueContext::has_mana;
            creators["attacker count"] = &ValueContext::attacker_count;
            creators["my attacker count"] = &ValueContext::my_attacker_count;
            creators["has aggro"] = &ValueContext::has_aggro;
            creators["mounted"] = &ValueContext::mounted;

            creators["available loot"] = &ValueContext::available_loot;
            creators["has available loot"] = &ValueContext::has_available_loot;
            creators["always loot list"] = &ValueContext::always_loot_list;
            creators["loot strategy"] = &ValueContext::loot_strategy;
            creators["last movement"] = &ValueContext::last_movement;
            creators["distance"] = &ValueContext::distance;
            creators["moving"] = &ValueContext::moving;
            creators["behind"] = &ValueContext::behind;
            creators["item count"] = &ValueContext::item_count;
        }

    private:
        static UntypedValue* item_count(AiManagerRegistry* ai) { return new ItemCountValue(ai); }
        static UntypedValue* behind(AiManagerRegistry* ai) { return new IsBehindValue(ai); }
        static UntypedValue* moving(AiManagerRegistry* ai) { return new IsMovingValue(ai); }
        static UntypedValue* distance(AiManagerRegistry* ai) { return new DistanceValue(ai); }
        static UntypedValue* last_movement(AiManagerRegistry* ai) { return new LastMovementValue(ai); }

        static UntypedValue* available_loot(AiManagerRegistry* ai) { return new AvailableLootValue(ai); }
        static UntypedValue* has_available_loot(AiManagerRegistry* ai) { return new HasAvailableLootValue(ai); }
        static UntypedValue* always_loot_list(AiManagerRegistry* ai) { return new AlwaysLootListValue(ai); }
        static UntypedValue* loot_strategy(AiManagerRegistry* ai) { return new LootStrategyValue(ai); }

        static UntypedValue* attacker_count(AiManagerRegistry* ai) { return new AttackerCountValue(ai); }
        static UntypedValue* my_attacker_count(AiManagerRegistry* ai) { return new MyAttackerCountValue(ai); }
        static UntypedValue* has_aggro(AiManagerRegistry* ai) { return new HasAggroValue(ai); }
        static UntypedValue* mounted(AiManagerRegistry* ai) { return new IsMountedValue(ai); }
        static UntypedValue* health(AiManagerRegistry* ai) { return new HealthValue(ai); }
        static UntypedValue* rage(AiManagerRegistry* ai) { return new RageValue(ai); }
        static UntypedValue* energy(AiManagerRegistry* ai) { return new EnergyValue(ai); }
        static UntypedValue* mana(AiManagerRegistry* ai) { return new ManaValue(ai); }
        static UntypedValue* combo(AiManagerRegistry* ai) { return new ComboPointsValue(ai); }
        static UntypedValue* dead(AiManagerRegistry* ai) { return new IsDeadValue(ai); }
        static UntypedValue* has_mana(AiManagerRegistry* ai) { return new HasManaValue(ai); }
        static UntypedValue* nearest_game_objects(AiManagerRegistry* ai) { return new NearestGameObjects(ai); }
        static UntypedValue* log_level(AiManagerRegistry* ai) { return new LogLevelValue(ai); }
        static UntypedValue* nearest_npcs(AiManagerRegistry* ai) { return new NearestNpcsValue(ai); }
        static UntypedValue* nearest_corpses(AiManagerRegistry* ai) { return new NearestCorpsesValue(ai); }
        static UntypedValue* possible_targets(AiManagerRegistry* ai) { return new PossibleTargetsValue(ai); }
        static UntypedValue* party_member_without_aura(AiManagerRegistry* ai) { return new PartyMemberWithoutAuraValue(ai); }
        static UntypedValue* party_member_to_heal(AiManagerRegistry* ai) { return new PartyMemberToHeal(ai); }
        static UntypedValue* party_member_to_resurrect(AiManagerRegistry* ai) { return new PartyMemberToResurrect(ai); }
        static UntypedValue* party_member_to_dispel(AiManagerRegistry* ai) { return new PartyMemberToDispel(ai); }
        static UntypedValue* current_target(AiManagerRegistry* ai) { return new CurrentTargetValue(ai); }
        static UntypedValue* self_target(AiManagerRegistry* ai) { return new SelfTargetValue(ai); }
        static UntypedValue* master(AiManagerRegistry* ai) { return new MasterTargetValue(ai); }
        static UntypedValue* line_target(AiManagerRegistry* ai) { return new LineTargetValue(ai); }
        static UntypedValue* tank_target(AiManagerRegistry* ai) { return new TankTargetValue(ai); }
        static UntypedValue* dps_target(AiManagerRegistry* ai) { return new DpsTargetValue(ai); }
        static UntypedValue* cc_target(AiManagerRegistry* ai) { return new CcTargetValue(ai); }
        static UntypedValue* current_cc_target(AiManagerRegistry* ai) { return new CurrentCcTargetValue(ai); }
        static UntypedValue* pet_target(AiManagerRegistry* ai) { return new PetTargetValue(ai); }
        static UntypedValue* grind_target(AiManagerRegistry* ai) { return new GrindTargetValue(ai); }
    };
};