#ifndef TWAMP_DATATYPES_H
#define TWAMP_DATATYPES_H

#include <stdint.h>

#define TWAMP_BASE_TIME_OFFSET 2208988800u
#define TWAMP_FLOAT_DENOM 4294.967296

#pragma pack(push,1)

struct Twamp_RawPacket
{
    uint8_t* data;
    uint32_t size;
};

struct Twamp_Timestamp
{
    uint32_t seconds;
    uint32_t fraction;
};

struct Twamp_TestPacket
{
    struct Twamp_RawPacket rawPacket;
    struct Twamp_Timestamp receivedTimestamp;
};

struct Twamp_MessageErrorEstimate
{
    uint8_t s:1;
    uint8_t z:1;
    uint8_t scale:6;
    uint8_t multiplier;
};


struct Twamp_MessageTestUnauthenticated
{
    uint32_t sequenceNumber;
    struct Twamp_Timestamp timestamp;
    struct Twamp_MessageErrorEstimate errorEstimate;
};

struct Twamp_MessageReflectorUnAuthenticated
{
    uint32_t sequenceNumber;
    struct Twamp_Timestamp timestamp;
    struct Twamp_MessageErrorEstimate errorEstimate;
    uint8_t mbz[2];
    struct Twamp_Timestamp receiveTimestamp;
    uint32_t senderSequenceNumber;
    struct Twamp_Timestamp senderTimestamp;
    struct Twamp_MessageErrorEstimage senderErrorEstimate;
    uint8_t mbz_[2];
    uint8_t senderTTL;
};

#pragma pack(pop)



#endif //TWAMP_DATATYPES_H
