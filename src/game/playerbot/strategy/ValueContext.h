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
            creators["master target"] = &ValueContext::master_target;
            creators["line target"] = &ValueContext::line_target;
            creators["tank target"] = &ValueContext::tank_target;
            creators["dps target"] = &ValueContext::dps_target;
            creators["cc target"] = &ValueContext::cc_target;
            creators["current cc target"] = &ValueContext::current_cc_target;
            creators["pet target"] = &ValueContext::pet_target;
            creators["grind target"] = &ValueContext::grind_target;
            creators["party member to dispel"] = &ValueContext::party_member_to_dispel;
        }

    private:
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
        static UntypedValue* master_target(AiManagerRegistry* ai) { return new MasterTargetValue(ai); }
        static UntypedValue* line_target(AiManagerRegistry* ai) { return new LineTargetValue(ai); }
        static UntypedValue* tank_target(AiManagerRegistry* ai) { return new TankTargetValue(ai); }
        static UntypedValue* dps_target(AiManagerRegistry* ai) { return new DpsTargetValue(ai); }
        static UntypedValue* cc_target(AiManagerRegistry* ai) { return new CcTargetValue(ai); }
        static UntypedValue* current_cc_target(AiManagerRegistry* ai) { return new CurrentCcTargetValue(ai); }
        static UntypedValue* pet_target(AiManagerRegistry* ai) { return new PetTargetValue(ai); }
        static UntypedValue* grind_target(AiManagerRegistry* ai) { return new GrindTargetValue(ai); }
    };
};