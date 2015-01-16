/*
 * Message.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

//前方参照（インクルードガードで防がれた時のため）
class Actor;
#include <string>

class Message {
private:
	int label;
	void* content;
public:
	Actor *sender, *destination;

	void setLabel(int i){label = i;}
	int getLabel(){return label;}
	void setContent(void* v){content = v;}
	void* getContent(){return content;}

	Message();
	Message(int label): label(label){};
	Message(int label, void* content): label(label), content(content){};
	Message(Actor*, Actor*);
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
