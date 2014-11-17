
#include "global_queue.h"
#include "message_pac.h"

#include <vector>




GlobalQueue::GlobalQueue(){
	GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, (MessagePac)0);
}

MessagePac GlobalQueue::pop(){
	MessagePac ret;

	ret = GlobalQueue::gqueue()[0];

	return(ret);

}

void GlobalQueue::push(MessagePac m){

}
    
    
    
    
    
    
    
