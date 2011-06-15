#pragma once

#include "../Action.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"

namespace ai
{
    class MeleeAction : public AttackAction 
    {
    public:
        MeleeAction(PlayerbotAI* ai) : AttackAction(ai, "melee") {}

        virtual const char* GetTargetName() { return "current target"; }
    };

    class ChangeCombatStrategyAction : public Action 
    {
    public:
        ChangeCombatStrategyAction(PlayerbotAI* ai, const char* name);
        virtual bool Execute(Event event);

    private:
        string name;
    };
}