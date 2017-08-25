/*
 * ServerConnector.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_TCPSERVER_SERVERCONNECTOR_H_
#define SRC_TCPSERVER_SERVERCONNECTOR_H_

#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include <vector>
#include "TCPSocket.h"
#include "AbstractServer.h"
#include "../API/includes/ServerHandler.h"
#include "../SDKUtilsClient/SDKUtilsClient.h"
#include "../API/Protocol.h"
////extra
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netinet/ip.h>

using namespace std;
namespace networkingLab
{

class ServerConnector : public AbstractServer
{
private:
	ServerHandler * handler;
	string ip;
	size_t port;
	SDKUtilsClient utils;
	TCPSocket * _socket;
	bool logged_in,keepRunning;
public:
	ServerConnector(ServerHandler * oHandler);
	virtual ~ServerConnector();
	virtual void run();
public:
	/**
	 * connect the server
	 */
	virtual bool connect(const string& ip, size_t port);
	/**
	 * register as new user
	 * possible ack/nack
	 */
	virtual bool newRegister(const string& name, const string& pwd);
	/**
	 * login as existing user
	 * possible ack/nack
	 */
	virtual bool login(const string& name, const string& pwd);
	/**
	 * bool start the game with specific player
	 * {name:port}
	 */
	virtual bool isInitedConnection()const;
/**
 * start the server
 */
	virtual void startServer();
	/**********************************************************
		 ****************** Matching  **********************
		 **********************************************************
		 */	/**
		 * get players list
		 */
		virtual bool getList();
		/**
		 * offer y to play.
		 */
		virtual bool offer_y(const string & name, const string & port);
		/**
		* offer random player to play
		*/
		virtual bool offer_random();
		/**
		 * confirm offer to play
		 */
		virtual void confirmPlay(const string& name, const string & port);
		/**
		 * decline offer to play
		 */
		virtual void declineOffer(const string& name, const string & port);
		/**
		 * stop game - end session -> get HS
		 */
		virtual bool endGame(const string score);
		/**
		 * exit the server
		 */
		virtual void stopAndExit();
};

} /* namespace networkingLab */

#endif /* SRC_TCPSERVER_SERVERCONNECTOR_H_ */
