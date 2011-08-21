#pragma once

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;

class PlayerbotFactory
{
public:
    PlayerbotFactory(Player* bot, uint32 level) : bot(bot), level(level) {}

    static ObjectGuid GetRandomBot();
    void Randomize();

private:
    void InitEquipment();
    bool CanEquipUnseenItem(uint8 slot, uint16 &dest, uint32 item);
    bool EquipItem(uint8 slot);
    void InitSkills();
    void SetRandomSkill(uint16 id);
    void InitSpells();
    void InitTalents();

private:
    Player* bot;
    uint32 level;
};
