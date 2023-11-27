/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE 374 HW5
   Copyright 2023 C. Andrade
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "trienode.h"

char* translate(const char* word);

void insertWord(trieNode* root, const char* word) {
    trieNode* current = root;
    char* wordNum  = translate(word);

    for (int i = 0; i < strlen(wordNum); i++) {
        char currNum = wordNum[i];
        if (current->branches[currNum - '2'] == NULL) {
            current->branches[currNum - '2'] = createTrieNode();
        }
        current = current->branches[currNum - '2'];
    }

    free(wordNum);
    if (current->word == NULL) {
        current->word = (char*)malloc(strlen(word) +1);
        if (current->word == NULL) {
            perror("Error copying words into trie");
            exit(EXIT_FAILURE);
        }
        strncpy(current->word, word, MAXLEN +2);
    } else {
        while (current->word != NULL) {
            if (current->branches[BRANCHES - 1] == NULL) {
                current->branches[BRANCHES - 1] = createTrieNode();
            }
            current = current->branches[BRANCHES - 1];
        }
        current->word = (char*)malloc(strlen(word) + 1);
        if (current->word == NULL) {
            perror("Error copying words into trie");
            exit(EXIT_FAILURE);
        }
        strncpy(current->word, word, MAXLEN +2);
    }
}

char* get_word(trieNode *root, char *pattern) {
    trieNode *current = root;

    for (size_t i = 0; i < strlen(translate(pattern)); i++) {
        char currentChar = pattern[i];

        int index;
        if (currentChar == '#') {
            index = BRANCHES - 1;
        } else {
            index = currentChar - '2';
        }

        if (current->branches[index] == NULL) {
            return NULL;
        }

        current = current->branches[index];
    }

    if (current->word != NULL) {
        return current->word;
    } else {
        return NULL;
    }
}

char* translate(const char* word) {
    char* t9Sequence = (char*)malloc((strlen(word) + 1));

    if (t9Sequence == NULL) {
        perror("Error allocating memory for T9 translation");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < strlen(word); i++) {
        char currentChar = tolower(word[i]);

        if (currentChar >= 'a' && currentChar <= 'c') {
            t9Sequence[i] = '2';
        } else if (currentChar >= 'd' && currentChar <= 'f') {
            t9Sequence[i] = '3';
        } else if (currentChar >= 'g' && currentChar <= 'i') {
            t9Sequence[i] = '4';
        } else if (currentChar >= 'j' && currentChar <= 'l') {
            t9Sequence[i] = '5';
        } else if (currentChar >= 'm' && currentChar <= 'o') {
            t9Sequence[i] = '6';
        } else if (currentChar >= 'p' && currentChar <= 's') {
            t9Sequence[i] = '7';
        } else if (currentChar >= 't' && currentChar <= 'v') {
            t9Sequence[i] = '8';
        } else {
            t9Sequence[i] = '9';
        }
    }

    t9Sequence[strlen(word)] = '\0';
    return t9Sequence;
}

trieNode* createTrieNode() {
    trieNode* node = (trieNode*)malloc(sizeof(trieNode));
    if (node == NULL) {
        perror("Error creating TrieNode");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < BRANCHES; i++) {
        node->branches[i] = NULL;
    }

    node->word = NULL;
    return node;
}

void free_tree(trieNode* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < BRANCHES; ++i) {
        free_tree(root->branches[i]);
    }

    free(root->word);
    free(root);
}
