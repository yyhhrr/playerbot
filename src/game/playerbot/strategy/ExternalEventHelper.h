#pragma once

#include "Trigger.h"

namespace ai
{
    class ExternalEventHelper {
    public:
        ExternalEventHelper(AiObjectContext* aiObjectContext) : aiObjectContext(aiObjectContext) {}

        void ParseChatCommand(string command) 
        {
            if (Check(command, ""))
                return;

            size_t i = string::npos;
            while (true)
            {
                size_t found = command.rfind(" ", i);
                if (found == string::npos)
                    break;

                string name = command.substr(0, found);
                string param = command.substr(found + 1);

                i = found - 1;

                if (Check(name, param))
                    break;
            }
        }

        void HandlePacket(map<uint16, string> &handlers, const WorldPacket &packet)
        {
            uint8 opcode = packet.GetOpcode();
            string name = handlers[packet.GetOpcode()];
            if (name.empty())
                return;

            Trigger* trigger = aiObjectContext->GetTrigger(name.c_str());
            if (!trigger)
                return;

            trigger->ExternalEvent(WorldPacket(packet));
        }

    private:
        bool Check(string name, string param)
        {
            Trigger* trigger = aiObjectContext->GetTrigger(name.c_str());
            if (!trigger)
                return false;

            trigger->ExternalEvent(param);
            return true;
        }

    private:
        AiObjectContext* aiObjectContext;
    };
}