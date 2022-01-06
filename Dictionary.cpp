//Programmer: Travis Gopaul
//Date: 4/6/21
//File: Dictionary.cpp
//Description: Member definitions for Dictionary.h. Utilizes Hash.h functions.

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <sstream>	//istringstream
#include <algorithm>	//remove()
#include <ctype.h>	//isupper()

Dictionary::Dictionary()	//constructor
{
	size = 8192;			//set size of array (#of buckets)
	T = new LinkedList[size];	//T is table aka array of linked lists
}

Dictionary::~Dictionary()
{
	for(int i = 0; i < this->size; i++)	//for each linked list in the array
		T[i].deleteList();
	
	delete [] this->T;	
}

void Dictionary::insert(std::string word)
{
	size_t pos = (hash(str_to_int(word))) % this->size; //hash%arraysize assigns a bucket n, 0<= n< size
	T[pos].putFront(word);
}

void Dictionary::read_file(std::string file)
{
	std::ifstream infile(file);
	std::string line;

	while(std::getline(infile, line))
		insert(line);

	infile.close();
}

size_t Dictionary::hash(size_t x)
{
	size_t w = 32;
	size_t p = 16;
	size_t a = 5915587277;
	size_t one = 1;

	size_t ax  = a * x;
	size_t two_w = one<<w;	//2^w
	size_t axMod2w = ax % (two_w - one); // ax % 2^w
	size_t w_minus_p = w - p;
	size_t two_w_minus_p = one<<w_minus_p;	//2^(w-p)
	size_t result = axMod2w/two_w_minus_p;	//(ax mod 2^w)/2^w-p
	return result;
}


size_t Dictionary::str_to_int(std::string str)
{
	size_t sum = 0;
	size_t n = (size_t)str.length();
	
	for(size_t i = 0; i < n; i++)
		sum += size_t(str.at(i)) << (size_t)7 * (n-i-(size_t)1);

	return sum;
}

// ************* statistic functions ********************
int Dictionary::word_count()
{
	int count = 0;
	LinkedList::ListNode *temp;
	
	for(int i = 0; i < this->size; i++)
	{
		temp = T[i].head;		//set temp = to the beginning of linked list
		while(temp != nullptr)		//while list is populated
		{
			count++;		
			temp = temp->next;	//iterate until last node reached
		}
	}

	return count;
}

int Dictionary::max_bucket()
{
	int max = 0, count;
	LinkedList::ListNode *temp;

	for(int i = 0; i < this->size; i++)
	{	
		count = 0;			//set count = 0 for each bucket
		temp = T[i].head;		//set temp = to beginning of list
		while(temp != nullptr)		//while list is populated
		{
			count++;	
			temp = temp->next;
		}
		if(count > max)			//if the count is larger than prev max, set new max
			max = count;
	}

	return max;
}


int Dictionary::min_bucket()
{
	int min, count;
	LinkedList::ListNode *temp;

	min = this->max_bucket();	//start min at the max bucket size; guarantee there will be smaller values

	for(int i = 0; i < this->size; i++)
	{
		count = 0;
		temp = T[i].head;
		while(temp != nullptr)
		{
			count++;
			temp = temp->next;
		}

		if(count != 0 && count < min)
			min = count;
	}
	
	return min;
}


size_t Dictionary::total_buckets()
{
	return this->size;
}


int Dictionary::used_buckets()
{
	int count = 0;
	LinkedList::ListNode *temp;

	for(int i = 0; i < this->size; i++)
	{
		temp = T[i].head;
		if(temp != nullptr)	//if the head is not null, the bucket is used
			count++	;	//increase count
	}

	return count;
}


int Dictionary::avg_buckets()
{
	int avg, numWords;
	numWords = this->word_count();
	avg = numWords/this->size;	//average = total words / total buckets
	return avg;
}



