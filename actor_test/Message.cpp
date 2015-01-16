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


/*
 * MessageInt
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
 * MessageDouble
 */
void MessageDouble::set_content(double d){
	MessageDouble::content = d;
}
Message& MessageDouble::operator =(double d){
	MessageDouble::set_content(d);
	return *this;
}
double MessageDouble::get_content(){
	return content;
}
MessageDouble::MessageDouble(Actor* sender, Actor* destination, double d)
: Message::Message(sender, destination){
	MessageDouble::set_content(d);
}
MessageDouble::MessageDouble(){
}
MessageDouble::~MessageDouble(){
}


/*
 * MessageStr
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

void MessageStr::set_content(char* str){
	MessageStr::content = str;
}
Message& MessageStr::operator =(char* str){
	MessageStr::set_content(str);
	return *this;
}
std::string MessageStr::get_content(){
	return content;
}
MessageStr::MessageStr(Actor* sender, Actor* destination, char* str)
: Message::Message(sender, destination){
	MessageStr::set_content(str);
}

MessageStr::MessageStr() {
	// TODO Auto-generated constructor stub

}

MessageStr::~MessageStr() {
	// TODO Auto-generated destructor stub
}

