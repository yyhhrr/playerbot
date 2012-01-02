#pragma once

namespace ai
{
    class LowManaStrategy : public Strategy
    {
    public:
        LowManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "low mana"; }
    };


}
