#include "qkioEvent.h"


namespace qk::io
{
    uint32_t EventHeader::hash() const
    {
        uint32_t value;
        std::memcpy(&value, this, sizeof(value));
        return value;
    }
}