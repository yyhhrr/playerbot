#pragma once

namespace ai
{
	class CastSinisterStrikeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSinisterStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "sinister strike") {} 
	};

    class CastMutilateAction : public CastMeleeSpellAction 
    { 
    public: 
        CastMutilateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mutilate") {} 
    };

	class CastGougeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGougeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "gouge") {} 
	};

    class CastBackstabAction : public CastMeleeSpellAction 
    { 
    public: 
        CastBackstabAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "backstab") {} 
    };
}