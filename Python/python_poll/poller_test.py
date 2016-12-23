import zmq
import sys
import time

TIMEOUT = 5000

def main():
    ctx = zmq.Context()

    sub1 = ctx.socket(zmq.SUB)
    sub1.bind('tcp://*:5566') 
    sub1.setsockopt(zmq.SUBSCRIBE, '')

    sub2= ctx.socket(zmq.SUB)
    sub2.bind('tcp://*:5577') 
    sub2.setsockopt(zmq.SUBSCRIBE, '')

    poller = zmq.Poller()
    poller.register(sub1, zmq.POLLIN)
    poller.register(sub2, zmq.POLLIN)

    while(True):
        
        socks = dict(poller.poll())
#        if socks.get(sub1) == zmq.POLLIN:
        if sub1 in socks:
            print 'sub1 get event'
            recv1 = sub1.recv()
            print('MSG at SUB1! Reads: ' + recv1)
        else:
            print('sub1 no event')
        
#        if socks.get(sub2) == zmq.POLLIN:
        if sub2 in socks:
            print 'sub1 get event'
            recv2 = sub2.recv()
            print('MSG at SUB2! Reads: ' + recv2)
        else:
            print('sub2 no event')
        
        time.sleep(1)
    
if __name__ == "__main__":
    main()
