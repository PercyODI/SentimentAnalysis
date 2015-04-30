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
#include <ctype.h>
#include <unistd.h>
#include "words.h"
#include "analysis.h"
 
int main(int argc, char *argv[])
{
	Node *positiveWords,
		 *negativeWords;
	char resultStr[9];
	int  i,
		 reviewResult;

	//Check for proper number of arguments
	//Any number over four is valid
	if(argc < 4)
	{
		printf("\nInvalid arguments\n");
		printf(	"%s %s %s %s", 
				"Expected:", 
				argv[0], 
				"<positive words file> <negative words file>",
				"<review files (any number)>\n\n");
		return 0;
	}

	positiveWords = createWordList(argv[1]);
	negativeWords = createWordList(argv[2]);

	//Test if both word lists are valid
	if(positiveWords != NULL && negativeWords != NULL)
	{
		//Run for every file after the first two given
		for(i = 3; i < argc; i++)
		{
			//If read access for file is denied or file doesn't exist,
			//continue to next file 
			if(access(argv[i], R_OK) == -1)
			{
				printf("\nInvalid File: %s\n", argv[i]);
				continue;
			}
			
			//Call analyze_review to determine sentiment value of file
			reviewResult = analyze_review(argv[i], positiveWords, negativeWords);
				
			//Set appropriate response according to sentiment value
			if(reviewResult > 0)
				strcpy(resultStr, "positive");
			else if(reviewResult == 0)
				strcpy(resultStr, "neutral");
			else if(reviewResult < 0)
				strcpy(resultStr, "negative");

			printf("\n%s is a %s review.\n", argv[i], resultStr);
		}

		printf("\n");
	}
	
	//Clean up and delete the two word lists.
	//ToDo: create a delete_all_words function to streamline process

	delete_all_words(positiveWords);
	delete_all_words(negativeWords);

	// while(positiveWords != NULL) 
		// positiveWords = delete_word(positiveWords, positiveWords->word);

	// while(negativeWords != NULL)
		// negativeWords = delete_word(negativeWords, negativeWords->word);

	return 0;
}
