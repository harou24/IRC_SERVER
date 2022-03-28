import socket
import subprocess
import os
from os import path

TEST_DIR = "../../build/apps"
SERVER_EXE = "./echo_server"

def changeDir(dir):
  os.chdir(dir)
  
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
  socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  socket.connect("127.0.0.1", 8080)
  socket.send("I am connected!")
  socket.close()

def runTest():
  changeDir(TEST_DIR)
  runServer()
#  connectToServer()
#stopServer()


runTest()
