#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TellTargetAction.h"


using namespace ai;

bool TellTargetAction::Execute(Event event)
{
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    if (target)
    {
        ostringstream out;
		out << "Target: " << target->GetName();
        ai->TellMaster(out);

        context->GetValue<Unit*>("old target")->Set(target);
    }
    return true;
}
