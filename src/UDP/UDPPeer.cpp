/*
 * UDPPeer.cpp
 *
 *  Created on: Aug 21, 2017
 *      Author: user
 */

#include "UDPPeer.h"

namespace networkingLab {

UDPPeer::UDPPeer(ServerHandler * oHandler,size_t server_port)
{
	handler = oHandler;
	this->port = server_port;
	sock = new UDPSocket(server_port);
	running = false;
}

UDPPeer::~UDPPeer()
{

}

void UDPPeer::run()
{
	running = true;
	int a = 0;
	while(running)
	{
		a = sock->recv(buff, SIZE);
		if(a>0)
		{
			buff[a] = '\0';
			handler->handleUDP(buff);
		}
	}
}

int UDPPeer::sendToPeer(const string ip, size_t port, const string msg)
{
	return sock->sendTo(msg, ip, port);
}

int UDPPeer::readSyncFromPeer()
{
	int a = sock->recv(buff, SIZE);
	if(a>0)
	{
		buff[a] = '\0';
		handler->handleUDP(buff);
		return a;
	}
	return a;
}

void UDPPeer::stop()
{
	running = false;
	sock->close();
}
bool UDPPeer::isRunning() const
{
	return running;
}
} /* namespace networkingLab */


