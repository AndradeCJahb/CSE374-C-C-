/* trienode.h contains structure and function declarations for
  a trie implementation
  CSE374, HW5, 22Wi
*/

#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 9

// trieNode is one node in an 9-tree, where branches correspond to
// # and the T9 alphabet.
typedef struct trieNode {
    struct trieNode *branches[BRANCHES];
    char *word;
} trieNode;

// given a word list (dict), build a trie that holds
// each word.  Return pointer to the root node.
trieNode* build_trie(FILE *dict);

// given a pattern, return the word stored in the
// appropriate trieNode
char* get_word(trieNode *root, char *pattern);

// deletes the entire tree branching from root
void free_tree(trieNode *root);

// inserts a given word into the trie data structure.
void insertWord(trieNode* root, const char* word);

// creates a trie node with empty branches and no associated word.
trieNode* createTrieNode();
#endif
