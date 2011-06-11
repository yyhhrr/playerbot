#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiObjectContext.h"
#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "NamedObjectContext.h"
#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "ChatCommandTrigger.h"
#include "ChatCommandHandlerStrategy.h"
#include "ListQuestsActions.h"
#include "StatsAction.h"
#include "StrategyContext.h"
#include "TriggerContext.h"
#include "ActionContext.h"
#include "ChatTriggerContext.h"
#include "ChatActionContext.h"

using namespace ai;

AiObjectContext::AiObjectContext(AiManagerRegistry* const ai) : AiManagerRegistryAware(ai) 
{
    strategyContexts.Add(new StrategyContext());
    
    actionContexts.Add(new ActionContext());
    actionContexts.Add(new ChatActionContext());
    
    triggerContexts.Add(new TriggerContext());
    triggerContexts.Add(new ChatTriggerContext());
}
