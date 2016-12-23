//
// Created by pct on 9/1/16.
//

#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *router = zmq_socket(context, ZMQ_ROUTER);
    void *dealer = zmq_socket(context, ZMQ_DEALER);
    int ret = zmq_bind(router, "tcp://127.0.0.1:5559");
    assert(ret == 0);
    ret = zmq_bind(dealer, "tcp://127.0.0.1:5560");
    assert(ret == 0);

    zmq_proxy(router, dealer, NULL);

    zmq_close(router);
    zmq_close(dealer);
    zmq_ctx_destroy(context);

    return 0;
}