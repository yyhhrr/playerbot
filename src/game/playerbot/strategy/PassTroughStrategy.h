#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"

namespace ai
{
    class PassTroughStrategy : public Strategy
    {
    public:
        PassTroughStrategy(AiManagerRegistry* const ai, float relevance = 100.0f) : Strategy(ai), relevance(relevance) {}

        virtual void InitTriggers(std::list<TriggerNode*> &triggers)
        {
            for (list<string>::iterator i = supported.begin(); i != supported.end(); i++)
            {
                const char* s = i->c_str();

                triggers.push_back(new TriggerNode(
                    s, 
                    NextAction::array(0, new NextAction(s, relevance), NULL)));
            }
        }

        virtual ActionNode* GetAction(const char* name)
        {
            return new ActionNode(name,  
                /*P*/ NULL,
                /*A*/ NULL, 
                /*C*/ NULL);
        }

    protected:
        list<string> supported;
        float relevance;
    };
}
