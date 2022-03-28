import socket
import subprocess
import os

TEST_DIR = "../../build/apps"

def changeDir(dir):
  os.chdir(dir)
  
def runServer():
  output = subprocess.run(["./echo_server"], capture_output=True)
  print(output, "\n")

def stopServer():
  output = subprocess.run(["./stop_loop.out"], capture_output=True)
  print(output, "\n")

def connectToServer():
  socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  socket.connect("127.0.0.1", 8080)
  socket.send("I am connected!")
  socket.close()

def runTest():
  changeDir(TEST_DIR)
  runServer()
  connectToServer()
#stopServer()
