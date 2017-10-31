//
// Created by feanaro on 31/10/17.
//

#ifndef TWAMP_TWAMP_LITE_UNAUTHENTICATED_H
#define TWAMP_TWAMP_LITE_UNAUTHENTICATED_H

#include "twamp_common_datatypes.h"

struct Twamp_RawPacket* Twamp_lite_unauthenticated_HandleTestPacket(struct Twamp_TestPacket* testPacket);
struct Twamp_MessageReflectorUnAuthenticated*
Twamp_lite_unauthenticated_DecodeTestMessage(struct Twamp_MessageTestUnauthenticated* messageTestUnauthenticated
        , struct Twamp_Timestamp* receivedTimestamp);

#endif //TWAMP_TWAMP_LITE_UNAUTHENTICATED_H
