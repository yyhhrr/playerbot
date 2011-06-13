#pragma once

namespace ai
{
    class Event
	{
	public:
        Event(Event &other) 
        {
            source = other.source;
            param = other.param;
            packet = other.packet;
        }
        Event() {}
        Event(string source) : source(source) {}
        Event(string source, string param) : source(source), param(param) {}
        Event(string source, WorldPacket &packet) : source(source), packet(packet) {}
        Event(string source, ObjectGuid &object) : source(source), object(object) {}
        virtual ~Event() {}

	public:
        string getSource() { return source; }
        string getParam() { return param; }
        WorldPacket& getPacket() { return packet; }
        ObjectGuid& getObject() { return object; }
        bool operator! () const { return source.empty(); }

    protected:
        string source;
        string param;
        WorldPacket packet;
        ObjectGuid object;
	};
}
