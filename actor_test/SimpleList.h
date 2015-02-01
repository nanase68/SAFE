/*
 * SimpleList.h
 *
 *  Created on: 2015/01/11
 *      Author: Ys
 */

#ifndef SIMPLELIST_H_
#define SIMPLELIST_H_

class SimpleListContent;

class SimpleList {
private:
	SimpleListContent* head;
public:
	void add(void* content);
	void* get();
	bool remove();

	SimpleList() : head(0){};
	virtual ~SimpleList(){};
};

class SimpleListContent{
public:
	void* content;
	SimpleListContent *next;
	SimpleListContent(){};
};
#endif /* SIMPLELIST_H_ */
