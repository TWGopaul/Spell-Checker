//Programmer: Travis Gopaul
//Date: 4/6/21
//File: main.cpp
//Description: Driver program for dictionary program

#include "Dictionary.h"
#include <chrono>
#include <iostream>

int main()
{
	std::string user_input;
	
	Dictionary T;
	//read in dictionary and build hash table

	
	printf("===============================================\n");
	auto start = std::chrono::system_clock::now();	//start time

	printf("Loading dictionary...\n");
	printf("===============================================\n");
	
	T.read_file("english.txt");	
	printf("Total words = %d\n", T.word_count());
	printf("Largest bucket size = %d\n", T.max_bucket());
	printf("Smallest bucket size = %d\n", T.min_bucket());
	printf("Total number of buckets = %ld\n", T.total_buckets());
	printf("Number of used buckets = %d\n", T.used_buckets());
	printf("Average number of words in each bucket = %d\n", T.avg_buckets());

	auto end = std::chrono::system_clock::now();	//end time
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "Total time taken: " << elapsed_seconds.count() << std::endl;

	printf("\n===============================================\n\n");
	printf("Please enter a string to spell check: \n");
	getline(std::cin, user_input);
	

	start = std::chrono::system_clock::now();	//start time
	T.spell_check(user_input);

	end = std::chrono::system_clock::now();	//end time
	elapsed_seconds = end-start;
	end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "Total time taken: " << elapsed_seconds.count() << std::endl;
	
	return 0;
}
