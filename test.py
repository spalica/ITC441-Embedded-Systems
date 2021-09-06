from threading import Thread
from time import sleep
 
# function to create threads
def threaded_function(arg):
    for i in range(arg):
        print("running")
         
        # wait 1 sec in between each thread
        sleep(1)
 
 
if __name__ == "__main__":
    thread = Thread(target = threaded_function, args = (10, ))
    thread.start()
    print("hi")
    sleep(4)
    print('hi')
    thread.join()
    print("thread finished...exiting")