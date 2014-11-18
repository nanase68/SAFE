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

int Message::get_content(){
	return Message::content;

}

bool Message::dealMessage(){
	Message::actor->receiveMessage(this);
}


Message::Message() {
	Message::content = 0;
}
Message::Message(int i){
	Message::content = i;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

