#ifndef ACTOR_TEST_MESSAGE_PAC_H_
#define ACTOR_TEST_MESSAGE_PAC_H_

class MessagePac {
private:
	int message;

public:
	MessagePac() {
		message = 0;
	}

	MessagePac(int i) {
		message = i;
	}

	void operator=(int n) {
		message = n;
	}

	int get_message(void) {
		return message;
	}

};

#endif //ACTOR_TEST_MESSAGE_PAC_H_
