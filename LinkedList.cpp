//Programmer: Travis Gopaul
//Date: 4/6/21
//File: LinkedList.cpp
//Description: Member definitions for LinkedList class

#include "LinkedList.h"

LinkedList::LinkedList(){head = nullptr;}

LinkedList::ListNode::ListNode() //default constructor for ListNode();
{
	next = nullptr;
	prev = nullptr;
}

void LinkedList::deleteList()
{
	ListNode *temp;	//temp ptr to traverse list
	temp = this->head;	//start at head
	
	ListNode *pos;	//node to track position

	//while there is a node to delete
	while(temp != nullptr)
	{
		//save address of next node
		pos = temp->next;
		//delete current position
		delete temp;
		//move to the next position
		temp = pos;
	}
}

void LinkedList::putFront(std::string s)
{
	ListNode *n;
	n  = new ListNode();	//create new node
	n->next = head;	//"push" head down/next = nullptr
	n->word = s;	

	if(head != nullptr)
		head->prev = n;

	head = n;	//n is the new head of list != nullptr
}


bool LinkedList::isFound(std::string s)
{
	bool exists = false;
	ListNode *n;
	n = this->head;
			
	while(n != nullptr)	//traverse this list searching for the word s
	{
		if(n->word.compare(s)== 0)
			exists = true;
		n = n->next;
	}

	return exists; 
}

void LinkedList::ListNode::delListFromNode()
{
	ListNode *temp;
	temp = this;
	

	ListNode *pos;	//node to track position

	//while there is a node to delete
	while(temp != nullptr)
	{
		//save address of next node
		pos = temp->next;
		//delete current position
		delete temp;
		//move to the next position
		temp = pos;
	}

}
