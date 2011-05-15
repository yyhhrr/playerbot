#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

void AiSocialManager::Emote(uint32 emote)
{
	bot->HandleEmoteCommand(emote);
}

void AiSocialManager::TellMaster(LogLevel level, const char* text)
{
	if (logLevel < level)
		return;

	ostringstream out;
	out << GetLogLevel(level) << ": " << text;
	TellMaster(out.str().c_str());
}

void AiSocialManager::TellMaster(const char* text)
{
	WorldPacket data(SMSG_MESSAGECHAT, 1024);
	bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
	ai->GetMaster()->GetSession()->SendPacket(&data);
	bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
}

void AiSocialManager::LeaveGroup()
{
	Group* group = bot->GetGroup();
	if (group) 
		group->RemoveMember(bot->GetGUID(), 0);
}

void AiSocialManager::AcceptInvitation()
{
	Group* grp = bot->GetGroupInvite();
	if (!grp)
		return;

	Player* inviter = sObjectMgr.GetPlayer(grp->GetLeaderGuid());
	if (!inviter)
		return;

	WorldPacket p;
	uint32 roles_mask = 0;
	p << roles_mask;
	bot->GetSession()->HandleGroupAcceptOpcode(p);
}

string AiSocialManager::GetLogLevel(LogLevel level) 
{
	switch (level) 
	{
	case LOG_LVL_BASIC:
		return "basic";
	case LOG_LVL_MINIMAL:
		return "minimal";
	case LOG_LVL_DETAIL:
		return "detail";
	default:
		return "debug";
	}
}

void AiSocialManager::SetLogLevel(string level) 
{
	if (level == "debug")
		logLevel = LOG_LVL_DEBUG;
	else if (level == "minimal")
		logLevel = LOG_LVL_MINIMAL;
	else if (level == "detail")
		logLevel = LOG_LVL_DETAIL;
	else 
		logLevel = LOG_LVL_BASIC;
}

void AiSocialManager::TellReputation() 
{
	Player *master = ai->GetMaster();
	ObjectGuid selection = master->GetSelectionGuid();
	if (selection.IsEmpty())
		return;

	Unit* unit = master->GetMap()->GetUnit(selection);
	if (!unit)
		return;

	const FactionTemplateEntry *factionTemplate = unit->getFactionTemplateEntry();
	uint32 faction = factionTemplate->faction;
	const FactionEntry* entry = sFactionStore.LookupEntry(faction);
	int32 reputation = bot->GetReputationMgr().GetReputation(faction);
	
	ostringstream out;
	out << "Reputation with " << entry->name[0] << ": ";
	ReputationRank rank = bot->GetReputationMgr().GetRank(entry);
	switch (rank) {
		case REP_HATED:
			out << "hated";
			break;
		case REP_HOSTILE:
			out << "hostile";
			break;
		case REP_UNFRIENDLY:
			out << "unfriendly";
			break;
		case REP_NEUTRAL:
			out << "neutral";
			break;
		case REP_FRIENDLY:
			out << "friendly";
			break;
		case REP_HONORED:
			out << "honored";
			break;
		case REP_REVERED:
			out << "revered";
			break;
		case REP_EXALTED:
			out << "exalted";
			break;
		default:
			out << "unknown";
			break;
	}

	int32 base = ReputationMgr::Reputation_Cap + 1;
	for (int i = MAX_REPUTATION_RANK - 1; i >= rank; --i)
		base -= ReputationMgr::PointsInRank[i];

	out << " (" << (reputation - base) << "/" << ReputationMgr::PointsInRank[rank] << ")";
	TellMaster(out.str().c_str());
}


void AiSocialManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "leave")
	{
		LeaveGroup();
	}
	if (text == "rep" || text == "reputation")
	{
		TellReputation();
	}
	else if (text.size() > 4 && text.substr(0, 4) == "log ")
	{
		string level = text.substr(text.find(" ") + 1);
		if (level == "?")
		{
			ostringstream out;
			out << "Log level: " << GetLogLevel(logLevel);
			TellMaster(out.str().c_str());
		}
		
		SetLogLevel(level);
	}
}

void AiSocialManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
		// If the leader role was given to the bot automatically give it to the master
		// if the master is in the group, otherwise leave group
	case SMSG_GROUP_SET_LEADER:
		{
			WorldPacket p(packet);
			std::string name;
			p >> name;
			if (bot->GetGroup() && name == bot->GetName())
			{
				if (bot->GetGroup()->IsMember(ai->GetMaster()->GetGUID()))
				{
					p.resize(8);
					p << ai->GetMaster()->GetGUID();
					bot->GetSession()->HandleGroupSetLeaderOpcode(p);
				}
			}
			return;
		}
	case SMSG_GROUP_INVITE:
		{
			AcceptInvitation();
			return;
		}

		// Handle when another player opens the trade window with the bot
		// also sends list of tradable items bot can trade if bot is allowed to obey commands from
    case BUY_ERR_NOT_ENOUGHT_MONEY:
        {
            TellMaster("Not enought money");
            return;
        }
    case BUY_ERR_ITEM_ALREADY_SOLD:
        {
            TellMaster("Item is already sold out");
            return;
        }
    case BUY_ERR_REPUTATION_REQUIRE:
        {
            TellMaster("Not enought reputation");
            return;
        }
    case BUY_ERR_CANT_FIND_ITEM:
        {
            TellMaster("Item not found");
            return;
        }
    }
}
