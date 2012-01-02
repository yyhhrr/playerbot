#pragma once

namespace ai
{
    class ShadowPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
    {
    public:
        ShadowPriestStrategyActionNodeFactory()
        {
            creators["mind flay"] = &mind_flay;
            creators["mind blast"] = &mind_blast;
        }
    private:
        static ActionNode* mind_flay(PlayerbotAI* ai)
        {
            return new ActionNode ("mind flay",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* mind_blast(PlayerbotAI* ai)
        {
            return new ActionNode ("mind blast",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("mind flay"), NULL),
                /*C*/ NULL);
        }
    };
};
