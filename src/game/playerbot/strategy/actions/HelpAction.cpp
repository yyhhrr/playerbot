#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HelpAction.h"
#include "ChatActionContext.h"

using namespace ai;

HelpAction::HelpAction(PlayerbotAI* ai) : Action(ai, "help") 
{
    ctx = new ChatActionContext();
}

HelpAction::~HelpAction()
{
    delete ctx;
}

bool HelpAction::Execute(Event event)
{
    ostringstream out; out << "Whisper any of: ";

    set<string> commands = ctx->supports();
    for (set<string>::iterator i = commands.begin(); i != commands.end(); ++i)
    {
        out << *i << ", ";
    }

    out << "[item], [quest] or [object] link";
    ai->TellMaster(out);

    return true;
}
