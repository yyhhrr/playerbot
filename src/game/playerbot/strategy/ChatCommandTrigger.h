#pragma once

#include "Trigger.h"

namespace ai
{
    class ChatCommandTrigger : public Trigger {
    public:
        ChatCommandTrigger(AiManagerRegistry* const ai, string command) : Trigger(ai, command.c_str()), triggered(false) {}

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