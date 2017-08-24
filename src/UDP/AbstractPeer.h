/*
 * AbstractPeer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: user
 */

#ifndef SRC_UDP_ABSTRACTPEER_H_
#define SRC_UDP_ABSTRACTPEER_H_


#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include "MThread.h"
#include "UDPSocket.h"
// extras
#include <stdio.h>
#include <arpa/inet.h>


namespace networkingLab
{
class AbstractPeer : public MThread
{
public:
	AbstractPeer();
	virtual ~AbstractPeer();
	virtual void run()=0;
public:
	/**
	 * send a message to the peer
	 */
	virtual int sendToPeer(const string ip,size_t port,const string msg)=0;
	/**
	 * read blocking from peer
	 */
	virtual int readSyncFromPeer()=0;
	/**
	 * stop
	 */
	virtual void stop()=0;
	/**
	 * is running ?
	 */
	virtual bool isRunning()const=0;

};

} /* namespace networkingLab */

#endif /* SRC_UDP_ABSTRACTPEER_H_ */
