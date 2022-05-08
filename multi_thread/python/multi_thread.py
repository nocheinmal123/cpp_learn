from multiprocessing.dummy import JoinableQueue
from queue import Queue
import threading

que = JoinableQueue()


class ThreadTest:
    def Init(self):
        for i in range(100):
            que.put(i)


    def work(self):
        print("current thread: ", threading.current_thread().name)
        while que.empty() == False:
            print("current thread: ", threading.current_thread().name)
            if que.empty():
                break
            val = que.get()
            print("val = {0}, que.empty() = {1}".format(val, que.empty()))

    def Func(self):
        self.Init()
        thread_list = []
        for i in range(3):
            t = threading.Thread(target = self.work)
            thread_list.append(t)
        for t in thread_list:
            t.start()
        for t in thread_list:
            t.join()




if __name__ == '__main__':
    sample = ThreadTest()
    sample.Func()

