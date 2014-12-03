/*
 * MessageStr.cpp
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

#include "Messages/MessageStr.h"
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
: Message::Message(Actor* sender, Actor* destination){
	MessageStr::set_content(str);
}

MessageStr::MessageStr() {
	// TODO Auto-generated constructor stub

}

MessageStr::~MessageStr() {
	// TODO Auto-generated destructor stub
}

