
#ifndef ACTOR_TEST_MESSAGE_PAC_H_
#define ACTOR_TEST_MESSAGE_PAC_H_

class MessagePac {
private:
	int message;

public:
	void operator=(int n){
		message = n;
	}

	int get_message(void){
		return message;
	}
};

#endif //ACTOR_TEST_MESSAGE_PAC_H_
