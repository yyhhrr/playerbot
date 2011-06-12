#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericActions.h"

#include "Engine.h"

using namespace ai;
using namespace std;

bool ActionExecutionListeners::ActionExecuted(Action* action)
{
    bool result = true;
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
    {
        result &= (*i)->ActionExecuted(action);
    }
    return result;
}

ActionExecutionListeners::~ActionExecutionListeners()
{
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
    {
        delete *i;
    }
    listeners.clear();
}


Engine::~Engine(void)
{
    Reset();
    
    strategies.clear();
}

void Engine::Reset()
{
    ActionNode* action = NULL;
    do 
    {
        action = queue.Pop();
    } while (action);

    triggers.clear();

    for (std::list<Multiplier*>::iterator i = multipliers.begin(); i != multipliers.end(); i++)
    {
        Multiplier* multiplier = *i;
        delete multiplier;
    }
    multipliers.clear();
}

void Engine::Init()
{
    Reset();

    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        strategy->InitMultipliers(multipliers);
        strategy->InitTriggers(triggers);
        MultiplyAndPush(strategy->getDefaultActions(), 0.0f, false, Event());
    }
}


bool Engine::DoNextAction(Unit* unit, int depth) 
{
    bool actionExecuted = false;
    ActionBasket* basket = NULL;

    time_t currentTime = time(0);
    aiObjectContext->Update();
    ProcessTriggers();

    int iterations = 0;
    do {
        basket = queue.Peek();
        if (basket) {
			if (++iterations > maxIterations)
				break;

            float relevance = basket->getRelevance(); // just for reference
            bool skipPrerequisites = basket->isSkipPrerequisites();
            Event event = basket->getEvent();
            // NOTE: queue.Pop() deletes basket
            ActionNode* actionNode = queue.Pop();
            Action* action = InitializeAction(actionNode);

            if (action && action->isUseful()) {
                if (action->isPossible()) {
                    if ((!skipPrerequisites || lastRelevance-relevance > 0.02) && 
                            MultiplyAndPush(actionNode->getPrerequisites(), relevance + 0.01, false, event)) {
                        PushAgain(actionNode, relevance, basket->getEvent());
                        continue;
                    }

                    sLog.outDetail("A:%s", action->getName());

                    if (actionExecutionListeners.ActionExecuted(actionNode->getAction()))
                        actionExecuted = action->Execute(event);

                    if (actionExecuted) {
                        MultiplyAndPush(actionNode->getContinuers(), 0, false, event);
                        lastRelevance = relevance;
                        delete actionNode;
                        break;
                    }
                    else {
                        MultiplyAndPush(actionNode->getAlternatives(), relevance, false, event);
                        sLog.outDetail("NOT EXECUTED:%s", actionNode->getName());
                    }
                }
                else {
                    MultiplyAndPush(actionNode->getAlternatives(), relevance, false, event);
                    sLog.outDetail("IMPOSSIBLE:%s", actionNode->getName());
                }
            }
            else {
                lastRelevance = relevance;
                sLog.outDetail("USELESS:%s", actionNode->getName());
            }
            delete actionNode;
        }
    }
    while (basket);

    if (!basket) {
        lastRelevance = 0.0f;
        PushDefaultActions();
        if (queue.Peek() && depth < 2)
            return DoNextAction(unit, depth + 1);
    }

    if (time(0) - currentTime > 1) {
        sLog.outDetail("too long execution");
    }

    return actionExecuted;
}

ActionNode* Engine::GetAction(const char* name)
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        ActionNode* node = strategy->GetAction(name);
        if (node)
            return node;
    }
    return NULL;
}

