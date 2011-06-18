#include "../pchdef.h"
#include "playerbot.h"

vector<string>& split(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) 
{
    vector<string> elems;
    return split(s, delim, elems);
}


char * strstri (const char * str1, const char * str2)
{
    char *cp = (char *) str1;
    char *s1, *s2;

    if ( !*str2 )
        return((char *)str1);

    while (*cp)
    {
        s1 = cp;
        s2 = (char *) str2;

        while ( *s1 && *s2 && !(tolower(*s1)-tolower(*s2)) )
            s1++, s2++;

        if (!*s2)
            return(cp);

        cp++;
    }

    return(NULL);
}



uint64 extractGuid(WorldPacket& packet)
{
    uint8 mask;
    packet >> mask;
    uint64 guid = 0;
    uint8 bit = 0;
    uint8 testMask = 1;
    while (true)
    {
        if (mask & testMask)
        {
            uint8 word;
            packet >> word;
            guid += (word << bit);
        }
        if (bit == 7)
            break;
        ++bit;
        testMask <<= 1;
    }
    return guid;
}
