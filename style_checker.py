#!/usr/bin/env

# Run script after make clean, otherwise you get an error
# Run the script in de root folder
# It wil check all files in the root and sub directories

import sys
import os

def checkLines(data, file):
	line_num = 0
	counter = 0
	data = data.readlines()
	for line in data:
		line_num += 1
		if len(line) > 80:
			print(file + " line " + str(line_num) + " has more then 80 characters, namely " + str(len(line)))
			counter += 1
		if line[0:len(line)-1].endswith((' ', ' ')):
			print(file + " line " + str(line_num) + " has trailing whitespaces")
			counter += 1
	if counter != 0:
		print("")

def checkFile(file):
	f = open(file)
	checkLines(f, file)

def files(dir):
	for f in os.listdir(dir):
		if not f.startswith('.'):
			if os.path.isdir(dir + f):
				files(dir + f + "/")
	allFiles = [dir + f for f in os.listdir(dir) if os.path.isfile(dir + f)]
	allFiles.sort()
	for filename in allFiles:
		checkFile(filename)

if __name__ == "__main__":
	dir = sys.path[0]
	files("./")