/*
 * Message.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#include "Message.h"

Message::Message(){

}
Message::Message(Actor* sender, Actor* destination) {
	Message::sender = sender;
	Message::destination = destination;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}
