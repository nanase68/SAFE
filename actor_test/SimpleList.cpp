/*
 * SimpleList.cpp
 *
 *  Created on: 2015/01/11
 *      Author: Ys
 */

#include "SimpleList.h"

void SimpleList::add(void* content){
	SimpleListContent* slc = new SimpleListContent(); // create SimpleListContent
	slc->content = content;
	slc->next = head;
	head = slc;
}
void* SimpleList::get(){
	return head ? (void*)(head->content) : 0;
}

bool SimpleList::remove(){
	SimpleListContent* temp = head;
	if(head) {
		head = head->next;
		delete temp; // delete SimpleListContent
		return true;
	} else {
		return false;
	}
}
