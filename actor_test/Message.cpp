/*
 * Message.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#include <Message.h>

Message Message::operator=(int i) {
	Message::content = i;
	return *this;
}

Message::Message() {
	// TODO Auto-generated constructor stub

}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

