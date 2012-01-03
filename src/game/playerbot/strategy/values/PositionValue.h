#pragma once
#include "../Value.h"

namespace ai
{
    class Position
    {
    public:
        Position() : isset(false) {}
        void Set(double x, double y, double z) { this->x = x; this->y = y; this->z = z; this->isset = true; }
        void Reset() { isset = false; }
        bool isSet() { return isset; }

        double x, y, z;
        bool isset;
    };

    class PositionValue : public ManualSetValue<Position&>, public Qualified
	{
	public:
        PositionValue(PlayerbotAI* ai);

	private:
        Position position;
    };
}
