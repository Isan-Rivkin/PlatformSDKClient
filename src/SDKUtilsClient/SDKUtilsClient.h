/*
 * SDKUtils.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_SDKUTILSCLIENT_SDKUTILSCLIENT_H_
#define SRC_SDKUTILSCLIENT_SDKUTILSCLIENT_H_

#include <iostream>
#include <string.h>
#include <strings.h>
#include <string>
#include "TCPSocket.h"
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>

#include <stdio.h>
#include <arpa/inet.h>

using namespace std;
namespace networkingLab {

class SDKUtilsClient {
public:
	SDKUtilsClient();
	virtual ~SDKUtilsClient();
public:
	 /**
		  * send a command protocol over TCP
		  * Socket from, cmd protocol, buffer or NULL
		  */
		 //int sendCommand(TCPSocket * socket,int cmd,const char* buff);
	int writeCommand(TCPSocket * socket, int cmd, const char* buff);
	 /**
		  * read command from socket by protocol
		  */
		 int getCommand(TCPSocket * sock)const;
		 /**
		  * read bufferd command followed after protocol command
		  */
		 char* getBufferdCommand(TCPSocket * sock) const;
		 /**
		  * random numbers service
		  */
		 int generateRandom(int low_bound, int high_bound);
		 int generateRandom(int low_bound, int high_bound,int seed);
		 /**
		  * cast string to number
		  */
		 size_t castToSize(const string& number_str) const;
		 /**
		  * cast integer to string
		  */
		 string intToString(int a)const;
		 /**
		  * cast size_t to string
		  */
		 string sizeToString(size_t sizeToStr)const;
		 /**
		  * simulate string input to cin console
		  */
		 string simulateInput(const string value)const;
};

} /* namespace networkingLab */

#endif /* SRC_SDKUTILSCLIENT_SDKUTILSCLIENT_H_ */
