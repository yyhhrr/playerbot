#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GuildBankAction.h"

#include "../values/ItemCountValue.h"

using namespace std;
using namespace ai;

bool GuildBankAction::Execute(Event event)
{
    ai->TellMaster("Cannot find the guild bank nearby");
    return false;
}
