//Programmer: Travis Gopaul
//Date: 4/6/21
//File: LinkedList.h
//Description: Header file for linked list class

#ifndef LINKED_LIST
#define LINKED_LIST

#include <string>

class LinkedList
{
	public:	
		struct ListNode		//list node obj
		{
			ListNode *next, *prev; //ptrs for doubly linked list
			std::string word;	//value to be stored by LL
			ListNode();		//default constructor
			
			void delListFromNode();	//deletes list called by node	
		};	
		
		ListNode *head;		//Beginning of the list
		LinkedList();		//ctor
		void putFront(std::string); //insert node at the front of LL
		void deleteList();		//deletes list, called by list
		bool isFound(std::string);	//returns true if a word is in the list
};

#endif
