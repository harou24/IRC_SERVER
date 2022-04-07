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
  print("Running the Server...")
  try:
    path.exists(SERVER_EXE)
  except Exception as error:
    print(error)
    print("Executable file not found, run make first...: |", SERVER_EXE, "|\n")
    exit()
  output = subprocess.run([SERVER_EXE, str(PORT), HOST], capture_output=True)
  print(output.stdout, "\n")

def stopServer():
    pid = getProcessIdByName(SERVER_EXE)
    print("Pid of the process is:", pid, "\n")
    os.kill(pid, signal.SIGTERM)

def connectToServer():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(bytes("I am connected!", 'utf-8'))
   # dataReceived = s.recv(1024)
   # print("Received by server: |", dataReceived, "|")
    s.close()

def runTest():
  changeDir(TEST_DIR)

  newPid = os.fork()
  if newPid == 0:
    runServer()
  else:
    time.sleep(1)
    connectToServer()
    stopServer()

#  connectToServer()
#stopServer()


runTest()
