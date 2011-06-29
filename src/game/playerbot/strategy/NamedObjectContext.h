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

    template <class T> class NamedObjectFactory
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

            if (creators.find(name) == creators.end())
                return NULL;

            ActionCreator creator = creators[name];
            if (!creator)
                return NULL;

            T *object = (*creator)(ai);
            Qualified *q = dynamic_cast<Qualified *>(object);
            if (q)
                q->Qualify(qualifier);

            return object;
        }

        set<string> supports()
        {
            set<string> keys;
            for (map<string, ActionCreator>::iterator it = creators.begin(); it != creators.end(); it++)
                keys.insert(it->first);
            return keys;
        }

    protected:
        typedef T* (*ActionCreator) (PlayerbotAI* ai);
        map<string, ActionCreator> creators;
    };


    template <class T> class NamedObjectContext : public NamedObjectFactory<T>
    {
    public:
        NamedObjectContext(bool shared = false, bool supportsSiblings = false) :
            NamedObjectFactory<T>(), shared(shared), supportsSiblings(supportsSiblings) {}

        T* create(string name, PlayerbotAI* ai)
        {
            if (created.find(name) == created.end())
                return created[name] = NamedObjectFactory<T>::create(name, ai);

            return created[name];
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
        bool IsSupportsSiblings() { return supportsSiblings; }

    protected:
        map<string, T*> created;
        bool shared;
        bool supportsSiblings;
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

        set<string> GetSiblings(string name)
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
            {
                if (!(*i)->IsSupportsSiblings())
                    continue;

                set<string> supported = (*i)->supports();
                set<string>::iterator found = supported.find(name);
                if (found == supported.end())
                    continue;

                supported.erase(found);
                return supported;
            }

            return set<string>();
        }

    private:
        list<NamedObjectContext<T>*> contexts;
    };

    template <class T> class NamedObjectFactoryList
    {
    public:
        virtual ~NamedObjectFactoryList()
        {
            for (list<NamedObjectFactory<T>*>::iterator i = factories.begin(); i != factories.end(); i++)
                delete *i;
        }

        void Add(NamedObjectFactory<T>* context)
        {
            factories.push_back(context);
        }

        T* GetObject(string name, PlayerbotAI* ai)
        {
            for (list<NamedObjectFactory<T>*>::iterator i = factories.begin(); i != factories.end(); i++)
            {
                T* object = (*i)->create(name, ai);
                if (object) return object;
            }
            return NULL;
        }

    private:
        list<NamedObjectFactory<T>*> factories;
    };
};
