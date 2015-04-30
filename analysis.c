/* Name: Pearse Hutson
 * Pawprint: pah9qd
 * ID: 14040826
 * Lab: E
 * Homework 4
 * Date: 5/1/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"
#include "analysis.h"

/**********************************************************
		anaylyze_review
Parameters:
	fileName: The name of a file to analyze
	positiveWords: The top of a BST containing positive words
	negativeWords: The top of a BST containing negative words
	
Return:
	The value of the sentiment analysis
	< 0: Negative
	= 0: Neutral
	> 0: Positive
	
Description:
	This function analyses a file based on two BSTs 
containing the list of positive words and negative words. 
The file is concatenated into one string, and the string 
is sent to count_words to count the number of positive words, 
then again to count the number of negative words.  
The number returned is the number of found positive words 
minus the number of found negative words.
**********************************************************/
int analyze_review(char *fileName, Node *positiveWords, Node *negativeWords)
{
	int fileSize,
		numPositiveWords = 0,
		numNegativeWords = 0;
	char *reviewString,
		 *holdString;

	FILE *fp;

	fp = fopen(fileName, "r");
	
	//File should be checked for read access availability
	//before analyze_review is called
	if(fp == NULL)
	{
		printf("Invalid File: %s\n", fileName);
		return 0;
	}

	//Determine length of the entire review
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);

	//Create two strings the size of the entire review
	reviewString = malloc(fileSize + sizeof(char));
	holdString = malloc(fileSize + sizeof(char));
	
	//Get first line of the review
	fgets(reviewString, fileSize, fp);
	
	//Get subsequent lines of the review and concatenate them 
	//to the reviewString
	while(fgets(holdString, fileSize, fp) != NULL)
		strcat(reviewString, holdString);

	//Print headers and found words to the screen
	printf("\n-----%s-----\n", fileName);
	printf("Positive Words:\n");
	numPositiveWords = count_words(reviewString, positiveWords);
	printf("\nNegative Words: \n");
	numNegativeWords = count_words(reviewString, negativeWords);

	fclose(fp);
	free(reviewString);
	free(holdString);
	
	//Return the sentiment analysis result
	return numPositiveWords - numNegativeWords;
}

/**********************************************************
		count_words
Parameters:
	string: A string containing a review
	wordList: The top of a word list
	
Return:
	The number of words that match the given list
	
Description:
	This function finds the number of words in a given 
string that are in the given word list. Each word is also 
printed to the screen.
**********************************************************/
int count_words(char *string, Node *wordList)
{
	char *tokenizedStr = malloc(sizeof(char) * (strlen(string) + 1)),
		 *token = NULL,
		 delimiters[] = " ,.\r\n\t";
	int wordCount = 0;
	
	//Make a copy of the string so as not to lose the original string
	strcpy(tokenizedStr, string);

	//Initialize the first token in the string
	token = strtok(tokenizedStr, delimiters);
	
	//Run until out of tokens in string
	while(token != NULL)
	{
		if(findWord(wordList, token) == 1)
		{
			//Increase the number of matched words in wordList
			wordCount++;
			//Print the word to the screen preceded by a tab
			printf("\t- %s\n", token);
		}
		//Move to next token
		token = strtok(NULL, delimiters);
	}
	
	//If no matching words print **None**
	if(wordCount == 0)
		printf("\t**None**\n");

	free(tokenizedStr);
	return wordCount;
}