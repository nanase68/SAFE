#include "message_pac.h"

MessagePac::MessagePac(){
	MessagePac::message = 0;
}

MessagePac::MessagePac(int i){
	MessagePac::message = i;
}

void MessagePac::operator=(int n) {
	MessagePac::message = n;
}

int MessagePac::get_message(void) {
	return MessagePac::message;
}


bool dealMessagePac(){
	MessagePac::actor.receiveMessage(message);
}
