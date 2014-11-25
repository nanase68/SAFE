/*
 * Message.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#include "Message.h"

Message Message::operator=(int i) {
	Message::content = i;
	return *this;
}

int Message::get_content(){
	return Message::content;

}

bool Message::dealMessage(){
	Message::actor->receiveMessage(this);
	// TODO かく
	return false;
}

Message::Message(){

}

Message::Message(Actor* a) {
	Message::actor = a;
	Message::content = 0;
}
Message::Message(Actor* a, int i){
	Message::actor = a;
	Message::content = i;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

