#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiObjectContext.h"
#include "NamedObjectContext.h"
#include "StrategyContext.h"
#include "TriggerContext.h"
#include "ActionContext.h"
#include "ChatTriggerContext.h"
#include "ChatActionContext.h"
#include "WorldPacketTriggerContext.h"
#include "WorldPacketActionContext.h"

using namespace ai;

AiObjectContext::AiObjectContext(AiManagerRegistry* const ai) : AiManagerRegistryAware(ai) 
{
    strategyContexts.Add(new StrategyContext());
    
    actionContexts.Add(new ActionContext());
    actionContexts.Add(new ChatActionContext());
    actionContexts.Add(new WorldPacketActionContext());
    
    triggerContexts.Add(new TriggerContext());
    triggerContexts.Add(new ChatTriggerContext());
    triggerContexts.Add(new WorldPacketTriggerContext());
}
