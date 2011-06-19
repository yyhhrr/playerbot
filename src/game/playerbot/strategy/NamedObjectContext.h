#pragma once;

namespace ai
{
    class Qualified
    {
    public:
        Qualified() {};

    public:
        void Qualify(string qualifier) { this->qualifier = qualifier; }

    protected:
        string qualifier;
    };

    template <class T> class NamedObjectContextBase
    {
    public:
        T* create(string name, PlayerbotAI* ai)
        {
            size_t found = name.find("::");
            string qualifier;
            if (found != string::npos)
            {
                qualifier = name.substr(found + 2);
                name = name.substr(0, found);
            }

            ActionCreator creator = creators[name];
            if (!creator)
                return NULL;

            T *object = (*creator)(ai);
            Qualified *q = dynamic_cast<Qualified *>(object);
            if (q)
                q->Qualify(qualifier);

            return object;
        }

    protected:
        typedef T* (*ActionCreator) (PlayerbotAI* ai);
        map<string, ActionCreator> creators;
    };


    template <class T> class NamedObjectContext : public NamedObjectContextBase<T>
    {
    public:
        NamedObjectContext() : NamedObjectContextBase<T>(), shared(false) {}
        NamedObjectContext(bool shared) : NamedObjectContextBase<T>(), shared(shared) {}

        T* create(string name, PlayerbotAI* ai)
        {
            T* result = created[name];
            if (result) 
                return result;

            return created[name] = NamedObjectContextBase<T>::create(name, ai);
        }

        virtual ~NamedObjectContext()
        {
            for (map<string, T*>::iterator i = created.begin(); i != created.end(); i++)
            {
                if (i->second)
                    delete i->second;
            }
            
            created.clear();
        }

        void Update()
        {
            for (map<string, T*>::iterator i = created.begin(); i != created.end(); i++)
            {
                if (i->second)
                    i->second->Update();
            }
        }

        bool IsShared() { return shared; }

    protected:
        map<string, T*> created;
        bool shared;
    };

    template <class T> class NamedObjectContextList
    {
    public:
        virtual ~NamedObjectContextList()
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
            {
                NamedObjectContext<T>* context = *i;
                if (!context->IsShared())
                    delete context;
            }
        }

        void Add(NamedObjectContext<T>* context)
        {
            contexts.push_back(context);
        }

        T* GetObject(string name, PlayerbotAI* ai)
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
            {
                T* object = (*i)->create(name, ai);
                if (object) return object;
            }
            return NULL;
        }

        void Update()
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
            {
                if (!(*i)->IsShared())
                    (*i)->Update();
            }
        }

    private:
        list<NamedObjectContext<T>*> contexts;
    };
};