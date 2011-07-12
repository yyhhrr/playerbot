#pragma once
#include "../Value.h"
#include "TargetValue.h"
#include "../../LootObjectStack.h"

namespace ai
{
    class HasTotemValue : public CalculatedValue<bool>, public Qualified
	{
	public:
        HasTotemValue(PlayerbotAI* ai) : CalculatedValue<bool>(ai) {}

    public:
        bool Calculate()
        {
            list<Unit*> units = *context->GetValue<list<Unit*>>("nearest npcs");
            for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = *i;
                Creature* creature = dynamic_cast<Creature*>(unit);
                if (!creature || !creature->IsTotem())
                    continue;

                if (!strstri(qualifier.c_str(), creature->GetName()))
                    return true;
            }

            return false;
        }
    };
}
