import socket
import subprocess
import os
from os import path
import time
import signal
import sys

TEST_DIR = "./build/apps"
SERVER_EXE = "./echo_server"

HOST = "127.0.0.1"
PORT = 8080

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

nbArgs = len(sys.argv)
if nbArgs < 2:
    exit()
data = sys.argv

def changeDir(dir):
  os.chdir(dir)

def listToString(list):
    str = ""
    return str.join(filter( lambda s: s != 'tests/script/run_and_stop.py' ,list))

def getProcessIdByName(name):
  for line in os.popen("ps ax | grep " + name + " | grep -v grep"):
    fields = line.split()
    pid = fields[0]
    return int(pid)

def runServer():
  try:
    path.exists(SERVER_EXE)
  except Exception as error:
    print(error)
    print("Executable file not found, run make first...: |", SERVER_EXE, "|\n")
    exit()
  output = subprocess.run([SERVER_EXE, str(PORT), HOST], capture_output=True)
  received = str(output.stdout, 'utf-8')
  received = received.replace("received: ", "")
  received = received.replace("\n", "")
  print("SENT     ->", "|" ,listToString(data), "|")
  print("RECEIVED ->", "|", received, "|")
  assert received == listToString(data)

def stopServer():
    socket.close()
    pid = getProcessIdByName(SERVER_EXE)
    os.kill(pid, signal.SIGTERM)

def sendData(data):
    socket.send(bytes(data, 'utf-8'))

def connectToServer():
    socket.connect((HOST, PORT))
    for i in range(1, nbArgs):
        sendData(data[i])

def runTest():
  changeDir(TEST_DIR)

  newPid = os.fork()
  if newPid == 0:
    runServer()
  else:
    time.sleep(1)
    connectToServer()
    stopServer()
    
runTest()
