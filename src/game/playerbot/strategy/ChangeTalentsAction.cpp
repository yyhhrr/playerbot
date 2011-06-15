#include "../../pchdef.h"
#include "../playerbot.h"
#include "ChangeTalentsAction.h"

using namespace ai;

bool ChangeTalentsAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();

    string text = event.getParam();
    if (text == "talents 1" || text == "talents primary")
    {
        bot->ActivateSpec(0);
        ai->GetAi()->TellMaster("Primary talents activated");
    }
    else if (text == "talents 2" || text == "talents secondary")
    {
        bot->ActivateSpec(1);
        ai->GetAi()->TellMaster("Secondary talents activated");
    }
    else
        return false;

    return true;
}
