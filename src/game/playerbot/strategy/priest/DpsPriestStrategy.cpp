#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "DpsPriestStrategy.h"

using namespace ai;

class DpsPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsPriestStrategyActionNodeFactory()
    {
        creators["shadow word: pain"] = &shadow_word_pain;
        creators["devouring plague"] = &devouring_plague;
        creators["mind flay"] = &mind_flay;
        creators["mind blast"] = &mind_blast;
    }
private:
    static ActionNode* shadow_word_pain(PlayerbotAI* ai)
    {
        return new ActionNode ("shadow word: pain",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* devouring_plague(PlayerbotAI* ai)
    {
        return new ActionNode ("devouring plague",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* mind_flay(PlayerbotAI* ai)
    {
        return new ActionNode ("mind flay",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* mind_blast(PlayerbotAI* ai)
    {
        return new ActionNode ("mind blast",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NextAction::array(0, new NextAction("shoot"), NULL));
    }
};

DpsPriestStrategy::DpsPriestStrategy(PlayerbotAI* ai) : GenericPriestStrategy(ai)
{
    actionNodeFactories.Add(new DpsPriestStrategyActionNodeFactory());
}

NextAction** DpsPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("holy fire", 9.0f), new NextAction("mind blast", 10.0f), new NextAction("smite", 5.0f), NULL);
}

void DpsPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no attackers",
        NextAction::array(0, new NextAction("mind flay", 20.0f), NULL)));
}
