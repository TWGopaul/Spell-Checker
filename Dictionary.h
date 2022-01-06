//Programmer: Travis Gopaul
//Date: 4/6/21
//File: Dictionary.h
//Description: Header file for Dictionary class which is a hash table using an array of linked lists

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "LinkedList.h"
#include <string>

class Dictionary
{
	private:
		LinkedList *T;
		size_t size;
		size_t hash(size_t);		//hash function
		size_t str_to_int(std::string); //convert a string to an int for hashing		
		
		void insert(std::string);	//insert a key/value pair into table

		LinkedList parse_string(std::string);	//parses string into words; filters out invalid characters; makes LL of misspelled words
		bool find(std::string); //checks if words from parse_string are in the hash table
		LinkedList one_edit(std::string);	//finds 1 edit dist words
	public:
		Dictionary();		//ctor
		~Dictionary();		//destructor
		void read_file(std::string);	//read a file, hash each word, store in array
		
		int word_count();	//returns total word count of file	
		int max_bucket();	//returns the word count in the bucket w/ the most words
		int min_bucket();
		size_t total_buckets();	//returns size
		int used_buckets();	//returns number of non empty buckets
		int avg_buckets();	//returns avg number of used buckets

		void spell_check(std::string);	//uses utility functions to hand spell check operations

};

#endif
