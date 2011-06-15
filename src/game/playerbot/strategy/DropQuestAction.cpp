#include "../../pchdef.h"
#include "../playerbot.h"
#include "DropQuestAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool DropQuestAction::Execute(Event event)
{
    Player* bot = ai->GetBot();
    Player *master = ai->GetMaster();
    string link = event.getParam();
    
    ObjectGuid oldSelection = master->GetSelectionGuid();
    master->SetSelectionGuid(bot->GetObjectGuid());

    PlayerbotChatHandler ch(bot);
    if (!ch.dropQuest(link.c_str()))
    {
        ostringstream out; out << "Could not drop quest: " << link;
        ai->TellMaster(out);
        return false;
    }

    master->SetSelectionGuid(oldSelection);
    ai->TellMaster("Quest removed");
    return true;
}
