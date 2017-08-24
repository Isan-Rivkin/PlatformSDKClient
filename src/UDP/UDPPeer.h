/*
 * UDPPeer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: user
 */

#include "AbstractPeer.h"
#include "../API/includes/ServerHandler.h"
#include <string.h>
#include <strings.h>
#include <string>
#include <iostream>
#include <vector>
#include "../SDKUtilsClient/SDKUtilsClient.h"
#include "UDPSocket.h"
#include "../API/Protocol.h"
#define SIZE 1000

#ifndef SRC_UDP_UDPPEER_H_
#define SRC_UDP_UDPPEER_H_

namespace networkingLab {

class UDPPeer : public AbstractPeer
{
	ServerHandler* handler;
	UDPSocket* sock;
	size_t port;
	bool running;
	char buff[SIZE];
public:
	UDPPeer(ServerHandler * oHandler, size_t server_port);
	virtual ~UDPPeer();
	virtual void run();
	public:
		/**
		 * send a message to the peer
		 */
		virtual int sendToPeer(const string ip,size_t port,const string msg);
		/**
		 * read blocking from peer
		 */
		virtual int readSyncFromPeer();
		/**
		 * stop
		 */
		virtual void stop();
		/**
		 * still running ?
		 */
		virtual bool isRunning()const;

};

} /* namespace networkingLab */

#endif /* SRC_UDP_UDPPEER_H_ */
