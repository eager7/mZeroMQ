#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *router = zmq_socket(context, ZMQ_ROUTER);
    void *dealer = zmq_socket(context, ZMQ_DEALER);
    zmq_bind(router, "tcp://127.0.0.1:5559");
    zmq_bind(dealer, "tcp://127.0.0.1:5560");

    zmq_pollitem_t items[] = {
            {router, 0, ZMQ_POLLIN, 0},
            {dealer, 0, ZMQ_POLLIN, 0},
    };

    while (1) {
        zmq_msg_t message;
        int more;
        size_t more_size = sizeof(more);

        zmq_poll(items, 2, -1);
        printf("poll events [%d-%d]\n", items[0].events, items[1].events);
        if(items[0].events & ZMQ_POLLIN){
            printf("router receive data\n");
            while (1){
                zmq_msg_init(&message);
                zmq_msg_recv(&message, router, 0);
                zmq_getsockopt(router, ZMQ_RCVMORE, &more, &more_size);
                zmq_msg_send(&message, dealer, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&message);
                if(!more){
                    break;
                }
            }
            printf("router send ok\n");
        }
        if(items[1].events & ZMQ_POLLIN){
            printf("dealer receive data\n");
            while (1) {
                zmq_msg_init(&message);
                zmq_msg_recv(&message, dealer, 0);
                zmq_getsockopt(router, ZMQ_RCVMORE, &more, &more_size);
                zmq_msg_send(&message, router, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&message);
                if (!more) {
                    break;
                }
            }
        }
    }
    zmq_close(router);
    zmq_close(dealer);
    zmq_ctx_destroy(context);

    return 0;
}