#include "../../pchdef.h"
#include "../playerbot.h"
#include "NearestGameObjects.h"

#include "../../GridNotifiers.h"
#include "../../GridNotifiersImpl.h"
#include "../../CellImpl.h"

using namespace ai;
using namespace MaNGOS;

class AnyGameObjectInObjectRangeCheck
{
public:
    AnyGameObjectInObjectRangeCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
    WorldObject const& GetFocusObject() const { return *i_obj; }
    bool operator()(GameObject* u)
    {
        if (u && i_obj->IsWithinDistInMap(u, i_range) && u->isSpawned() && u->GetGOInfo())
            return true;

        return false;
    }

private:
    WorldObject const* i_obj;
    float i_range;
};

list<GameObject*> NearestGameObjects::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();

    list<GameObject *> targets;

    AnyGameObjectInObjectRangeCheck u_check(bot, range);
    GameObjectListSearcher<AnyGameObjectInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects((const WorldObject*)bot, searcher, range);

    for(list<GameObject *>::iterator tIter = targets.begin(); tIter != targets.end();)
    {
        if(!bot->IsWithinLOSInMap(*tIter))
        {
            list<GameObject *>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else
            ++tIter;
    }

    return targets;
}