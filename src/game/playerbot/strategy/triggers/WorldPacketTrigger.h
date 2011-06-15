#pragma once

#include "../Trigger.h"

namespace ai
{
    class WorldPacketTrigger : public Trigger {
    public:
        WorldPacketTrigger(PlayerbotAI* ai, string command) : Trigger(ai, command.c_str()), triggered(false) {}

        virtual void ExternalEvent(WorldPacket &packet) 
        {
            this->packet = packet;
            triggered = true;
        }

        virtual Event Check()
        {
            if (!triggered)
                return Event();

            triggered = false;
            return Event(getName(), packet);
        }

    private:
        WorldPacket packet;
        bool triggered;
    };
}