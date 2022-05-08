from concurrent.futures import thread
from multiprocessing.dummy import JoinableQueue
from queue import Queue
import threading
import time

class Producer(threading.Thread):
    def __init__(self, threadName, que):
        super().__init__(name = threadName)
        self._que = que
        self._is_end = False


    def run(self):
        for i in range(1000):
            print("product ", i);
            self._que.put(i)
        self._que.join()


class Consumer(threading.Thread):
    def __init__(self, threadName, que):
        super().__init__(name = threadName)
        self._que = que
        self._name = threadName

    def run(self):
        while True:
            val = self._que.get()
            print("-----cosumer {0}, getval = {1}".format(self._name, val));
            self._que.task_done()


if __name__ == '__main__':
    que = JoinableQueue()
    producer_list = []
    for i in range(3):
        producer = Producer("producer", que)
        producer_list.append(producer)
    consumer_list = []
    for i in range(10):
        consumer_list.append(Consumer("consumer " + str(i), que))
    
    for producer in producer_list:
        producer.start()
    for consumer in consumer_list:
        consumer.setDaemon(True)
        consumer.start()
    for producer in producer_list:
        producer.join()
