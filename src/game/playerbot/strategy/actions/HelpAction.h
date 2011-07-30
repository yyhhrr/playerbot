#pragma once

#include "../Action.h"

namespace ai
{
    class HelpAction : public Action {
    public:
        HelpAction(PlayerbotAI* ai);
        virtual ~HelpAction();
        virtual bool Execute(Event event);

    private:
        NamedObjectContext<Action>* ctx;
    };

}
