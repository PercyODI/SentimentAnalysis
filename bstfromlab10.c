/* Name: Pearse Hutson
 * Id: 14040826
 * PawPrint: pah9qd
 * Date: 4/20/15
 * Lab: E
 * Labcode: White
 */

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void padding(char ch, int n) {
    int i;

    for (i = 0; i < n; ++i) {
        putchar(ch);
    }
}

void structure(BST* root, int level) {
    if (root == NULL) {
        padding('\t', level);
        puts("~");
    } else {
        structure(root->right, level+1);
        padding('\t', level);
        printf("%d\n", root->data);
        structure(root->left, level+1);
    }
}

void print(BST* root)
{
	structure(root, 0);
}

/**********************************************************
				build_balanced_tree
Parameters:
	a: An int array
	low: The lowest valid index in the array
	high: The highest valid index in the array
Return:
	The head of a balanced BST
	
	This function creates a balanced BST from a sorted array
**********************************************************/
BST* build_balanced_tree(int a[], int low, int high)
{	
	int middle = (low + high) / 2;
	
	if(middle > high || middle < low)
		return NULL;
	
	BST *newNode = malloc(sizeof(BST));
	newNode->data = a[middle];
	newNode->left = build_balanced_tree(a, low, middle - 1);
	newNode->right = build_balanced_tree(a, middle + 1, high);
		
	return newNode;	
} 

/**********************************************************
					delete_node
Parameters:
	tree: A pointer to the root of a BST
	data: The value to be deleted from the tree
Return:
	A pointer to the updated tree
	
	This function deletes one node from the tree and 
shifts the other values up
**********************************************************/
BST* delete_node(BST *tree, int data)
{
	BST *nullCheck = NULL;
	BST *holdBSTptr = NULL;
	if(tree == NULL)
		return NULL;

	if(data < tree->data)
	{
		nullCheck = delete_node(tree->left, data);
		if(nullCheck == NULL)
			tree->left = NULL;
		else if(nullCheck != tree->left)
			tree->left = nullCheck;
		return tree;
	}
	else if(data > tree->data)
	{
		nullCheck = delete_node(tree->right, data);
		if(nullCheck == NULL)
			tree->right = NULL;
		else if(nullCheck != tree->right)
			tree->right = nullCheck;
		return tree;
		
	}
	else if(data == tree->data)
	{
		if(tree->left == NULL && tree->right == NULL)
		{
			free(tree);
			return NULL;
		}
		else if(tree->left != NULL && tree->right != NULL)
		{
			tree->data = (min(tree->right))->data;
			tree->right = delete_node(tree->right, tree->data);
			return tree;
		}
		else //Only one child node
		{
			if(tree->left != NULL)
				holdBSTptr = tree->left;
			else if(tree->right != NULL)
				holdBSTptr = tree->right;
			free(tree);
			return holdBSTptr;
		}
	}
	
	return tree;
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
BST* min(BST *tree)
{
	if(tree == NULL)
		return NULL;
	else if(tree->left != NULL)
		return min(tree->left);
	else
		return tree;
}