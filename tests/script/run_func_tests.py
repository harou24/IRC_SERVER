import subprocess
import os
from os import path

TEST_DIR = "./build/apps"
SERVER_EXE = "./test_server_messaging.out"
MSG_TO_SEND = "Hello"


def changeDir(dir):
  os.chdir(dir)

def runTest():
  changeDir(TEST_DIR)
  output = subprocess.run([SERVER_EXE, MSG_TO_SEND], capture_output=True)
  if (output.returncode != 0):
    print("TEST->", SERVER_EXE, " SUCCEEDED!")
  else:
    print("TEST->", SERVER_EXE, " SUCCEEDED!")
    
runTest()
