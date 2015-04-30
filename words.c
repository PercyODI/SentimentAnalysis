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

/**********************************************************
					createWordList
Parameters:
	fileName: The name of a file
	
Return:
	A pointer to the top of a word list
	
Description:
	This function takes a user specified file containing 
a list of words. The words are added individually to the 
BST using the addNodeToList function. A pointer to the top 
of the tree is then returned.
**********************************************************/
Node* createWordList(char* fileName)
{
	Node *root = NULL;
	char *wordToAdd = malloc(sizeof(char) * (MAX_WORD_SIZE + 1));
	FILE *fp = fopen(fileName, "r");

	if(fp == NULL)
	{
		printf("Failed to open %s\nAborting\n", fileName);
		free(wordToAdd);
		return NULL;
	}

	while(fscanf(fp, "%250s", wordToAdd) != EOF)
		root = addNodeToList(wordToAdd, root);

	free(wordToAdd);
	fclose(fp);
	return root;
}

/**********************************************************
					addNodeToList
Parameters:
	wordToAdd = a string containing a word to add to the list
	listRoot = the top of a BST to add the word to
	
Return:
	A pointer to the current top of a BST
	
Description:
	This function takes a a single word string and adds it 
to the specified word list. After adding the word to an 
appropriate spot, the tree is then rebalanced using
AVL_balance. 
	This function works recursively, so the root changes 
between calls. Each time the function returns up the stack, 
the next call is to balance the next highest level, so that
each potentially affected level (including the true root)
is checked and balanced.
**********************************************************/
Node* addNodeToList(char *wordToAdd, Node *listRoot)
{
	Node *holdNode = NULL;
	if(listRoot == NULL)
	{
		Node *newNode = malloc(sizeof(Node));
		if(newNode == NULL)
		{
			printf("Not enough memory to add node to list");
			return NULL;
		}
		newNode->word = malloc(sizeof(char) * (strlen(wordToAdd) + 1));
		if(newNode->word == NULL)
		{
			printf("Not enough memory to add node to list");
			return NULL;
		}
		strcpy(newNode->word, wordToAdd);
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if(strcmp(wordToAdd, listRoot->word) == 0)
		return listRoot;
	else if(strcmp(wordToAdd, listRoot->word) < 0)
	{
		holdNode = addNodeToList(wordToAdd, listRoot->left);
		if(listRoot->left == NULL)
		{
			listRoot->left = holdNode;
		}
		else if(holdNode != listRoot->left)
		{
			listRoot->left = holdNode;
		}
		return AVL_balance(listRoot);
	}
	else if(strcmp(wordToAdd, listRoot->word) > 0)
	{
		holdNode = addNodeToList(wordToAdd, listRoot->right);
		if(listRoot->right == NULL)
		{
			listRoot->right = holdNode;
		}
		else if(holdNode != listRoot->right)
		{
			listRoot->right = holdNode;
		}
		return AVL_balance(listRoot);
	}
	else
	{
		printf("Error in addNodeToList");
		return NULL;
	}
}

/**********************************************************
						treeHeight
Parameters:
	listRoot: The top of a BST
	
Return:
	The number of nodes of the longest leg
	
Description:
	This function takes a BST root and finds the length of 
its longest leg. This function works recursively to find 
the longest leg and return that result.
**********************************************************/
int treeHeight(Node *listRoot)
{
	int leftHeight, rightHeight;
	if(listRoot == NULL)
		return 0;
		
	leftHeight = treeHeight(listRoot->left);
	rightHeight = treeHeight(listRoot->right);

	return leftHeight >= rightHeight ? (leftHeight + 1) : (rightHeight + 1);
}

/**********************************************************
					AVL_balance
Parameters:
	listRoot: the top of a BST
	
Return:
	A pointer to the top of a word list
	
Description:
	This function takes a BST root and checks if its two 
legs are balanced (off by no more than one child). If the 
legs are unbalanced, it performs a pivot to balance the tree. 
This function does not work recursively, and must be called 
on every node to ensure balance. Pivot actions were derived 
from the following resource: 
https://www.cpp.edu/~ftang/courses/CS241/notes/self%20balance%20bst.htm
**********************************************************/
Node* AVL_balance(Node *listRoot)
{
	int leftHeight = 0,
		rightHeight = 0,
		balanceFactor = 0;
	Node *holdB = NULL,
		 *holdC = NULL,
		 *holdD = NULL,
		 *pivot = NULL,
		 *tempRoot = NULL;

	
	leftHeight = treeHeight(listRoot->left);
	rightHeight = treeHeight(listRoot->right);
	balanceFactor = rightHeight - leftHeight;

	//If no change, return listRoot
	if(balanceFactor >= -1 && balanceFactor <= 1)
		return listRoot;
	else if(balanceFactor > 1) //Right Case
	{
		leftHeight = treeHeight(listRoot->right->left);
		rightHeight = treeHeight(listRoot->right->right);
		balanceFactor = rightHeight - leftHeight;

		if(balanceFactor >= 0)
		{
			//Right-Right Case
			pivot = listRoot->right;
			holdB = listRoot->right->left;

			listRoot->right = holdB;
			pivot->left = listRoot;

			return pivot;
		}
		else
		{
			//Right-Left Case

			//Right-Rotation
			pivot = listRoot->right->left;
			tempRoot = listRoot->right;

			holdC = pivot->right;

			listRoot->right = pivot;
			tempRoot->left = holdC;

			//Left-Rotation
			holdD = pivot->left;
			pivot->left = listRoot;
			listRoot->right = holdD;

			return pivot;
		}
	}
	else if(balanceFactor < -1) //Left Case
	{
		leftHeight = treeHeight(listRoot->left->left);
		rightHeight = treeHeight(listRoot->left->right);
		balanceFactor = rightHeight - leftHeight;

		if(balanceFactor >= 0)
		{
			//Left-Right Case

			//Left-Rotation
			pivot = listRoot->left->right;
			tempRoot = listRoot->left;

			holdC = pivot->left;

			listRoot->left = pivot;
			tempRoot->right = holdC;

			//Right-Rotation
			holdD = pivot->right;
			pivot->right = listRoot;
			listRoot->left = holdD;

			return pivot;
		}
		else
		{
			//Left-Left Case
			pivot = listRoot->left;
			holdB = listRoot->left->right;

			listRoot->left = holdB;
			pivot->right = listRoot;

			return pivot;
		}	
	}
	else
	{
		printf("Error in AVL_balance");
		return NULL;
	}
}

/**********************************************************
					findWord
Parameters:
	wordList: The top of a word list BST
	string: A word to be searched for
	
Return:
	1 if word is found in the list
	0 if word is not found in the list
	
Description:
	This function searches for a specific word within a 
word list BST. This function works recursively to check 
only in trees where the word can occur.
**********************************************************/
int findWord(Node* wordList, char *string)
{
// 	int isWord = 0;

	if(wordList == NULL)
		return 0;

	if(strcmp(string, wordList->word) == 0)
		return 1;
	else if(strcmp(string, wordList->word) > 0)
		return findWord(wordList->right, string);
	else
		return findWord(wordList->left, string);
}

/**********************************************************
					delete_all_words
Parameters:
	wordList: The top of a tree of words
Return:
	None
	
	This function frees an entire word list through 
post-order traversal. This is more efficient than 
delete_word because it does not attempt to keep a 
balanced tree. 
**********************************************************/
void delete_all_words(Node *wordList)
{
	if(wordList == NULL)
		return;
	
	delete_all_words(wordList->left);
	delete_all_words(wordList->right);
	
	free(wordList->word);
	free(wordList);
	return;
}