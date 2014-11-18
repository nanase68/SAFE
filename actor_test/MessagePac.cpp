#include "MessagePac.h"

MessagePac::MessagePac(){
	MessagePac::message = 0;
}

MessagePac::MessagePac(int i){
	MessagePac::message = i;
}

void MessagePac::operator=(int n) {
	MessagePac::message = n;
}

Message MessagePac::get_message(void) {
	return MessagePac::message;
}


bool MessagePac::dealMessagePac(){
	MessagePac::actor.receiveMessage(MessagePac::message);

	//TODO かく
	return false;
}