//****************************** Spell checker functions ************************************
LinkedList Dictionary::parse_string(std::string str)
{
	LinkedList misspelled;	//create a LL to store each individual word
	
	std::string word;
	std::string chars = ":;?!{}()=*\\\"+";	//special chars to filter out


	//I got this from techiedelght.com
	//for loop scans the string for each character in the chars string and removes it
	for(char c: chars)
		str.erase(std::remove(str.begin(), str.end(), c), str.end());

	std::istringstream iss(str);

	/* While loop parses user input string using string stream with a whitespace delimeter
 	 * Each word has unwanted characters removed
 	 * The final if statement handles various case events
 	 * (ie: FOR vs for vs For should all be valid words)
 	 */
	while(getline(iss, word, ' '))	
	{
		//erase commas
		std::size_t found = word.find(",");
		if((found != std::string::npos) && (found == (word.length() -1)))
			word.erase(word.length()-1);

		//erase "'s"
		found = word.find("'s");
		if((found != std::string::npos) && (found == (word.length() -2)))
			word.erase(word.length()-2);


		//erase '.' at end of sentence
		//wont erase acronym's periods since the found pos will be before the end of the word
		//see: 2nd condition in if statement
		found = word.find(".");
		if((found != std::string::npos) && (found == (word.length() -1)))
			word.erase(word.length()-1);
	
		
		//series of if statements to handle case-sensitivity	
		if(!find(word))	//if word as-is is not found
		{
			std::string copy = word;	//make copy of word
	
			if(islower(copy[0]))	//if the first letter is lower case
				copy[0] = toupper(copy[0]);	//make it upper case
			
			else
			{
				//taken from stack overflow, makes word all lower case
				std::transform(copy.begin(), copy.end(), copy.begin(),
					 [](unsigned char c){ return std::tolower(c); });
			}
			
			if(!find(copy))	//if all lowercase word is not found, make it uppercase
			{				
			std::transform(copy.begin(), copy.end(), copy.begin(),
					 [](unsigned char c){ return std::toupper(c); });
			}
			if(!find(copy))	//if captilized not found
			{
				//taken from stack overflow, makes word all lower case
				std::transform(copy.begin(), copy.end(), copy.begin(),
					 [](unsigned char c){ return std::tolower(c); });
			
				//make all lowercase and add to misspelled list
				misspelled.putFront(copy);
			}
		}

	}
	return misspelled;
}


bool Dictionary::find(std::string w)
{
	LinkedList::ListNode *temp;	//temp to traverse buckets
	
	bool inTable = false;		
	size_t table_pos;		//variable for the hash of searched word
	
	
	table_pos = (hash(str_to_int(w)) % size);	//hash the searched word
	inTable = false;				//reset boolean gate	
		
	if(T[table_pos].head != nullptr)		//search the LL at the position in the array
	{
		temp = T[table_pos].head;
		while(temp != nullptr)
		{
			if(temp->word.compare(w) == 0)	//if the word at the current node = searched word
			{
				inTable = true;
			}
			temp = temp->next;
		}
	}			

	return inTable;
}


LinkedList Dictionary::one_edit(std::string w)
{
	std::string word = w;	//make copy of original word
	std::string copy1, copy2;
	LinkedList suggestions;	//LL to store possible suggestions

	//replace letters, lowercase 
	for (int i = 0; i < word.length(); i++)	//loop through each letter in the word
	{
		for(int j = 97; j < 123; j++)		//loop through the alphabet
		{	
			copy1 = word;		//make another copy of word; resets the copy each loop
			copy1.at(i) = j;	//replace each letter in the word with a-z
			//if suggestion found and not already in the list and not original word, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1)) && (w.compare(copy1) != 0))		
				suggestions.putFront(copy1);
		}
	}

	//adding one lowercase character, a-z, at each position in the word
	for(int i = 0; i < word.length(); i++)
	{
		for(int j = 97; j < 123; j++)	//loop through the alphabet, add character to the end of the string
		{	
			copy1 = word;	//make another copy of word; resets the copy each loop
			copy1.insert(i, 1, j); //add one letter from a-z to the beggining of the word
	
			//if suggestion found and not already in the list, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1))&&(w.compare(copy1) != 0))		
				suggestions.putFront(copy1);
		}
	}

	//replace letters, uppercase 
	for (int i = 0; i < word.length(); i++)	//loop through each letter in the word
	{
		for(int j = 65; j < 91; j++)		//loop through the alphabet
		{	
			copy1 = word;		//make another copy of word; resets the copy each loop
			copy1.at(i) = j;	//replace each letter in the word with a-z
			//if suggestion found and not already in the list and not original word, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1)) && (w.compare(copy1) != 0))		
				suggestions.putFront(copy1);
		}
	}

	//adding one uppercase character, A-Z, at each position in the word
	for(int i = 0; i < word.length(); i++)
	{
		for(int j = 65; j < 91; j++)	//loop through the alphabet, add character to the end of the string
		{	
			copy1 = word;	//make another copy of word; resets the copy each loop
			copy1.insert(i, 1, j); //add one letter from a-z to the beggining of the word
	
			//if suggestion found and not already in the list, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1))&&(w.compare(copy1) != 0))		
				suggestions.putFront(copy1);
		}
	}


	//delete
	for (int i = 0; i < word.length(); i++)	//loop through each letter in the word
	{
		copy1 = word;	//reset copy1
		copy1.erase(i,1);	//erase 1 letter at position i

			//if suggestion found and not already in the list, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1))&&(w.compare(copy1) != 0)) 		
				suggestions.putFront(copy1);
	}
	
	//swaping adjacent
	for (int i = 0; i+1 < word.length(); i++)	//loop through each letter in the word
	{
		copy1 = copy2 = word;	//reset copy1
		copy1.at(i) = copy2.at(i+1);	//swap char i with i+1
		copy1.at(i+1) = copy2.at(i);	//swp char i+1 with char i

			//if suggestion found and not already in the list, add it to list
			if(find(copy1)&& !(suggestions.isFound(copy1))&&(w.compare(copy1) != 0))		
				suggestions.putFront(copy1);
	}
	return suggestions;
}


