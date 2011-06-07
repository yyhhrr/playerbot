#pragma once;

namespace ai
{

template <class T, class TThis> class NamedObjectFactory
{
public:
    T* create(string name, AiManagerRegistry* ai)
    {
        ActionCreator creator = creators[name];
        return creator ? (((TThis*)this)->*creator)(ai) : NULL;
    }

protected:
    typedef T* (TThis::*ActionCreator) (AiManagerRegistry* ai);
    map<string, ActionCreator> creators;
};

};