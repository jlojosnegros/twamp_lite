#include <assert.h>
//#include <libc.h>
#include <stdio.h>
#include <nn.h>
#include <reqrep.h>
#include <stdlib.h>


#include "twamp_common_datatypes.h"
#include "twamp_network.h"
#include "twamp_utils.h"


int client (const char *url, uint32_t seqNumber)
{
    uint8_t* buf = NULL;

    int sock = nn_socket (AF_SP, NN_REQ);
    assert (sock >= 0);
    assert (nn_connect (sock, url) >= 0);
    printf ("client: connected \n");


    struct Twamp_MessageTestUnauthenticated message;
    message.sequenceNumber = hton(seqNumber);
    message.errorEstimate = twamp_utils_GetErrorEstimate();

    struct Twamp_Timestamp now = twamp_utils_GetTime();
    message.timestamp.seconds = hton(now.seconds);
    message.timestamp.fraction = hton(now.fraction);

    printf ("client: sending ...\n");
    int bytes = nn_send(sock, (uint8_t*)&message, sizeof(struct Twamp_MessageTestUnauthenticated), 0);
    printf ("client: sent \"%d\" bytes\n", bytes);
    assert(bytes == sizeof(struct Twamp_MessageTestUnauthenticated));

    printf ("client: waiting for response ...\n");
    bytes = nn_recv(sock, &buf, NN_MSG,0);
    printf ("client: recaived \"%d\" bytes as response\n", bytes);
    assert(bytes >= 0);

    nn_freemsg(buf);


    return nn_shutdown(sock, 0);
}

int main (const int argc, const char **argv)
{
    if (argc > 2)
    {
        return client(argv[1], atoi(argv[2]));
    }
    else
    {
        fprintf (stderr, "Usage: twamp_client <URL> <SEQ_NUMBER>...\n");
        return 1;
    }
}