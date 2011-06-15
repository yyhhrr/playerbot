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
#include "ValueContext.h"

using namespace ai;

AiObjectContext::AiObjectContext(PlayerbotAI* ai) : PlayerbotAIAware(ai) 
{
    strategyContexts.Add(new StrategyContext());
    
    actionContexts.Add(new ActionContext());
    actionContexts.Add(new ChatActionContext());
    actionContexts.Add(new WorldPacketActionContext());
    
    triggerContexts.Add(new TriggerContext());
    triggerContexts.Add(new ChatTriggerContext());
    triggerContexts.Add(new WorldPacketTriggerContext());

    valueContexts.Add(new ValueContext());
}

void AiObjectContext::Update()
{
    strategyContexts.Update();
    triggerContexts.Update();
    actionContexts.Update();
    valueContexts.Update();
}
