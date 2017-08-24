/*
 * GAPI.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_API_INCLUDES_GAPI_H_
#define SRC_API_INCLUDES_GAPI_H_

#include "MThread.h"
#include "AbstractAPI.h"
#include <string.h>
#include <strings.h>
#include <string>
#include <iostream>
#include <vector>
#include "../../TCPServer/AbstractServer.h"
#include "../../UDP/AbstractPeer.h"
#include "../../UDP/UDPPeer.h"
#include "../../SDKUtilsClient/SDKUtilsClient.h"
#include "../Protocol.h"
using namespace std;
namespace networkingLab {

class GAPI : public AbstractAPI
{
private:
	AbstractServer * _server;
	AbstractPeer   * _peer;
	ServerHandler  * _client;
	size_t server_port,client_port;
	SDKUtilsClient utils;
	bool _inited_p2p_async;
public:
	GAPI(size_t server_port);
	virtual ~GAPI();
public:
	virtual size_t getPlayerPort()const;
	// init
	virtual void initServer(AbstractServer * pServer_connector);
	virtual void initClientHandler(ServerHandler * client);
	virtual void initPeerConnector(AbstractPeer * pPeer_connector);
	// instead of initPeerConnector(AbstractPeer*) - can init everything from here
	virtual void initPeerHConnector(size_t port);

public:

	virtual void run();
	virtual void handleUDP(const char * msg);
	virtual void handleTCP(const char* msg, int command);
public:
	/**
	 * connect the server
	 */
	virtual bool connect(const string& ip, size_t port);
	/**
	 * start async communication with the server, only after authenthication process.
	 */
	virtual void startAsyncCommunication();
	/**
	 * start async communication with the other peer UDP
	 */
	virtual void startAsyncPeerCommunication();
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
	virtual bool startGame(const string& name,const string& port);
	/**
	 * start random game with player
	 */
	virtual bool startRandom();
	/**
	 * confirm offer to play
	*/
	virtual void confirmPlay(const string& name, const string & port);
	/**
	* decline offer to play
	*/
	virtual void declineOffer(const string& name, const string & port);
	/**
	 * get the user list from the server
	 */
	virtual bool getUserList();
	/**
	 * get Highscore List list - {name:score}
	 */
	virtual bool getHighscores();
	/**
	 * end a game with peer
	 */
	virtual void endGame(string score);;
	/**
	 * terminate connection
	 */
	virtual void exit();
	/**
	* get the server connector
	*
	*/
	virtual AbstractServer* getServerConnector();
	/****************************************************
	 * **************** UDP CLIENT ************************
	 *****************************************************/
	/**
	 * write a message to a peer ip:port
	 */
	virtual int sendToPeer(const UserDetails & otherPeer,const char * msg, size_t len);
	/**
	 * read synch from peer
	 */
	virtual int readSyncFromPeer();

};

} /* namespace networkingLab */

#endif /* SRC_API_INCLUDES_GAPI_H_ */
