/*
 * AbstractAPI.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_API_INCLUDES_ABSTRACTAPI_H_
#define SRC_API_INCLUDES_ABSTRACTAPI_H_

#include "MThread.h"
#include <string.h>
#include <strings.h>
#include <string>
#include <vector>
#include "TCPSocket.h"
#include "ServerHandler.h"
#include "UDPSocket.h"

#include "../../SDKUtilsClient/SDKUtilsClient.h"
#include "../../TCPServer/AbstractServer.h"
#include "../../UDP/AbstractPeer.h"
using namespace std;

namespace networkingLab
{
struct UserDetails
{
	string name;
	size_t port,score,winnigs;
	string ip;
	UserDetails(string oName, string oIp,size_t oPort)
	{
		score =0;
		winnigs = 0;
		name = oName;
		port = oPort;
		ip = oIp;
	}
	UserDetails(string oName , size_t oScore, size_t oWinnings)
	{
		port = 0;
		name = oName;
		score = oScore;
		winnigs = oWinnings;
	}
};
class AbstractAPI : public MThread, public ServerHandler
{
private:

	public:
		AbstractAPI();
		virtual ~AbstractAPI();
	public:
		virtual size_t getPlayerPort()const=0;
		// init methods
		virtual void initServer(AbstractServer * pServer_connector)=0;
		virtual void initPeerConnector(AbstractPeer * pPeer_connector)=0;
		virtual void initClientHandler(ServerHandler * client)=0;
		// instead of initPeerConnector(AbstractPeer*) - can init everything from here
			virtual void initPeerHConnector(size_t port)=0;
	public:
		virtual void run()=0;
		virtual void handleUDP(const char * msg)=0;
		virtual void handleTCP(const char* msg, int command)=0;
	public:
		/**
		 * connect the server
		 */
		virtual bool connect(const string& ip, size_t port)=0;
		/**
		 * start async connection
		 * only after authenthication process must be turned on.
		 */
		virtual void startAsyncCommunication()=0;
		/**
		 * start async communication with the other peer UDP
		 */
		virtual void startAsyncPeerCommunication()=0;
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
		virtual bool startGame(const string& name,const string& port)=0;
		/**
		 * start random game with player
		 */
		virtual bool startRandom()=0;
		/**
		 * confirm offer to play
		 */
		virtual void confirmPlay(const string& name, const string & port)=0;
		/**
		 * decline offer to play
		 */
		virtual void declineOffer(const string& name, const string & port)=0;
		/**
		 * get the user list from the server
		 */
		virtual bool getUserList()=0;
		/**
		 * get Highscore List list - {name:score}
		 */
		virtual bool getHighscores()=0;
		/**
		 * end a game with peer
		 */
		virtual void endGame(string score)=0;
		/**
		 * terminate connection
		 */
		virtual void exit()=0;
		/**
		 * get the server connector
		 */
		virtual AbstractServer* getServerConnector()=0;
		/****************************************************
		 * **************** UDP CLIENT ************************
		 *****************************************************/
		/**
		 * write a message to a peer ip:port
		 */
		virtual int sendToPeer(const UserDetails & otherPeer,const char * msg, size_t len)=0;
		/**
		 * read synch from peer
		 */
		virtual int readSyncFromPeer()=0;

};

} /* namespace networkingLab */

#endif /* SRC_API_INCLUDES_ABSTRACTAPI_H_ */
