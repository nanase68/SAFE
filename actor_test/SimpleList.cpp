/*
 * SimpleList.cpp
 *
 *  Created on: 2015/01/11
 *      Author: Ys
 */

#include "SimpleList.h"

void SimpleList::add(void* content){
	SimpleListContent* slc = new SimpleListContent();
	slc->content = content;
	slc->next = head;
	head = slc;
}
void* SimpleList::get(){
	return (void*)(head->content);
}

bool SimpleList::remove(){
	SimpleListContent* temp = head;
	head = head->next;
	delete temp;
	return true;
}
