

#ifndef TWAMP_TWAMP_NETWORK_H
#define TWAMP_TWAMP_NETWORK_H

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#define ntoh(X) _Generic((X), int16_t: ntohs, uint16_t: ntohs, int32_t: ntohl, uint32_t: ntohl)(X)
#define hton(X) _Generic((X), int16_t: ntohs, uint16_t: htons, int32_t: ntohl, uint32_t: htonl)(X)

#endif //TWAMP_TWAMP_NETWORK_H
