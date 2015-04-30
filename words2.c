/* Name: Pearse Hutson
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"

Node* createWordList(char* fileName)
{
	Node *root = NULL;
	char *wordToAdd = malloc(sizeof(char) * MAX_WORD_SIZE);
	FILE *fp = fopen(fileName, "r");

	if(fp == NULL)
	{
		printf("Failed to open %s", fileName);
		return NULL;
	}

	while(fscanf(fp, "%s", wordToAdd) != EOF)
	{
		root = addNodeToList(wordToAdd, root);
	}

	free(wordToAdd);
	fclose(fp);
	return root;
}

Node* addNodeToList(char *wordToAdd, Node *listRoot)
{
	Node *holdNode = NULL;
	if(listRoot == NULL)
	{
		Node *newNode = malloc(sizeof(Node));
		newNode->word = malloc(sizeof(char) * (strlen(wordToAdd) + 1));
		strcpy(newNode->word, wordToAdd);
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if(strcmp(wordToAdd, listRoot->word) == 0)
	{
		printf("Remove word - Duplicate");
		return listRoot;
	}
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

int treeHeight(Node *listRoot)
{
	int leftHeight, rightHeight;
	if(listRoot == NULL)
		return 0;
	leftHeight = treeHeight(listRoot->left);
	rightHeight = treeHeight(listRoot->right);

	return leftHeight >= rightHeight ? (leftHeight + 1) : (rightHeight + 1);
}

//https://www.cpp.edu/~ftang/courses/CS241/notes/self%20balance%20bst.htm
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
	{
		return listRoot;
	}
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

void padding(char ch, int n) {
    int i;

    for (i = 0; i < n; ++i) {
        putchar(ch);
    }
}

void structure(Node* root, int level) {
    if (root == NULL) {
        padding('\t', level);
        puts("~");
    } else {
        structure(root->right, level+1);
        padding('\t', level);
        printf("%s\n", root->word);
        structure(root->left, level+1);
    }
}

int findWord(Node* wordList, char *string)
{
	int isWord = 0;

	if(wordList == NULL)
		return 0;

	if(strcmp(string, wordList->word) == 0)
		return 1;

	isWord = findWord(wordList->left, string);
	
	if(isWord == 1)
		return 1;

	isWord = findWord(wordList->right, string);
	
	if(isWord == 1)
		return 1;
	
	return 0;
}

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