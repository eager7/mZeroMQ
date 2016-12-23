#!/bin/env python

import zmq, time


if __name__ == '__main__':
	print "sub program"
	context = zmq.Context()
	subscriber = context.socket(zmq.SUB)
	subscriber.connect("tcp://127.0.0.1:7788")
	subscriber.setsockopt(zmq.SUBSCRIBE, '')
	
	while True:
		print subscriber.recv_string()