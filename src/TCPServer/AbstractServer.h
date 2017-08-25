/*
 * AbstractServer.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_TCPSERVER_ABSTRACTSERVER_H_
#define SRC_TCPSERVER_ABSTRACTSERVER_H_
// extras
#include <stdio.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include "TCPSocket.h"
#include "MThread.h"


using namespace std;
namespace networkingLab
{

class AbstractServer : public MThread
{
public:
	AbstractServer();
	virtual ~AbstractServer();
	virtual void run()=0;
public:
	/**
	 * connect the server
	 */
	virtual bool connect(const string& ip, size_t port)=0;
	/**
	 * register as new user
	 * possible ack/nack
	 */
	virtual bool newRegister(const string& name, const string& pwd)=0;
	/**
	 * login as existing user
	 * possible ack/nack
	 */
	virtual bool login(const string& name, const string& pwd)=0;
	/**
	 * bool start the game with specific player
	 * {name:port}
	 */
	virtual bool isInitedConnection()const=0;
/**
 * start the server
 */
	virtual void startServer()=0;

	/**********************************************************
	 ****************** Matching Phaze 2 **********************
	 **********************************************************
	 */
	/**
	 * get players list
	 */
	virtual bool getList()=0;
	/**
	 * offer specific player to play {name:port}
	 */
	virtual bool offer_y(const string & name, const string & port)=0;
	/**
	 * offer random player to play
	 */
	virtual bool offer_random()=0;
	/**
	* confirm offer to play
	*/
	virtual void confirmPlay(const string& name, const string & port)=0;
	/**
	 * decline offer to play
	 */
	virtual void declineOffer(const string& name, const string & port)=0;
	/**
	 * end game with peer and get highscores
	 */
	virtual bool endGame(const string score)=0;
	/**
			 * exit the server
			 */
			virtual void stopAndExit()=0;
};

} /* namespace networkingLab */

#endif /* SRC_TCPSERVER_ABSTRACTSERVER_H_ */
