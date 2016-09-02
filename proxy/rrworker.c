#include "zhelpers.h"
#include "unistd.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://127.0.0.1:5560");

    while (1) {
        char *string = s_recv(requester);
        printf("recv:%s\n", string);
        free(string);

        sleep(1);

        s_send(requester, "world");
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);

    return 0;
}