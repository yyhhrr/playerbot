#ifndef _RandomPlayerbotMgr_H
#define _RandomPlayerbotMgr_H

#include "Common.h"
#include "PlayerbotAIBase.h"

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;

using namespace std;

class MANGOS_DLL_SPEC RandomPlayerbotMgr : public PlayerbotAIBase
{
    public:
        RandomPlayerbotMgr(Player* const master);
        virtual ~RandomPlayerbotMgr();

        virtual void UpdateAIInternal(uint32 elapsed);

    private:
        uint32 GetEventValue(uint32 bot, string event);
        uint32 SetEventValue(uint32 bot, string event, uint32 value, uint32 validIn);
        list<uint32> GetBots();
        vector<uint32> GetFreeBots();
        uint32 AddRandomBot();
        void ProcessBot(uint32 bot);

    private:
        Player* const master;
        uint32 account;
};

#endif
