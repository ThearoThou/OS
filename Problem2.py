import threading
import time

# Semaphores with initial values
a = threading.Semaphore(1)  # Starts at 1 to allow Process 1 to begin
b = threading.Semaphore(0)
c = threading.Semaphore(0)

def process1():
    while True:
        a.acquire()  # wait(a)
        print("H", end='', flush=True)
        print("E", end='', flush=True)
        b.release()  # signal(b) twice for two "L"s
        b.release()

def process2():
    while True:
        b.acquire()  # wait(b)
        print("L", end='', flush=True)
        c.release()  # signal(c) after each "L"

def process3():
    while True:
        c.acquire()  # wait(c) twice to ensure after both "L"s
        c.acquire()
        print("O", end='', flush=True)

# Start threads
t1 = threading.Thread(target=process1)
t2 = threading.Thread(target=process2)
t3 = threading.Thread(target=process3)
t1.start()
t2.start()
t3.start()

time.sleep(1)  # Give time for the single "HELLO" to print; threads block afterward
# Expected output: HELLO (then nothing more)
