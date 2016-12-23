#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int main(void)
{   
    void * context = zmq_ctx_new();
    void *puller = zmq_socket(context, ZMQ_PULL);
    zmq_bind(puller, "tcp://127.0.0.1:5556");

    while(1)
    {
        sleep(1);
        printf("recv...\n");
        zmq_msg_t request;
        zmq_msg_init(&request);
        int size = zmq_msg_recv(&request, puller, 0);
        char *string = malloc(size +1);
        memcpy(string, zmq_msg_data(&request), size);
        string[size] = 0;
        printf("recv:%s\n", string);
        zmq_msg_close(&request);
    }
    zmq_close(puller);
    zmq_ctx_destroy(context);
    
    return 0;
}


