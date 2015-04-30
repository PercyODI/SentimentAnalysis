#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_ {
    int data;
    struct node_ *left;
    struct node_ *right;
} BST;

/**
 * param a: an int array
 * param low: the lowest valid indice in the array
 * param high: the highest valid indice in the array
 *
 * return: the root of a balanced BST
 *
 * This function should build a balanced bst from a sorted array. 
 * Hint: This function should look similar to binary search. 
 */
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

//Only for array, not for linked list
BST* find_node(BST *root, int val)
{
	if(root == NULL)
		return NULL;
	else if(val == root->data)
		return root;
	else if(val < root->data)
		return find_node(root->left, val);
	else if(val > root->data)
		return find_node(root->right, val);
	else
	{
		printf("Error: find_node invalid");
		return NULL;
	}
}

void remove_ptr(BST *root, BST *nodeToRemove, int val)
{
	BST *toDeletePtr = root;
	
	while(toDeletePtr->left != nodeToRemove || toDeletePtr->right != nodeToRemove)
	{
		if(val < toDeletePtr->data)
			toDeletePtr = toDeletePtr->left;
		else if(val > toDeletePtr->data)
			toDeletePtr = toDeletePtr->right;
	}
	if(toDeletePtr->left == nodeToRemove)
		toDeletePtr->left = NULL;
	else if(toDeletePtr->right == nodeToRemove)
		toDeletePtr->right = NULL;
	
	return;
}


BST* remove_node(BST *root, int val)
{
	BST *nodeToRemove = find_node(root, val);
	BST *toDeletePtr = root;
	
	if(root == NULL)
		return NULL;
	
	if(nodeToRemove->left != NULL)
		toDeletePtr = remove_node(root, nodeToRemove->left->data);
	if(nodeToRemove->right != NULL)
		toDeletePtr = remove_node(root, nodeToRemove->right->data);
	
	free(nodeToRemove);
	
	if(nodeToRemove == root)
		return NULL;
	else
	{
		while(toDeletePtr->left != nodeToRemove || toDeletePtr->right != nodeToRemove)
		{
			if(val < toDeletePtr->data)
				toDeletePtr = toDeletePtr->left;
			else if(val > toDeletePtr->data)
				toDeletePtr = toDeletePtr->right;
		}
		if(toDeletePtr->left == nodeToRemove)
			toDeletePtr->left = NULL;
		else if(toDeletePtr->right == nodeToRemove)
			toDeletePtr->right = NULL;
		
		return root;
	}
		
	// if(root == NULL)
		// return NULL;
	// BST* penultimate = NULL,
		 // travRoot = root;
	// char leftOrRight = 'n';
	
	// while(penultimate == NULL && travRoot != NULL)
	// {
		// if(val == travRoot->left->data)
		// {
			// leftOrRight = 'l';
			// penultimate = travRoot;
		// }
		// else if(val == travRoot->right->data)
		// {
			// leftOrRight = 'r';
			// penultimate = travRoot;
		// }
		// else if(val < travRoot->data)
			// travRoot = travRoot->left;
		// else if(val > travRoot->data)
			// travRoot = travRoot->right;
	// }
	
	// if(penultimate == NULL && travRoot == NULL)
	// {
		// printf("Value not found")
			// return;
	// }
	
	// travRoot = penultimate;
	
	// while(
	// {
		// while(travRoot->left != NULL)
		// {
			// travRoot = travRoot->left;
		// }
		// while(travRoot->right != NULL)
		// {
			// travRoot = travRoot->right;
		// }
		
	// }
}



// int find_array_index(int a[], int low, int high, int val)
// {
	// int middle = (low + high) / 2;
	
	// if(middle > high || middle < low)
		// return -1;
		
	// if(val == a[middle])
		// return middle;
	// else if(val < a[middle])
		// return find_node(a, low, middle - 1, val);
	// else if(val > a[middle])
		// return find_node(a, middle + 1, high, val);
	// else
	// {
		// printf("\nfind_node error\n");
		// return -1;
	// }	
// }
    
void padding(char ch, int n) {
    int i;

    for (i = 0; i < n; ++i) {
        putchar(ch);
    }
}

void structure(BST* root, int level) {
    int i;

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

int main(void) {
    
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    
    BST* root = build_balanced_tree(a, 0, 8);
	
	structure(root, 0);

	printf("\n\n------------------------------------\n\n");
	
	root = remove_node(root, 2);
	
	printf("\n\n------------------------------------\n\n");
	
	root = remove_node(root, root->data);
    
    structure(root, 0);
/*
    assert(root != NULL);
    assert(root->data == 5);
    assert(root->left != NULL);
    assert(root->left->data == 2);
    assert(root->left->left->data == 1);
    assert(root->left->left->left == NULL);
    assert(root->left->left->right == NULL);
    assert(root->left->right != NULL);
    assert(root->left->right->data == 3);
    assert(root->left->right->left == NULL);
    assert(root->left->right->right != NULL);
    assert(root->left->right->right->data == 4);
    assert(root->left->right->right->left == NULL);
    assert(root->left->right->right->right == NULL);
    
    assert(root->right != NULL);
    assert(root->right->data == 7);
    assert(root->right->left != NULL);
    assert(root->right->left->data == 6);
    assert(root->right->left->right == NULL);
    assert(root->right->left->left == NULL);
    assert(root->right->right != NULL);
    assert(root->right->right->data == 8);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right != NULL);
    assert(root->right->right->right->data == 9);
    assert(root->right->right->right->left == NULL);
    assert(root->right->right->right->right == NULL);
    assert(root->right->right->left == NULL);
*/

    printf("Yay!\n");

    return 0;
}