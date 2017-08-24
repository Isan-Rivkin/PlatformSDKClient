/*
 * ServerHandler.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_API_INCLUDES_SERVERHANDLER_H_
#define SRC_API_INCLUDES_SERVERHANDLER_H_

#include <string>
#include <string.h>
#include <strings.h>
#include <iostream>
using namespace std;

namespace networkingLab
{

class ServerHandler {
public:
	ServerHandler();
	virtual ~ServerHandler();
public:
	virtual void handleUDP(const char * msg)=0;
	virtual void handleTCP(const char* msg,int command)=0;
};

} /* namespace networkingLab */

#endif /* SRC_API_INCLUDES_SERVERHANDLER_H_ */
