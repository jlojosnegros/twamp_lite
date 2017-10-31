#include <assert.h>
//#include <libc.h>
#include <stdio.h>
#include <nn.h>
#include <reqrep.h>

#include "twamp_lite_unauthenticated.h"
#include "twamp_utils.h"
#include "twamp_alloc.h"

int server (const char *url)
{
    int sock = nn_socket (AF_SP, NN_REP);
    assert (sock >= 0);
//    int ret = nn_bind (sock, url);
//    printf ("server: bind %d\n", ret);
    assert (nn_bind (sock, url) >= 0);
    while (1)
    {
        printf ("server: waiting for incoming message ... \n");
        uint8_t *buf = NULL;
        int bytes = nn_recv (sock, &buf, NN_MSG, 0);
        assert (bytes >= 0);
        printf ("server: RECEIVED \"%d\"\n", bytes);

        struct Twamp_TestPacket packet;
        packet.rawPacket.data = buf;
        packet.rawPacket.size = (uint32_t) bytes;
        packet.receivedTimestamp = twamp_utils_GetTime();

        struct Twamp_RawPacket* response = Twamp_lite_unauthenticated_HandleTestPacket(&packet);
        if ( NULL == response)
        {
            printf ("server: ERROR while handling Test packet\n");
        }
        else
        {
            printf ("server: Sending response %d...\n", response->size);
            int bytes = nn_send(sock, response->data, response->size, 0);
            printf ("server: sended %d bytes ...\n", bytes);
            assert(bytes == response->size);
            //twamp_free(response);
        }

        nn_freemsg (buf);
    }
    return nn_shutdown (sock, 0);
}

int main (const int argc, const char **argv)
{
    if (argc > 1)
    {
        return server(argv[1]);
    }
    else
    {
        fprintf (stderr, "Usage: twamp_server <URL> ...\n");
        return 1;
    }
}