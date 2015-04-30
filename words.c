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
						padding
Parameters:
	ch: A character to output to the screen
	n: The number of times to output that character
	
Return:
	Nothing
	
Description:
	This function outputs a character a number of times to 
the screen. Often used in conjunction with structure() to 
output specific numbers of tab characters. Used for 
checking tree structure and debugging node errors.
**********************************************************/
void padding(char ch, int n) {
    int i;

    for (i = 0; i < n; ++i)
        putchar(ch);
}

/**********************************************************
					structure
Parameters:
	root: the top of a BST
	
Return:
	Nothing
	
Description:
	This function outputs a BST to the screen.
**********************************************************/
void structure(Node* root, int level) {
    if (root == NULL) {
        padding('\t', level);
        puts("~");
    } 
    else 
    {
        structure(root->right, level+1);
        padding('\t', level);
        printf("%s\n", root->word);
        structure(root->left, level+1);
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
					delete_word
Parameters:
	wordList: The top of a BST
	word: A word to be deleted
	
Return:
	A pointer to the top of the word list
	
Description:
	This function finds a node and removes it from a BST. 
This function will return a valid BST, but will not ensure 
a balanced tree. This function works recursively to find 
a node and perform delete operations and pointer 
reallocation.
**********************************************************/
Node* delete_word(Node *wordList, char *word)
{
	Node *nullCheck = NULL;
	Node *holdNodeptr = NULL;
	if(wordList == NULL)
		return NULL;

	if(strcmp(word, wordList->word) < 0)
	{
		nullCheck = delete_word(wordList->left, word);
		if(nullCheck == NULL)
			wordList->left = NULL;
		else if(nullCheck != wordList->left)
			wordList->left = nullCheck;
		return wordList;
	}
	else if(strcmp(word, wordList->word) > 0)
	{
		nullCheck = delete_word(wordList->right, word);
		if(nullCheck == NULL)
			wordList->right = NULL;
		else if(nullCheck != wordList->right)
			wordList->right = nullCheck;
		return wordList;
		
	}
	else if(strcmp(word, wordList->word) == 0)
	{
		if(wordList->left == NULL && wordList->right == NULL)
		{
			free(wordList->word);
			free(wordList);
			return NULL;
		}
		else if(wordList->left != NULL && wordList->right != NULL)
		{
			free(wordList->word);
			wordList->word = malloc(sizeof(char) * (strlen((min(wordList->right))->word) + 1));
			strcpy(wordList->word, (min(wordList->right))->word);
			wordList->right = delete_word(wordList->right, wordList->word);
			return wordList;
		}
		else //Only one child node
		{
			if(wordList->left != NULL)
				holdNodeptr = wordList->left;
			else if(wordList->right != NULL)
				holdNodeptr = wordList->right;
			free(wordList->word);
			free(wordList);
			return holdNodeptr;
		}
	}
	
	return wordList;
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

/**********************************************************
						min
Parameters:
	tree: A pointer to the root of a BST
Return:
	A pointer to the smallest node in the tree
	
	This function returns a pointer to the node with the 
lowest data value
**********************************************************/
Node* min(Node *wordList)
{
	if(wordList == NULL)
		return NULL;
	else if(wordList->left != NULL)
		return min(wordList->left);
	else
		return wordList;
}