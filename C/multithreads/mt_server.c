#include "zhelpers.h"
#include <pthread.h>
#include <unistd.h>

static void *work_thread(void *context){
    void *receiver = zmq_socket(context, ZMQ_REP);
    int ret = zmq_connect(receiver, "inproc://worker");
    assert(ret == 0);

    printf("start thread[%ld]\n", pthread_self());
    while (1){
        char *string = s_recv(receiver);
        printf("recv[%ld]:%s\n", pthread_self(), string);

        sleep(1);

        s_send(receiver, "World");
    }
    zmq_close(receiver);
    return NULL;
}


int main()
{
    void *context = zmq_ctx_new();

    void *client = zmq_socket(context, ZMQ_ROUTER);
    int ret = zmq_bind(client, "tcp://127.0.0.1:5555");
    assert(ret == 0);

    void *workers = zmq_socket(context, ZMQ_DEALER);
    ret = zmq_bind(workers, "inproc://worker");
    assert(ret == 0);

    for (int i = 0; i < 5; ++i) {
        pthread_t worker;
        pthread_create(&worker, NULL, work_thread, context);
    }

    zmq_proxy(client, workers, NULL);

    zmq_close(client);
    zmq_close(workers);
    zmq_ctx_destroy(context);

    return 0;
}