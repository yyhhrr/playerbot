#include "../../pchdef.h"
#include "../playerbot.h"
#include "QueryQuestAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool QueryQuestAction::Execute(Event event)
{
    Player *master = ai->GetMaster();
    Player *bot = ai->GetBot();
    string text = event.getParam();

    PlayerbotChatHandler ch(master);
    uint32 questId = ch.extractQuestId(text.c_str());
    if (!questId)
        return false;

    for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        if(questId == bot->GetQuestSlotQuestId(slot))
        {
            ostringstream out;
            out << "Quest ";
            out << (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE ? "completed" : "not completed");
            ai->TellMaster(out.str().c_str());
            return true;
        }
    }

    return false;
}
