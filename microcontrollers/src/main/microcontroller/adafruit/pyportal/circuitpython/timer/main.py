import time

print("hi")

previousTime = time.monotonic()  # Time in seconds since power on

while True:
    now = time.monotonic()
    if now - previousTime >= 10.333:  # If 10.333 seconds elapses
        print("done")
        previousTime = now
