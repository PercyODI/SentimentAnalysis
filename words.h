#ifndef WORDS_H_
#define WORDS_H_

#define MAX_WORD_SIZE 256

typedef struct node_{
	char *word;
	struct node_ *left;
	struct node_ *right;
} Node;

Node* createWordList(char* fileName);
Node* addNodeToList(char *wordToAdd, Node *listRoot);
int treeHeight(Node *listRoot);
Node* AVL_balance(Node *listRoot);
int findWord(Node* wordList, char *string);
void delete_all_words(Node *wordList);

#endif