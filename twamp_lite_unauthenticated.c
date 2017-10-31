//
// Created by feanaro on 31/10/17.
//

#include "twamp_lite_unauthenticated.h"
#include "twamp_utils.h"
#include "twamp_network.h"
#include "twamp_alloc.h"

#include <assert.h>

struct Twamp_RawPacket* Twamp_lite_unauthenticated_HandleTestPacket(struct Twamp_TestPacket* testPacket)
{
    assert(NULL != testPacket);
    assert(NULL != testPacket->rawPacket.data);
    assert(0 < testPacket->rawPacket.size);


    uint32_t padding = 0;
    if (testPacket->rawPacket.size > (uint32_t) sizeof(struct Twamp_MessageReflectorUnAuthenticated))
    {
        padding = testPacket->rawPacket.size - (uint32_t) sizeof(struct Twamp_MessageReflectorUnAuthenticated);
    }

    struct Twamp_MessageReflectorUnAuthenticated* response = Twamp_lite_unauthenticated_DecodeTestMessage(
            (struct Twamp_MessageTestUnauthenticated*)testPacket->rawPacket.data
            , &(testPacket->receivedTimestamp)
    );
    if (NULL == response)
    {
        goto error;
    }

    struct Twamp_RawPacket* rawResponse = twamp_malloc(sizeof(struct Twamp_RawPacket));
    if (NULL == rawResponse)
    {
        goto error_noRawResponse;
    }

    const uint32_t rawResponseSize = sizeof(struct Twamp_MessageReflectorUnAuthenticated) + padding;
    rawResponse->data = twamp_malloc(rawResponseSize);
    if ( NULL == rawResponse->data)
    {
        goto error_noRawResponseData;
    }

    rawResponse->size = rawResponseSize;

    memcpy(rawResponse->data, response, sizeof(*response));
    twamp_free(respose);

    return rawResponse;

error_noRawResponseData:
    twamp_free(rawResponse);

error_noRawResponse:
    twamp_free(response);

error:
    return NULL;

}

struct Twamp_MessageReflectorUnAuthenticated*
Twamp_lite_unauthenticated_DecodeTestMessage(struct Twamp_MessageTestUnauthenticated* messageTestUnauthenticated
                                           , struct Twamp_Timestamp* receivedTimestamp)
{
    assert(NULL != messageTestUnauthenticated);
    assert(NULL != receivedTimestamp);

    struct Twamp_MessageReflectorUnAuthenticated* messageReflectorUnAuthenticated = twamp_malloc(sizeof(struct Twamp_MessageTestUnauthenticated));
    if ( NULL == messageReflectorUnAuthenticated)
    {
        return NULL;
    }
    memset(messageReflectorUnAuthenticated, 0, sizeof(messageReflectorUnAuthenticated));

    struct Twamp_Timestamp timeReflected = twamp_utils_GetTime();
    /* timestamps */
    messageReflectorUnAuthenticated->timestamp.seconds = hton(timeReflected.seconds);
    messageReflectorUnAuthenticated->timestamp.fraction = hton(timeReflected.fraction);
    messageReflectorUnAuthenticated->receiveTimestamp.seconds = hton(receivedTimestamp->seconds);
    messageReflectorUnAuthenticated->receiveTimestamp.fraction = hton(receivedTimestamp->fraction);
    /* data from the incoming message */
    messageReflectorUnAuthenticated->sequenceNumber = messageTestUnauthenticated.sequenceNumber;
    messageReflectorUnAuthenticated->senderSequenceNumber = messageTestUnauthenticated.sequenceNumber;
    messageReflectorUnAuthenticated->senderTTL = 255; /* by definition */
    messageReflectorUnAuthenticated->senderTimestamp.seconds = messageTestUnauthenticated.timestamp.seconds;
    messageReflectorUnAuthenticated->senderTimestamp.fraction = messageTestUnauthenticated.timestamp.fraction;
    messageReflectorUnAuthenticated->senderErrorEstimate = messageTestUnauthenticated.errorEstimate;
    messageReflectorUnAuthenticated->errorEstimate = hton(twamp_utils_GetErrorEstimate());

    return messageReflectorUnAuthenticated;
}