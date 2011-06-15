#include "../../pchdef.h"
#include "../playerbot.h"
#include "ReviveFromCorpseAction.h"

using namespace ai;

bool ReviveFromCorpseAction::Execute(Event event)
{
    Player* bot = ai->GetBot();
    Player* master = ai->GetMaster();
    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
        return false;

    time_t reclaimTime = corpse->GetGhostTime() + bot->GetCorpseReclaimDelay( corpse->GetType()==CORPSE_RESURRECTABLE_PVP );
    if (reclaimTime > time(0))
    {
        ostringstream os;
        os << "Will resurrect in ";
        os << (reclaimTime - time(0));
        os << " secs";
        ai->TellMaster(os.str().c_str());
        ai->SetNextCheckDelay(reclaimTime - time(0));
    }
    else
    {
        PlayerbotChatHandler ch(master);
        if (! ch.revive(*bot))
        {
            ai->TellMaster(".. could not be revived ..");
            return false;
        }
        ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Set(NULL);
        bot->SetSelectionGuid(ObjectGuid());
    }
    return true;
}
