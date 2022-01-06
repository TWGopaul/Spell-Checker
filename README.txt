//Programmer: Travis Gopaul
//COSC 320
//Spell Check program

This program uses a hash table data structure to store a dictionary of words. The hash table is then used as a spell checker in which the user can enter a string and the program will check if each word is in the table. If the word is not found, the program alters the word by adding, deleting, swaping and replacing upper and lower case characters. The
altered word is then searched for and printed on the screen as a suggestion. The suggestions are put into a linked list and each have the alteration functions ran on them to produce two edit distance suggestions. These suggestions are also presented to the user. 

main.cpp - driver program for the Dictionary and spell checker functions
Dictionary.h/.cpp - Header file and member definition file for the Dictionary class. An instance of the class is made up of an array of LinkedList objects, and each list has a pointer to the head of the list. This will be referred to as the table, T.
LinkedList.h/,cpp - Header file and member definition file for the LinkedList class. An instance of a LinkedList object has a pointer to the  previous node, a pointer to the next node and a string.
english.txt - File of english words to be read in by Dictionary object and stored in T.
foo.txt - sample text file to test functions of Dictionary class
makefile - run 'make' to compile programj with './main' executable
	run 'make clean' to remove *.o and 'main' executable
	run 'make val' to compile and run with valgrind
	run 'make leak' to compile and run with valgrind with --leak-check=full option

In my approach to this project I used the multiplication method of hashing that we used in lab 7. The Dictionary classfirst reads in the text file line by line. Each line is a word which is converted into an int with the given standard interpretation. That int is then hashed with the aforementioned method. The hash produces numbers larger than the array size of the Dictionary, which is 2^13 = 8192. Therefore I used the result of hash(str_to_int(word)) % 8192 as the position in which to insert a new node as the head of the LinkedList object. This ensured that any given bucket was inside the bounds of the table; a number between 0 and 8192, exclusive.

From there the program prompts the user to enter a string. Dictionary.spell_check(std::string) is called. The string is passed as a parameter to parse_string(std::string), which uses a stringstream with space, " ", as a delimiter to obtain individual words from the input. The words are trimmed of special characters, ''s', end of sentence '.', and have capital characters manipulated to then be searched for in the table. If they are not found, the word is put into a dynamically created LinkedList of misspelled words.

To search the table with find(std::string word), the program checks if the ListNode head == null at the position of the hash(word)%8192. If the node is = nullptr, then the word is not in that bucket, and therefore not in the table. If the head is not nullptr, a for loop searches the list until the last node, checking if the word seached matches the word in the bucket. In this way, the key, val pair is the string and the hash value%8192. The function returns true for found and false for not found. 

After the list of misspelled words is created, the spell_check() function runs the one_edit() function on each word inthe list. A linked list of one edit distance words is created and displayed on the screen. In the same loop to print the suggestions, the suggestions are put into another dynamically allocated LinkedList. In another while loop, each word in that list of suggestions is passed to one_edit() again, to find the two edit distance suggestions. Those words are stored in another linked list to then be displayed on the screen. After each while loop is exited, a deleteList() function is called to handle freeing the dynamic memory. 

Finally, the one_edit(std::string) function takes a string, and performs string manipulations to search for suggestions. The first for loop replaces each letter with a-z. The second for loop inserts a letter a-z in each position of the word. The third and fourth loops do the same as the first two loops, but with capital letters A-Z. The fifth loop deletes one letter from each position in the word. The last loop swaps adjacent characters in the word, from the begging to the end. 

Design/Notes/Deficiencies - 
I tried to account for all of the different capitalization combinations in the file, but I came across some that would need more attention. For example, spell checking the word "testt". There is abug in searching for the word "Test" as a suggestion, which is in the english.txt file not "test". Somewhere in the string manipulation this gets overlooked.  The program does search for different capitalizations initially, so "test" is a valid word becuase it searches "test", "Test" and "TEST" before determining if it is misspelled. I would change the find() function to be even more thourough as an improvement. I will say this project was illuminating on how spell checkers can be so off in terms of the intended word and the suggestions given, considering that example of "testt".




