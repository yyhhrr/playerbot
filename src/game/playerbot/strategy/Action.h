#pragma once
#include "Event.h"

namespace ai
{
    class NextAction
    {
    public:
        NextAction(const char* name, float relevance = 0.0f)
        {
            this->name = name;
            this->relevance = relevance;
        }
        NextAction(const NextAction& o)
        {
            this->name = o.name;
            this->relevance = o.relevance;
        }

    public:
        const char* getName() { return name.c_str(); }
        float getRelevance() {return relevance;}

    public:
        static int size(NextAction** actions);
        static NextAction** clone(NextAction** actions);
        static NextAction** merge(NextAction** what, NextAction** with);
        static NextAction** array(uint8 nil,...);
        static void destroy(NextAction** actions);

    private:
        float relevance;
        std::string name;
    };
    
    //---------------------------------------------------------------------------------------------------------------------
    
    class ActionBasket;

    class Action : public AiManagerRegistryAware
	{
	public:
        Action(AiManagerRegistry* const ai, const char* name = NULL) : AiManagerRegistryAware(ai) {
            this->name = name;
        }
        virtual ~Action(void) {}

    public:
        virtual bool ExecuteResult() { Execute(); return true; }
        virtual bool Execute(Event event) { return ExecuteResult(); }
        virtual void Execute() { }
        virtual bool isPossible() { return true; }
        virtual bool isUseful() { return true; }
        virtual NextAction** getPrerequisites() { return NULL; }
        virtual NextAction** getAlternatives() { return NULL; }
        virtual NextAction** getContinuers() { return NULL; }
        virtual const char* getName() { return !name ? "action" : name; }
        virtual int getKind() { return 0; }

    protected:
        Player* GetBot();
        void TellMaster(ostringstream &stream) { TellMaster(stream.str().c_str()); }
        void TellMaster(string &text) { TellMaster(text.c_str()); }
        void TellMaster(const char* text) { ai->GetSocialManager()->TellMaster(text); }

    protected:
        const char* name;
	};

    class ActionNode
    {
    public:
        ActionNode(const char* name, NextAction** prerequisites = NULL, NextAction** alternatives = NULL, NextAction** continuers = NULL)
        {
            this->action = NULL; 
            this->name = name;
            this->prerequisites = prerequisites;
            this->alternatives = alternatives;
            this->continuers = continuers;
        }
        virtual ~ActionNode() 
        { 
            NextAction::destroy(prerequisites); 
            NextAction::destroy(alternatives); 
            NextAction::destroy(continuers); 
        }

    public:
        Action* getAction() { return action; }
        void setAction(Action* action) { this->action = action; }
        const char* getName() { return name.c_str(); }

    public:
        NextAction** getContinuers() { return NextAction::merge(NextAction::clone(continuers), action->getContinuers()); }
        NextAction** getAlternatives() { return NextAction::merge(NextAction::clone(alternatives), action->getAlternatives()); }
        NextAction** getPrerequisites() { return NextAction::merge(NextAction::clone(prerequisites), action->getPrerequisites()); }

    private:
        string name;
        Action* action;
        NextAction** continuers;
        NextAction** alternatives;
        NextAction** prerequisites;
    };

    //---------------------------------------------------------------------------------------------------------------------

	class ActionBasket
	{
	public:
        ActionBasket(ActionNode* action, float relevance, bool skipPrerequisites, Event event) : 
          action(action), relevance(relevance), skipPrerequisites(skipPrerequisites), event(event) {}
        virtual ~ActionBasket(void) {}
	public:
		float getRelevance() {return relevance;}
		ActionNode* getAction() {return action;}
        Event getEvent() { return event; }
        bool isSkipPrerequisites() { return skipPrerequisites; }
        void AmendRelevance(float k) {relevance *= k; }
        void setRelevance(float relevance) { this->relevance = relevance; }
	private:
		ActionNode* action;
		float relevance;
        bool skipPrerequisites;
        Event event;
	};

    //---------------------------------------------------------------------------------------------------------------------
    
   
}
