/*
 * Tester.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: user
 */

#include "Tester.h"

namespace networkingLab {

Tester::Tester() {
	socket = new TCPSocket(1555);
	socket->accept();
}

Tester::~Tester() {}

} /* namespace networkingLab */
