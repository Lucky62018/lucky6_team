import os
import threading
import commands

main = "./main data.json"
x = 500
y = 500
n = x / 10

def run(k):
  fileName = str(k) + ".ppm"
  command = main + " " + fileName
  out = commands.getstatusoutput(command)

t0 = threading.Thread(target=run(0))
t0.start()
print(threading.activeCount())
t1 = threading.Thread(target=run(1))
t1.start()

print("finished")