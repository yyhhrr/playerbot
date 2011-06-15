#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidActions.h"

using namespace ai;

bool CastCasterFormAction::Execute(Event event)
{
    ai->GetAi()->RemoveAura("dire bear form");
    ai->GetAi()->RemoveAura("bear form");
    ai->GetAi()->RemoveAura("cat form");
	ai->GetAi()->RemoveAura("moonkin form");
    ai->GetAi()->RemoveAura("travel form");
	ai->GetAi()->RemoveAura("aquatic form");
    return true;
}


NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), NULL), CastSpellAction::getPrerequisites());
}

Value<Unit*>* CastEntanglingRootsCcAction::GetTargetValue()
{
    return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>("cc target", "entangling roots");
}

bool CastEntanglingRootsCcAction::Execute(Event event)
{
    return ai->GetAi()->CastSpell("entangling roots", GetTarget()); 
}