void Dictionary::spell_check(std::string input)
{
	LinkedList misspelled = parse_string(input);	//set = to the misspelled list returned by parse_string()
	int mis_count = 0, sugg_count = 0;	


	LinkedList::ListNode *temp1, *temp2, *temp3, *temp4;
	temp1 = misspelled.head;
	if(temp1 == nullptr)
		printf("No spelling errors found!\n");

	while(temp1 != nullptr)		//iterate through LL of mispelled words
	{
		mis_count++;		//increase misspelled word count
		std::cout << std::endl << "\"" <<  temp1->word << "\" is misspelled." << std::endl;
	
		LinkedList one_edit_sugg = one_edit(temp1->word);	//call one-edit on each mispelled word
		temp2 = one_edit_sugg.head;		
			if(temp2 == nullptr)	//if no suggestions
				std::cout << "No suggestions found for \"" << temp1->word << "\"" << std::endl; 
			else	//print suggestions and load into a LL
			{
				std::cout <<"\nThe following words are within one edit distance" << std::endl;
				std::cout <<"================================================\n" << std::endl;
				while(temp2!=nullptr)	//if a LL of suggestions is returned
				{
					sugg_count++;	//increase suggestion count
					std::cout << temp2->word << " ";	
					temp2=temp2->next;
				}
			}

			std::cout << std::endl;		

			//handle 2 edit distance suggestions	
			temp3 = one_edit_sugg.head;	//set temp3 = begin of LL of one edit suggestions
			if(temp3 != nullptr)
			{
				std::cout <<"\nThe following words are within two edit distances" << std::endl;
				std::cout <<"================================================\n" << std::endl;
			}
			while(temp3!= nullptr)		//iterate through list 
			{
				std::cout <<"Suggestions for " << temp3->word << ": ";
				LinkedList two_edit_sugg = one_edit(temp3->word); 	//call one edit on the suggestion
				temp4 = two_edit_sugg.head;	
				while(temp4 != nullptr)
					{
						sugg_count++; //increase suggestion count
						std::cout << temp4->word << " ";	//print 2 edit suggestions
						temp4 = temp4->next;
					}	
				std::cout << std::endl;	
				//memory clean up from LL created in one_edit() 
				two_edit_sugg.deleteList();	//delete that LL

				temp3 = temp3->next;		//move on to next word
			}
			//memory clean up from LL created in one_edit() 
			one_edit_sugg.deleteList();


		temp1 = temp1->next;
	}
	//statistics go here

	std::cout <<"================================================" << std::endl;
	std::cout <<"Summary" << std::endl;
	std::cout <<"================================================" << std::endl;
	std::cout << "Number of misspelled words = " << mis_count << std::endl;
	std::cout << "Number of suggestions = " << sugg_count << std::endl;
	//clean up memory allocation
	misspelled.deleteList();	//delete LL from parse_string function
		

}
