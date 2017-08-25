/*
 * GAPI.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#include "../includes/GAPI.h"

namespace networkingLab {

GAPI::GAPI(size_t server_port)
{
	this->client_port = 0;
	this->_client = NULL;
	this->_server = NULL;
	this->server_port = server_port;
	this->_peer = NULL;
	this->_inited_p2p_async = false;
}

GAPI::~GAPI() {
}

void GAPI::run() {
	_server->waitForThread();
	_peer->waitForThread();
	cout <<"[GAPI:] run method invoked === disconnected from server. "<<endl;
}

bool GAPI::connect(const string& ip, size_t port)
{
	bool res = _server->connect(ip, port);
	return res;
}
void GAPI::startAsyncCommunication()
{
	_server->startServer();
}
bool GAPI::newRegister(const string& name, const string& pwd)
{
	bool res = _server->newRegister(name, pwd);
	return res;
}

bool GAPI::login(const string& name, const string& pwd)
{
	bool res = _server->login(name, pwd);
	return res;
}

bool GAPI::startGame(const string& name,const string& port)
{
	int ret = _server->offer_y(name, port);
	return ret;
}

bool GAPI::startRandom()
{
	return _server->offer_random();
}

bool GAPI::getUserList()
{
	return _server->getList();
}

bool GAPI::getHighscores()
{
	return false;
}

void networkingLab::GAPI::endGame(string score)
{
	/**
	 * TODO::
	 * let peer know as well !
	 * UDP
	 */
	_server->endGame(score);
}

void GAPI::exit()
{
	_server->stopAndExit();
	_peer->stop();
}

void GAPI::handleUDP(const char* msg)
{
	_client->handleUDP(msg);
}

void GAPI::initServer(AbstractServer* pServer_connector)
{
	_server = pServer_connector;
}
void GAPI::initClientHandler(ServerHandler* client) {
	_client = client;
}
void GAPI::handleTCP(const char* msg, int command)
{
	if(msg != NULL && (command == AUTH_ACK_LOGIN || AUTH_NACK_LOGIN))
	{
		string port="";
		for(size_t i =0; i< strlen(msg);++i)
			port += msg[i];
		this->client_port = utils.castToSize(port);
	}
	_client->handleTCP(msg, command);
}
AbstractServer* GAPI::getServerConnector()
{
	return _server;
}
void networkingLab::GAPI::confirmPlay(const string& name, const string& port)
{
	_server->confirmPlay(name, port);
}

void networkingLab::GAPI::declineOffer(const string& name, const string& port)
{
	_server->declineOffer(name, port);
}

void networkingLab::GAPI::initPeerConnector(AbstractPeer* pPeer_connector)
{
	this->_peer = pPeer_connector;
}

void GAPI::startAsyncPeerCommunication()
{
	if(!_inited_p2p_async)
	{
		_peer->start();
		_inited_p2p_async = true;
	}
}

int networkingLab::GAPI::sendToPeer(const UserDetails& otherPeer, const char* msg,
		size_t len)
{
	this->_peer->sendToPeer(otherPeer.ip, otherPeer.port, msg);
	return 1;
}

int GAPI::readSyncFromPeer()
{
	return this->_peer->readSyncFromPeer();
}
size_t networkingLab::GAPI::getPlayerPort() const
{
	return client_port;
}

void networkingLab::GAPI::initPeerHConnector(size_t port)
{
	_peer = new UDPPeer(this,port);
}

} /* namespace networkingLab */

