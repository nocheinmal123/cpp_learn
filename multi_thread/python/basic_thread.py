from concurrent.futures import thread
import threading
import time
from tracemalloc import start

def run():
    time.sleep(10)
    with open("/home/nio/private/cpp_learn/multi_thread/in.txt", "a") as _file:
        _file.write(str(1) + "\n")


# # 计时针对的是主线程，主线程结束，计时随之结束，打印出主线程的用时
# # 主线程的任务完成之后，子线程继续执行自己的任务，直到全部的子线程任务全部结束
# if __name__ == '__main__':
#     start_time = time.time()

#     print("this is main thread: ",threading.current_thread().name)

#     thread_list = []
#     for i in range(5):
#         t = threading.Thread(target = run)
#         thread_list.append(t)

#     for t in thread_list:
#         t.start()

#     print("main thread end ", threading.current_thread().name)
#     print("total time ", time.time() - start_time)

'''
#设置守护线程，主线程执行完毕，子线程还没来得及执行，立马也就随之结束了
if __name__ == '__main__':
    start_time = time.time()

    print("this is main thread:", threading.current_thread().name)
    thread_list = []
    for i in range(5):
        t = threading.Thread(target = run)
        thread_list.append(t)
 
    for t in thread_list:
        t.setDaemon(True)
        t.start()


    print("main thread ends ", threading.current_thread().name)
    print("total time ", time.time() - start_time)
'''


#join的作用

if __name__ == '__main__':
    start_time = time.time()

    print("this is main thread: ", threading.current_thread().name)
    thread_list = []
    for i in range(5):
        t = threading.Thread(target = run)
        thread_list.append(t)

    for t in thread_list:
        t.setDaemon(True)
        t.start()

    # for t in thread_list:
    #     t.join()

    print("main thread ends ", threading.current_thread().name)
    print("total time ", time.time() - start_time)