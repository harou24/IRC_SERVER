import os
print("------ RUN FUNC TESTS ------\n")

print("Testing if server receives messages!")
os.system('python3 tests/script/run_and_stop.py "Hello_Server!" "This" "is" "a" "Test"')

print("test sending message to server:")
os.system('python3 tests/script/run_and_stop.py "NICK hello"')

print("test sending message to server:")
os.system('python3 tests/script/run_and_stop.py "USER username hostname servername realname"')
