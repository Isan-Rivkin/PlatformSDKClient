/*
 * ServerConnector.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#include "ServerConnector.h"

namespace networkingLab
{

ServerConnector::ServerConnector(ServerHandler * oHandler):logged_in(false),keepRunning(false)
{
	this->ip = "";
	this->port = 0;
	this->handler = oHandler;
	this->_socket = NULL;
}

ServerConnector::~ServerConnector()
{
}

void ServerConnector::run()
{
	keepRunning = true;
	if(logged_in)
	{
		while(keepRunning)
		{
			int command = utils.getCommand(_socket);
			if(command>0)
			{
				char * msg=NULL;
				switch(command)
				{
				case MATCH_LIST:
				{
					msg = utils.getBufferdCommand(_socket);
					handler->handleTCP(msg,command);
					break;
				}
				case MATCH_OFFER_FROM_X:
				{
					msg = utils.getBufferdCommand(_socket);
					handler->handleTCP(msg,command);
					break;
				}
				case MATCH_OFFER_ACK_ACCEPTED_:
				{
					msg = utils.getBufferdCommand(_socket);
					handler->handleTCP(msg,command);
					break;
				}
				case MATCH_OFFER_NACK_REJECTED_:
				{
					handler->handleTCP(NULL, command);
					break;
				}
				case BUSY_STOP_GAME:
				{
					msg = utils.getBufferdCommand(_socket);
					handler->handleTCP(msg,command);
					break;
				}
				default:
				{
					cout <<"[ServerConnector:] Unrecognized command from the server" <<endl;
					break;
				}
				}
			}
		}
		cout << "[ServerConnector:] Connection to the Main Server has ended." <<endl;
	}
}

bool ServerConnector::connect(const string& ip, size_t port)
{

	this->_socket = new TCPSocket(ip,port);
	//
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);
	int fd = _socket->getSocketFileDescriptor();
	if(getsockname(fd, (struct sockaddr *)&sin, &len) == -1)
	    perror("getsockname");
	else
	    printf("port number %d\n", ntohs(sin.sin_port));

	//
	return true;
}

bool ServerConnector::newRegister(const string& name, const string& pwd)
{
	string full_request = name + ":" +pwd;
	int bytes = utils.writeCommand(_socket,AUTH_REQ_REGISTER, full_request.c_str());
	if(bytes>0)
	{
		int result = utils.getCommand(_socket);
		if(result == AUTH_ACK_LOGIN)
		{
			logged_in = true;
			return true;
		}
	}
	return false;
}

bool ServerConnector::login(const string& name, const string& pwd)
{
	string full_request = name + ":" + pwd;
	int bytes = utils.writeCommand(_socket, AUTH_REQ_LOGIN, full_request.c_str());
	if(bytes > 0)
	{
		int result = utils.getCommand(_socket);
		char * str_port = utils.getBufferdCommand(_socket);
		if(result == AUTH_ACK_LOGIN)
		{
			handler->handleTCP(str_port, AUTH_ACK_LOGIN);
			logged_in = true;
			return true;
		}
		handler->handleTCP(str_port, AUTH_NACK_LOGIN);
		return false;
	}
	return false;
}

bool ServerConnector::isInitedConnection() const
{
	return logged_in;
}

void ServerConnector::startServer()
{
	if(logged_in)
	{
		start();
	}
	else
	{
		cerr << "[ServerConnector:] Error please login." <<endl;
	}
}

bool ServerConnector::getList()
{
	if(logged_in)
	{
		int ret = utils.writeCommand(_socket,MATCH_LIST, NULL);
		if(ret > 0 )
		{
			return true;
		}
		else
		{
			cerr << "Error: couldnt get list from server." <<endl;
			return false;
		}
	}
}

bool ServerConnector::offer_y(const string& name, const string& port)
{
	if(logged_in)
	{
		string parsed_ = name +":"+port;
		int ret = utils.writeCommand(_socket, MATCH_MATCH_Y, parsed_.c_str());
		if(ret > 0 )
			return true;
	}
	return false;
}

bool ServerConnector::offer_random()
{
	if(logged_in)
	{
		int ret = utils.writeCommand(_socket, MATCH_RANDOM, NULL);
		if(ret>0)
		{
			return true;
		}
	}
	return false;
}
void ServerConnector::confirmPlay(const string& name, const string& port)
{
	cout <<name << " " << port << endl;
	string full_msg = name + ":" + port;
	utils.writeCommand(_socket, MATCH_ACK_OFFER_TO_X, full_msg.c_str());
}

void ServerConnector::declineOffer(const string& name, const string& port)
{
	string full_msg = name + ":" + port;
	utils.writeCommand(_socket, MATCH_OFFER_NACK_REJECTED_, full_msg.c_str());
}
bool ServerConnector::endGame(const string score)
{
	if(logged_in)
	{
		int ret = utils.writeCommand(_socket, BUSY_STOP_GAME, score.c_str());
		if(ret>0)
			return true;
	}
	return false;
}

} /* namespace networkingLab */


