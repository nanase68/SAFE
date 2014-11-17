
#include "global_queue.h"
#include "message_pac.h"

#include <vector>




GlobalQueue::GlobalQueue(){
	GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

MessagePac GlobalQueue::pop(){
	MessagePac ret;

	ret = GlobalQueue::gqueue[0];

	return(ret);

}


    
    
    
    
    
    
    
