/*
 * SDKUtils.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#include "../SDKUtilsClient/SDKUtilsClient.h"

namespace networkingLab {

SDKUtilsClient::SDKUtilsClient() {


}
int SDKUtilsClient::generateRandom(int low_bound, int high_bound)
{
	return generateRandom(low_bound, high_bound,0);
}
int SDKUtilsClient::generateRandom(int low_bound, int high_bound,int seed)
{
	int val;
	 /* initialize random seed: */
	if(seed==0)
	  srand(time(NULL));
	else
	  srand(time(NULL)+seed);
	  /* generate secret number between 1 and 10: */
	  val = rand() % high_bound + low_bound;
	  return val;
}
size_t SDKUtilsClient::castToSize(const string& number_str) const
{
	std::istringstream iss(number_str);
	size_t port;
	iss >> port;
	return port;
}

SDKUtilsClient::~SDKUtilsClient() {

}

int networkingLab::SDKUtilsClient::writeCommand(TCPSocket* socket, int cmd,
		const char* buff)
{
	int cmdNet = htonl(cmd);
	int res = socket->write((char*)&cmdNet,4);
	if(res < 4)
	{
		return -1;
	}
	if(buff != NULL)
	{
		int len = strlen(buff);
		int lenNet = htonl(len);
		res= socket->write((char*)&lenNet,4);
		if(res < 0)
		{
			return -1;
		}
		res = socket->write(buff,len);
		if(res < len)
		{
			return -1;
		}
	}
	return res;
}

int networkingLab::SDKUtilsClient::getCommand(TCPSocket* sock) const
{
	int command;
			char * buffer;
			int len;
			int ret = sock->read((char*)&command,4);
			if(ret >0)
			{
				command = ntohl(command);
				return command;
			}
			else
			{
				cout <<"[SDKUtils:] couldn't read command -1" <<endl;
			}
			return -1;
}

char* networkingLab::SDKUtilsClient::getBufferdCommand(TCPSocket* sock) const {
	char * buffer;
	int len;
	sock->read((char*)&len, 4);
	len=ntohl(len);
	buffer = new char[len];
	int bytes = sock->read(buffer, len);
	buffer[bytes] = '\0';

	return buffer;
}

string SDKUtilsClient::intToString(int a) const
{
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}
string SDKUtilsClient::sizeToString(size_t sizeToStr)const
{
	std::stringstream ss;
	ss <<sizeToStr;
	std::string sService = ss.str();
	return sService;
}
string networkingLab::SDKUtilsClient::simulateInput(const string value) const
{
	streambuf *backup;
		  istringstream oss(value);
		  backup = cin.rdbuf();
		  cin.rdbuf(oss.rdbuf());
		  string str;
//		  cin >> str;
		  return str;
}

} /* namespace networkingLab */

