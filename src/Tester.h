/*
 * Tester.h
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#ifndef SRC_TESTER_H_
#define SRC_TESTER_H_

#include "TCPSocket.h"

namespace networkingLab
{

class Tester
{
private:
	TCPSocket * socket;
public:
	Tester();
	virtual ~Tester();
};

} /* namespace networkingLab */

#endif /* SRC_TESTER_H_ */
