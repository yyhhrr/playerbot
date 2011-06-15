#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidActions.h"

using namespace ai;

bool CastCasterFormAction::Execute(Event event)
{
    ai->RemoveAura("dire bear form");
    ai->RemoveAura("bear form");
    ai->RemoveAura("cat form");
	ai->RemoveAura("moonkin form");
    ai->RemoveAura("travel form");
	ai->RemoveAura("aquatic form");
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
    return ai->GetAiObjectContext()->GetValue<Unit*>("cc target", "entangling roots");
}

bool CastEntanglingRootsCcAction::Execute(Event event)
{
    return ai->CastSpell("entangling roots", GetTarget()); 
}
