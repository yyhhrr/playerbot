#include "../../pchdef.h"
#include "../playerbot.h"
#include "TeleportAction.h"
#include "LastMovementValue.h"

using namespace ai;

bool TeleportAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();

    list<GameObject*> gos = *ai->GetAi()->GetAiObjectContext()->GetValue<list<GameObject*>>("nearest game objects");
    for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = *i;
        GameObjectInfo const *goInfo = go->GetGOInfo();
        if (goInfo->type != GAMEOBJECT_TYPE_SPELLCASTER)
            continue;

        uint32 spellId = goInfo->spellcaster.spellId;
        const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
        if (pSpellInfo->Effect[0] != SPELL_EFFECT_TELEPORT_UNITS && pSpellInfo->Effect[1] != SPELL_EFFECT_TELEPORT_UNITS && pSpellInfo->Effect[2] != SPELL_EFFECT_TELEPORT_UNITS)
            continue;

        ostringstream out; out << "Teleporting using " << goInfo->name;
        ai->GetAi()->TellMaster(out);

        Spell *spell = new Spell(bot, pSpellInfo, false);
        SpellCastTargets targets;
        targets.setUnitTarget(bot);
        spell->prepare(&targets, false);
        spell->cast(true);
        return true;
    }


    LastMovement& movement = ai->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
    if (movement.lastAreaTrigger)
    {
        WorldPacket p(CMSG_AREATRIGGER);
        p << movement.lastAreaTrigger;
        p.rpos(0);

        bot->GetSession()->HandleAreaTriggerOpcode(p);
        movement.lastAreaTrigger = 0;
        return true;
    }

    ai->GetAi()->TellMaster("Cannot find any portal to teleport");
    return false;
}
