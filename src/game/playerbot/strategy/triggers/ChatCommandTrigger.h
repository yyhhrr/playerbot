#pragma once

#include "../Trigger.h"

namespace ai
{
    class ChatCommandTrigger : public Trigger {
    public:
        ChatCommandTrigger(PlayerbotAI* ai, string command) : Trigger(ai, command), triggered(false) {}

        virtual void ExternalEvent(string param) 
        {
            this->param = param;
            triggered = true;
        }

        virtual Event Check()
        {
            if (!triggered)
                return Event();

            triggered = false;
            return Event(getName(), param);
        }

    private:
        string param;
        bool triggered;
    };
}