//
// Created by feanaro on 31/10/17.
//
#include "twamp_common_datatypes.h"
#include "twamp_utils.h"
#include <sys/time.h>
#include <stddef.h>
#include <memory.h>

struct Twamp_Timestamp twamp_utils_GetTime(void)
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    uint64_t msSinceEpoch = (currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000);

    struct Twamp_Timestamp retVal;
    retVal.seconds =  (msSinceEpoch / 1000) + TWAMP_BASE_TIME_OFFSET;
    retVal.fraction = (msSinceEpoch % 1000) + ( TWAMP_FLOAT_DENOM * 1000 );

    return retVal;
}

struct Twamp_MessageErrorEstimate twamp_utils_GetErrorEstimate(void)
{
    struct Twamp_MessageErrorEstimate errorEstimate;
    memset(&errorEstimate, 0, sizeof(errorEstimate));

    /* todo ... whatever is neeeded to calculate this */

    return errorEstimate;
}