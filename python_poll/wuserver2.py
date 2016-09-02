#
#   Weather update server
#   Binds PUB socket to tcp://*:5556
#   Publishes random weather updates
#

import zmq
import time
from random import randrange

context = zmq.Context()

pub2 = context.socket(zmq.PUB)
pub2.connect("tcp://localhost:5577")

while True:

    pub2.send_string("Regards from SUB2")
    time.sleep(1)
