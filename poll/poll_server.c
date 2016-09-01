#include <zmq.h>

#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define check_result(x) do{if(!(x)) {printf("chekc error:%s\n", strerror(errno));exit(-1);}}while(0)

int main(void)
{
    printf("zmq poll server\n");

    char recv_buf[2048] = {0};
    void *context = zmq_ctx_new();

    void *puller = zmq_socket(context, ZMQ_PULL);
    zmq_connect(puller, "tcp://127.0.0.1:5557");

    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://127.0.0.1:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, 0, 0);

    zmq_pollitem_t items[] = {
        {puller, 0, ZMQ_POLLIN, 0},
        {subscriber, 0, ZMQ_POLLIN, 0}
    };

    int len = sizeof(items)/sizeof(zmq_pollitem_t);
    for(int n = 0; n < 100; n++){
        printf("waiting...\n");
        int result = zmq_poll(items, len, -1);
        switch(result){
            case 0:
                printf("time out\n");
            break;
            case -1:
                printf("error:%s\n", strerror(errno));
            break;
            default:{
                printf("event[%d][%d]\n", items[0].events, items[1].events);
                for(int i = 0; i < len; i++){
                    if(items[i].events & ZMQ_POLLIN){
                        printf("get event[%d]\n", i);
                        int ret = zmq_recv(items[i].socket, recv_buf, sizeof(recv_buf), ZMQ_DONTWAIT);
                        if(ret > 0){
                            printf("message:%s\n", recv_buf);
                        }
                    }
                }
            }
        }
    }
    
    zmq_close(puller);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    
    return 0;
}








