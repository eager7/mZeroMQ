#!/bin/env python

import zmq, time


if __name__ == '__main__':
	print "pub program"
	context = zmq.Context()
	publisher = context.socket(zmq.PUB)
	publisher.bind("tcp://127.0.0.1:5555")

	publisher.send_string("publisher message")
	time.sleep(1)
	publisher.send_string("publisher message")
	time.sleep(1)


	