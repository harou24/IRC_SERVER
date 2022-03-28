import socket
import subprocess
import os
from os import path
import time
import signal

TEST_DIR = "../../build/apps"
SERVER_EXE = "./echo_server"

HOST = "127.0.0.1"
PORT = 8080

def changeDir(dir):
  os.chdir(dir)

def getProcessIdByName(name):
  for line in os.popen("ps ax | grep " + name + " | grep -v grep"):
    fields = line.split()
    pid = fields[0]
    return int(pid)

  
def runServer():
  print("Run Server\n")
  try:
    path.exists(SERVER_EXE)
  except Exception as error:
    print(error)
    print("Executable file not found, run make first...: |", SERVER_EXE, "|\n")
    exit()
  output = subprocess.run([SERVER_EXE, "8080", "127.0.0.1"], capture_output=True)
  print(output, "\n")

def stopServer():
  output = subprocess.run(["./stop_loop.out"], capture_output=True)
  print(output, "\n")

def connectToServer():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(bytes("I am connected!", 'utf-8'))
    s.close()

def runTest():
  changeDir(TEST_DIR)

  newPid = os.fork()
  if newPid == 0:
    runServer()
  else:
    time.sleep(1)
    connectToServer()
    pid = getProcessIdByName(SERVER_EXE)
    print("Pid of the process is:", pid, "\n")
    os.kill(pid, signal.SIGTERM)
    
#  connectToServer()
#stopServer()


runTest()
