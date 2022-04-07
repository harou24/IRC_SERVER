#include "Server.hpp"
#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include <stdexcept>

#include <assert.h>
#include <unistd.h>

#include <iostream>
#include <thread>


Server serv(8080, "");

std::string msgToSend("");
TcpConnector* connector;
TcpStream* stream;

void  runServer()
{
	std::cout << "Runing server...\n";
	serv.start();
}

void connectClient()
{
	connector = new TcpConnector();
	assert(serv.isRunning() == true);
	stream = connector->connect(8080, "127.0.0.1");
}

void sendMsg()
{
	assert(serv.isRunning() == true);
	stream->send(msgToSend.c_str(), msgToSend.size());
}

void stopClient()
{
//    delete stream;
	delete connector;
}

void  runClient()
{
	assert(serv.isRunning() == true);
	connectClient();
	sleep(1);
	assert(serv.getNbrClients() == 1 && "NB CLIENTS IS NOT RIGHT");
	assert(serv.getClients().size() == 1 && "NB CLIENTS IS NOT RIGHT");
	sendMsg();
	sleep(1);
	assert(serv.getQueue().size() == 1);
	assert(serv.getQueue().front().data == msgToSend);
	stopClient();
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "You need to provide a message to send \
		to the server as argument of this program!\n";
		exit(1);
	}

	msgToSend = std::string(argv[1]);

	std::thread serverJob(runServer);
	sleep(2);
	assert(serv.isRunning() == true);

	std::thread clientJob(runClient);
	clientJob.join();

	std::cout << "Stopping server..." << "\n";
	serv.stop();
	assert(serv.isRunning() == false);

	serverJob.join();
	return 0;
}
