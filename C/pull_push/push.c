#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{	
	void * context_r = zmq_ctx_new();
	void *pusher = zmq_socket(context_r, ZMQ_PUSH);
	zmq_connect(pusher, "tcp://127.0.0.1:5556");

    while(1)
    {
		sleep(1);
		printf("send...\n");
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, sizeof("pusher"));
		memcpy(zmq_msg_data(&reply), "pusher", sizeof("pusher"));
		zmq_msg_send(&reply, pusher, 0);
		zmq_msg_close(&reply);
    }
	zmq_close(pusher);
	zmq_ctx_destroy(context_r);
	
	return 0;
}

