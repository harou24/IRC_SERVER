#include <iostream>

#include <signal.h>
#include <unistd.h>

int running = 1;

void sig_handler(int pid) {
  std::cout << "Stopping the loop... pid=" << pid << ".\n";
  running = 0;
}

int     main() {
    signal(SIGQUIT, sig_handler);

    std::cout << "Starting the loop...\n";
    while (running)
    {
      std::cout << "looping...\n";
      sleep(1);
    }
    std::cout << "Loop stoped!\n";
    return (0);
}
