/*
 * Message.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#include "Message.h"

bool Message::dealMessage(){
	Message::destination->receiveMessage(this);
	// TODO かく
	return false;
}

Message::Message(){

}

Message::Message(Actor* sender, Actor* destination) {
	Message::sender = sender;
	Message::destination = destination;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}


/*
 * MessageInt.cpp
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */
void MessageInt::set_content(int i){
	MessageInt::content = i;
}
Message& MessageInt::operator =(int i){
	MessageInt::set_content(i);
	return *this;
}
int MessageInt::get_content(){
	return content;
}
MessageInt::MessageInt(Actor* sender, Actor* destination, int i)
: Message::Message(sender, destination){
	MessageInt::set_content(i);
}

MessageInt::MessageInt() {
	// TODO Auto-generated constructor stub

}

MessageInt::~MessageInt() {
	// TODO Auto-generated destructor stub
}

/*
 * MessageStr.cpp
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

void MessageStr::set_content(std::string str){
	MessageStr::content = str;
}
Message& MessageStr::operator =(std::string str){
	MessageStr::set_content(str);
	return *this;
}
std::string MessageStr::get_content(){
	return content;
}
MessageStr::MessageStr(Actor* sender, Actor* destination, std::string str)
: Message::Message(sender, destination){
	MessageStr::set_content(str);
}

MessageStr::MessageStr() {
	// TODO Auto-generated constructor stub

}

MessageStr::~MessageStr() {
	// TODO Auto-generated destructor stub
}

