#
#   Weather update server
#   Binds PUB socket to tcp://*:5556
#   Publishes random weather updates
#

import zmq
import time
from random import randrange

context = zmq.Context()
pub1 = context.socket(zmq.PUB)
pub1.connect("tcp://localhost:5566")

while True:

    pub1.send_string("Regards from SUB1")
    time.sleep(1)
