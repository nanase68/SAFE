/*
 * MessageInt.cpp
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

#include "Messages/MessageInt.h"
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

