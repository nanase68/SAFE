/*
 * MessageInt.cpp
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

#include "Messages/MessageInt.h"
MessageInt::set_content(int i){
	MessageInt::content = i;
}
MessageInt::operator =(int i){
	MessageInt::set_content(i);
	return *this;
}
MessageInt::get_content(){
	return content;
}
MessageInt::MessageStr(Actor* sender, Actor* destination, int i)
: Message::Message(Actor* sender, Actor* destination){
	MessageInt::set_content(i);
}

MessageInt::MessageInt() {
	// TODO Auto-generated constructor stub

}

MessageInt::~MessageInt() {
	// TODO Auto-generated destructor stub
}

