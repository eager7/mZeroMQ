#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://127.0.0.1:5559");

    for (int i = 0; i < 10; ++i) {
        s_send(requester, "hello");
        char *string = s_recv(requester);
        printf("recv:%s\n", string);
        free(string);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);

    return 0;
}