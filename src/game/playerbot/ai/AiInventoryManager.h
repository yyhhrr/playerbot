#pragma once

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;

    class IterateItemsVisitor 
    {
    public:
        IterateItemsVisitor() {}

        virtual bool Visit(Item* item) = 0;
    };

    class FindItemVisitor : public IterateItemsVisitor {
    public:
        FindItemVisitor() : IterateItemsVisitor(), result(NULL) {}

        virtual bool Visit(Item* item)
        {
            if (!Accept(item->GetProto()))
                return true;

            result = item;
            return false;
        }

        Item* GetResult() { return result; }

    protected:
        virtual bool Accept(const ItemPrototype* proto) = 0;

    private:
        Item* result;
    };

    enum IterateItemsMask
    {
        ITERATE_ITEMS_IN_BAGS = 1,
        ITERATE_ITEMS_IN_EQUIP = 2,
        ITERATE_ALL_ITEMS = 255
    };

	class AiInventoryManager : public AiManagerBase
	{
	public:
		AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);
        virtual ~AiInventoryManager();

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
        virtual void Query(const string& text);

	};

};
