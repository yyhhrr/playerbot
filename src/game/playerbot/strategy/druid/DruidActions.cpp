#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidActions.h"

using namespace ai;

bool CastCasterFormAction::Execute(Event event)
{
    spellManager->RemoveAura("dire bear form");
    spellManager->RemoveAura("bear form");
    spellManager->RemoveAura("cat form");
	spellManager->RemoveAura("moonkin form");
    spellManager->RemoveAura("travel form");
	spellManager->RemoveAura("aquatic form");
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

Unit* CastEntanglingRootsCcAction::GetTarget()
{
    return ai->GetTargetManager()->FindCcTarget("entangling roots");
}

bool CastEntanglingRootsCcAction::Execute(Event event)
{
    return spellManager->CastSpell("entangling roots", GetTarget()); 
}
