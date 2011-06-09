#pragma once;

namespace ai
{
    template <class T> class NamedObjectFactoryBase
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


    template <class T> class NamedObjectFactory : public NamedObjectFactoryBase<T>
    {
    public:
        T* create(string name, AiManagerRegistry* ai)
        {
            T* result = created[name];
            if (result) 
                return result;

            return created[name] = NamedObjectFactoryBase<T>::create(name, ai);
        }

        virtual ~NamedObjectFactory()
        {
            for (map<string, T*>::iterator i = created.begin(); i != created.end(); i++)
                delete i->second;
            
            created.clear();
        }

    protected:
        map<string, T*> created;
    };

};