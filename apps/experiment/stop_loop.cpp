#include <iostream>

#include <signal.h>

int main(void)
{
  pid_t pid;

  std::cout << "What is the process you want to stop ?\n";
  std::cin >> pid;
  std::cout << "Sending signal to kill the process...\n";
  kill(pid, SIGQUIT);

  return 0;
}