bool Engine::MultiplyAndPush(NextAction** actions, float forceRelevance, bool skipPrerequisites, Event event)
{
    bool pushed = false;
    if (actions)
    {
        for (int j=0; j<10; j++) // TODO: remove 10
        {
            NextAction* nextAction = actions[j];
            if (nextAction)
            {
                ActionNode* action = GetAction(nextAction->getName());
                InitializeAction(action);

                float k = nextAction->getRelevance();
                for (std::list<Multiplier*>::iterator i = multipliers.begin(); i!= multipliers.end(); i++)
                {
                    Multiplier* multiplier = *i;
                    k *= multiplier->GetValue(action->getAction());
                }

                if (forceRelevance > 0.0f)
                    k = forceRelevance;

                if (k > 0)
                {
                    queue.Push(new ActionBasket(action, k, skipPrerequisites, event));
                    pushed = true;
                }

                delete nextAction;
            }
            else 
                break;
        }
        delete actions;
    }
    return pushed;
}

bool Engine::ExecuteAction(const char* name)
{
	bool result = false;

    ActionNode *actionNode = GetAction(name);
    if (!actionNode)
        return false;

    Action* action = InitializeAction(actionNode);
    if (action && action->isPossible() && action->isUseful())
    {
        if (actionExecutionListeners.ActionExecuted(action))
		{
            result = action->Execute(Event());
		}

        MultiplyAndPush(action->getContinuers(), 0.0f, false, Event());
    }
	return result;
}

void Engine::addStrategy(const char* name)
{
    removeStrategy(name);

    Strategy* strategy = aiObjectContext->GetStrategy(name);
    if (strategy)
	{
        strategies.push_back(strategy);

		PlayerbotAI* manager = ai->GetAi();
		if (manager)
		{
			string list = strategy->GetIncompatibleStrategies();
			manager->ChangeStrategy(list.c_str(), this);
		}
	}

    Init();
}

void Engine::addStrategies(const char* first, ...)
{
	addStrategy(first);

	va_list vl;
	va_start(vl, first);

	const char* cur = NULL;
	do 
	{
		cur = va_arg(vl, const char*);
		if (cur)
			addStrategy(cur);
	}
	while (cur);

	va_end(vl);
}

bool Engine::removeStrategy(const char* name)
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        if (!strcmp(strategy->getName(), name))
        {
            strategies.remove(strategy);
            Init();
            return true;
        }
    }

    return false;
}

void Engine::toggleStrategy(const char* name)
{
    if (!removeStrategy(name)) 
        addStrategy(name);
}

void Engine::ProcessTriggers()
{
    for (std::list<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        TriggerNode* node = *i;
        Trigger* trigger = node->getTrigger();
        if (!trigger)
        {
            trigger = aiObjectContext->GetTrigger(node->getName());
            node->setTrigger(trigger);
        }

        if (!trigger)
            continue;

        if (testMode || trigger->needCheck())
        {
            Event event = trigger->Check();
            if (!event)
                continue;

            MultiplyAndPush(node->getHandlers(), 0.0f, false, event);
        }
    }
}

void Engine::PushDefaultActions() 
{
    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        MultiplyAndPush(strategy->getDefaultActions(), 0.0f, false, Event());
    }
}

string Engine::ListStrategies()
{
    string s = "Strategies: ";

    if (strategies.empty())
        return s;

    for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = *i;
        s.append(strategy->getName());
        s.append(", ");
    }
    return s.substr(0, s.length() - 2);
}

void Engine::PushAgain(ActionNode* actionNode, float relevance, Event event) 
{
    NextAction** nextAction = new NextAction*[2];
    nextAction[0] = new NextAction(actionNode->getName(), relevance);
    nextAction[1] = NULL;
    MultiplyAndPush(nextAction, relevance, true, event);
    delete actionNode;
}

bool Engine::ContainsStrategy(StrategyType type)
{
	for (std::list<Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
	{
		Strategy* strategy = *i;
		if (strategy->GetType() & type)
			return true;
	}
	return false;
}

Action* Engine::InitializeAction(ActionNode* actionNode) 
{
    Action* action = actionNode->getAction();
    if (!action)
    {
        action = aiObjectContext->GetAction(actionNode->getName());
        actionNode->setAction(action);
    }
    return action;
}
