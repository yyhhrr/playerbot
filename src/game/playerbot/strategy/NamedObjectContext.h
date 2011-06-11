#pragma once;

namespace ai
{
    template <class T> class NamedObjectContextBase
    {
    public:
        T* create(string name, AiManagerRegistry* ai)
        {
            ActionCreator creator = creators[name];
            if (!creator)
                return NULL;

            return (*creator)(ai);
        }

    protected:
        typedef T* (*ActionCreator) (AiManagerRegistry* ai);
        map<string, ActionCreator> creators;
    };


    template <class T> class NamedObjectContext : public NamedObjectContextBase<T>
    {
    public:
        T* create(string name, AiManagerRegistry* ai)
        {
            T* result = created[name];
            if (result) 
                return result;

            return created[name] = NamedObjectContextBase<T>::create(name, ai);
        }

        virtual ~NamedObjectContext()
        {
            for (map<string, T*>::iterator i = created.begin(); i != created.end(); i++)
                delete i->second;
            
            created.clear();
        }

    protected:
        map<string, T*> created;
    };

    template <class T> class NamedObjectContextList
    {
    public:
        virtual ~NamedObjectContextList()
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
                delete *i;
        }

        void Add(NamedObjectContext<T>* context)
        {
            contexts.push_back(context);
        }

        T* GetObject(const char* name, AiManagerRegistry* const ai)
        {
            for (list<NamedObjectContext<T>*>::iterator i = contexts.begin(); i != contexts.end(); i++)
            {
                T* object = (*i)->create(name, ai);
                if (object) return object;
            }
            return NULL;
        }

    private:
        list<NamedObjectContext<T>*> contexts;
    };
};