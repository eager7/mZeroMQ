#include <zmq.h>

#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define check_result(x) do{if(!(x)) {printf("error:%s\n", strerror(errno));exit(-1);}}while(0)

int main()
{
    printf("zmq poll client\n");
    
    void *context = zmq_ctx_new();

    void *pusher = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(pusher, "tcp://127.0.0.1:5557");
    
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://127.0.0.1:5556");

    printf("start send msg\n");
    for(int i = 0; i < 60; i++){
        printf("pusher\n");
        check_result(zmq_send(pusher, "pusher", sizeof("pusher"), 0) > 0);
        printf("publisher\n");
        check_result(zmq_send(publisher, "publisher", sizeof("publisher"), 0) > 0);
        sleep(1);
    }

    zmq_close(pusher);
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    
    return 0;
}

