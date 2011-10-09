#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ReviveFromCorpseAction.h"
#include "../../PlayerbotFactory.h"

using namespace ai;

bool ReviveFromCorpseAction::Execute(Event event)
{
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
        ai->TellMaster(os.str());
        ai->SetNextCheckDelay(5000);
    }
    else
    {
        PlayerbotChatHandler ch(master);
        if (! ch.revive(*bot))
        {
            ai->TellMaster(".. could not be revived ..");
            return false;
        }
        context->GetValue<Unit*>("current target")->Set(NULL);
        bot->SetSelectionGuid(ObjectGuid());

        if (urand(0, 10) >= 5 && bot->getFaction() != master->getFaction())
        {
			PlayerbotFactory factory(bot, master->getLevel());
            factory.Randomize();
        }
    }
    return true;
}
