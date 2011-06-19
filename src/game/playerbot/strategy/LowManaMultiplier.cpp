#include "../../pchdef.h"
#include "../playerbot.h"
#include "LowManaMultiplier.h"

using namespace ai;

float LowManaMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    string name = action->getName();

    // Hunter
    if (name == "arcane shot" || 
        name == "multi-shot" ||
        name == "serpent sting" ||
        name == "viper sting" ||
        name == "scorpid sting" 
        ) return !(rand() % 50) ? 1 : 0;

    // Priest
    if (name == "shadow word: pain" || 
        name == "devouring plague" || 
        name == "mind blast" 
        ) return !(rand() % 50) ? 1 : 0;


    return 1.0f;
}