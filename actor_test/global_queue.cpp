
#include "global_queue.h"
#include "message_pac.h"






void GlobalQueue::init(void){
    for(int i=0; i < GLOBAL_QUEUE_SIZE; i++){
        GlobalQueue::gqueue[i] = 0;
    }
    
    
}




MessagePac GlobalQueue::pop(void){
	MessagePac ret;

	ret = GlobalQueue::gqueue[0];

	return(ret);

}
    
    
    
    
    
    
    
