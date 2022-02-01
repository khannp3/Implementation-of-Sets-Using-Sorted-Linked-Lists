/*
 * SLLSet.cpp
 *
 *  Created on: Nov. 17, 2021
 *      Author: moham
 */


#include "SLLSet.h"
#include <iostream>

SLLSet::SLLSet() {
	size = 0;
	head = NULL;
}

SLLSet::SLLSet(int sortedArray[], int arrSize) {
	size = arrSize; head = NULL; //variable gets initialized
	for (int i=size-1; i>=0; i--) { //iterates thru for loop
		SLLNode* node = new SLLNode; //new node structure
		node->value = sortedArray[i]; //assign value of node
		node->next = head; //next pointer of node gets assigned to previous address of node
		head = node;
	}
}

int SLLSet::getSize()
{
	return size;
}

SLLSet SLLSet::copy()
{
	SLLNode* temperature = head; //variable gets initialized
	int arr[size];
	for (int i=0; i<size; i++) { //iterates thru for loop for setting values for arr
		arr[i] = temperature->value;
		temperature = temperature->next;
	}
	return *(new SLLSet(arr,size));
}
bool SLLSet::isIn(int v) {
    SLLNode* temperature = head;  //variable gets initialized
    for (int i=0; i<size; i++) { //iterates thru for loop for checking if any element in SLLset is equal to int v
    	if (temperature->value == v) {  //if any element in SLLset is equal to int v, return true
    		return true;
    	}
    	temperature = temperature->next;
    }
	return false; //if any element in SLLset is not equal to int v, return false
}
void SLLSet::add(int v) {
	SLLNode* newNode = head; //variable gets initialized
	if(isIn(v)==false) { //checks if there's int v present in set
		//	Accounting for when the set is already empty
    	if(newNode == NULL) { // considering when set is empty
    		SLLNode* temperature_1 = new SLLNode(v,NULL); //a new node gets initialized
    		newNode = temperature_1;
    	}
    	//	Accounting for when the value to be added is at the beginning of the set
    	else if(newNode->value > v){ //considering when at the beginning of the set the valued is to be added
    	    SLLNode* temperature_2 = new SLLNode(v,newNode);
    	    head = temperature_2;
    	}
    	else {
    		while (newNode->next!=NULL) {  //iterates thru while loop for each node
    			if (newNode->value < v && newNode->next->value > v) { // finds right location for added val
    				SLLNode* temperature_3 = new SLLNode(v,newNode->next);
    				newNode->next = temperature_3;
    			}
    			else {
    				newNode = newNode->next; //if cant find the right location, move to next location
    			}
    		}
    		if(newNode->value < v){ //assuming at the end of the set the value is being added
    			SLLNode* temperature_4 = new SLLNode(v,NULL);
    			newNode->next = temperature_4;
    		}
    	}
    size+=1; //size is added by 1, after something gets added
	}
}

void SLLSet::remove(int v) {
	if(isIn(v) == true) { //checks if v is part of set, so it can be removed if it is
		SLLNode* temperature = head; ///new node gets initialized
		if (v == head->value) { //if v= value at head, then its removed
			head = head->next;
			size -= 1; //size is subtracted by 1
		}
		while (temperature !=NULL && temperature->next != NULL) { //iterates thru while loop for updating temp pointer for next node
			if ((temperature->next)->value == v) {//checks if correct node is found
				temperature->next = (temperature->next)->next;  // previous pointer is changed to point at next node and removed value is skipped
				size -= 1;
			}
			else {
				temperature = temperature->next;
			}
		}
	}
}

