#pragma once
#include "Value.h"

namespace ai
{
    class ItemCountValue : public CalculatedValue<uint8>, public Qualified
	{
	public:
        ItemCountValue(AiManagerRegistry* const ai) : CalculatedValue<uint8>(ai) {}

    public:
        virtual uint8 Calculate();
	};
}
