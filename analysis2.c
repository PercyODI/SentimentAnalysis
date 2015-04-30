#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"
#include "analysis.h"

int analyze_review(char *fileName, Node *positiveWords, Node *negativeWords)
{
	int fileSize,
		numPositiveWords = 0,
		numNegativeWords = 0;
	char *reviewString,
		 *holdString;

	FILE *fp;

	fp = fopen(fileName, "r");
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);

	reviewString = malloc(fileSize + sizeof(char));
	holdString = malloc(fileSize + sizeof(char));
	fgets(reviewString, fileSize, fp);
	while(fgets(holdString, fileSize, fp) != NULL)
		strcat(reviewString, holdString);

	numPositiveWords = count_words(reviewString, positiveWords);
	numNegativeWords = count_words(reviewString, negativeWords);

	fclose(fp);
	free(reviewString);
	free(holdString);
	return numPositiveWords - numNegativeWords;
}

int count_words(char *string, Node *wordList)
{
	char *tokenizedStr = malloc(sizeof(char) * (strlen(string) + 1));
	char *token;
	int wordCount = 0;
	strcpy(tokenizedStr, string);

	token = strtok(tokenizedStr, " ,.\n\t");
	while(token != NULL)
	{
		wordCount += findWord(wordList, token);
		token = strtok(NULL, " ,.\n\t");
	}

	free(tokenizedStr);
	return wordCount;
}