SLLSet SLLSet::setUnion(SLLSet s){
	SLLNode* nodeUnion = new SLLNode();   //first node gets initialized
	SLLSet* setUnion = new SLLSet();  //variable gets initialized
	setUnion->head = nodeUnion;
	int sizeCount = 0;
	SLLNode* unionSetAdd = setUnion->head;
	SLLNode* old_SetAdd = head;
	SLLNode* new_SetAdd = s.head;
	for(int i=0; i<size+s.getSize(); i++) { //iterates m times thru for loop
		if(old_SetAdd == NULL){ //if oldsetAdd is NULL, remaining values from set get added
			if(new_SetAdd != NULL){ //to add value until NULL reaches for new set
				unionSetAdd->value = new_SetAdd->value; //sets current unionset value to newset value
				new_SetAdd = new_SetAdd->next;
				sizeCount += 1; //size_count get updated for each new addition
			}
		}
		else if(new_SetAdd == NULL){// this runs if newSetAdd is NULL
			if(old_SetAdd != NULL){
				unionSetAdd->value = old_SetAdd->value;
				old_SetAdd = old_SetAdd->next;
				sizeCount += 1;
			}
		}
		else if(old_SetAdd->value < new_SetAdd->value){  //confirms the lower value is added to unionset first
			unionSetAdd->value = old_SetAdd->value;
			old_SetAdd = old_SetAdd->next;
			sizeCount += 1;
		}
		else if(old_SetAdd->value > new_SetAdd->value){ //if not, the opposite cases occurs to confirm the lower value is added to unionset first
			unionSetAdd->value = new_SetAdd->value;
			new_SetAdd = new_SetAdd->next;
			sizeCount += 1;
		}
		else if(old_SetAdd->value == new_SetAdd->value){ //when both oldset values are equal, value gets added
			unionSetAdd->value = old_SetAdd->value;
			old_SetAdd = old_SetAdd->next;  //to avoid intersection values,set location gets updated
			new_SetAdd = new_SetAdd->next;
			sizeCount += 1;
		}
		if(old_SetAdd == NULL && new_SetAdd == NULL){
			break;
		}
		SLLNode* nextUnionNode = new SLLNode(); // new node in unionset for next value gets initialized
		unionSetAdd->next = nextUnionNode;
		unionSetAdd = nextUnionNode;
	}
	if(sizeCount == 0){ //confirming for no union between sets
		delete nodeUnion; //the first created nodeUnion gets deleted
		setUnion->head = NULL; //head set to NULL
		setUnion->size = 0; //setUnion sized set to 0
		return *setUnion;
	}
	unionSetAdd->next = NULL; //last node in unionSet set to NULL
	setUnion->size = sizeCount; //size of unionSet gets updated
	return *setUnion;
}

SLLSet SLLSet::intersection(SLLSet s){
	SLLSet* setInter = new SLLSet(); //intersection set gets initialized
	if (head == NULL) { // if current set empty, then empty intersection set is returned
		return *setInter;
	}
	if (s.head == NULL) {
		return *setInter;//if s set empty, then empty intersection set is returned
	}
	SLLNode* temperature = head; // node gets initialized, and gets set equal to head
	while (temperature!= NULL) { //iterates thru while loop through each node
		if (s.isIn(temperature->value) == false){
			remove(temperature->value);
		}
		temperature = temperature->next;
	}
	if (head == NULL) { //if node points to NULL,intersection set will be returned
		return *setInter;
	}
	*setInter = copy();
	return *setInter;
}

SLLSet SLLSet::difference(SLLSet s){
	SLLSet *setDiff = new SLLSet(); //variables get initialized
	if (head == NULL) { //if head points to NULL, setDiff is returned
		return *setDiff;
	}
	if (s.head == NULL) {//if head of the s set points to NULL, setDiff is returned
		*setDiff = copy();
		return *setDiff;
	}
	SLLNode *temperature = head; //temperature node gets initialized, sets equal to head
	while (temperature != NULL) { //iterates thru while loop through each node
		if (s.isIn(temperature->value) == true) {
			remove (temperature->value);
		}
		temperature = temperature->next;
	}
	if (head == NULL) {  //if given node points to NULL, setDiff is returned
		return *setDiff;
	}
	*setDiff = copy();
	 return *setDiff;
}

SLLSet SLLSet::setUnion(SLLSet sArray[],int size) {
	SLLSet* setUnion = new SLLSet(); //variables get initialized
	for (int i=0; i<size; i++) { //iterates thru for loop through sArray
		*setUnion = (*setUnion).setUnion(sArray[i]);} // update setUnion to union of all set in array
	return *setUnion;}

string SLLSet::toString() {
	SLLNode *temperature = head; //variables get initialized
	string output = "";
	for (int i=0; i<size; i++) { //iterates thru for loop through each node
		output += to_string(temperature->value); //elements are converted to string
		temperature = temperature->next;
		if (temperature!=NULL) {
			output += ", "; //adds , between each element
		}
	}
	return output;
}
