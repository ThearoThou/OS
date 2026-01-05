import threading
import time
import random
from collections import deque
from threading import Semaphore

BUFFER_SIZE = 100
buffer = deque(maxlen=BUFFER_SIZE)

mutex = Semaphore(1)
empty_slots = Semaphore(98)
pairs_ready = Semaphore(0)

def producer(name):
    while True:
        time.sleep(random.uniform(0.3, 1.0))
        p1, p2 = f"{name}-A", f"{name}-B"

        empty_slots.acquire()
        empty_slots.acquire()

        with mutex:
            buffer.append(p1)
            buffer.append(p2)
            print(f"[{name}] placed pair ({p1}, {p2})  size={len(buffer)}")

        pairs_ready.release()

def consumer():
    while True:
        pairs_ready.acquire()

        with mutex:
            p1 = buffer.popleft()
            p2 = buffer.popleft()
            print(f"[Consumer] took ({p1}, {p2})  size={len(buffer)}")

        empty_slots.release()
        empty_slots.release()

        time.sleep(random.uniform(0.5, 1.2))
        print(f"shipped ({p1}, {p2})\n")   # FIXED - no arrow

if __name__ == "__main__":
    print("=== Problem 1: Entangled Particle Pairs Simulation ===\n")

    for i in range(1, 4):
        threading.Thread(target=producer, args=(f"P{i}",), daemon=True).start()

    threading.Thread(target=consumer, daemon=True).start()

    try:
        time.sleep(15)
    except KeyboardInterrupt:
        print("\nStopped.")
