#include "../../pchdef.h"
#include "../playerbot.h"
#include "PartyMemberToDispel.h"

using namespace ai;


Unit* PartyMemberToDispel::Calculate()
{
    uint32 dispelType = atoi(qualifier.c_str());

    Player* bot = ai->GetAi()->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
        if( !player || !player->isAlive() || player == bot)
            continue;

        if (ai->GetAi()->HasAuraToDispel(player, dispelType))
            return player;

        Pet* pet = player->GetPet();
        if (pet && ai->GetAi()->HasAuraToDispel(pet, dispelType))
            return pet;
    }

    return NULL;
}

