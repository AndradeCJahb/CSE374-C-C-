/* tnine.c is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE 374 HW5
   Copyright 2023 C. Andrade
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

void run_session(trieNode *wordTrie);

// Ensures that user entered Dictionary is valid and returns corresponding
// word when given a user inputted t9 code and/or sequence of '#' characters.
int main(int argc, char **argv) {
	
    // Stores the dictionary file required to create trie structure.
    FILE *dictionary = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        dictionary = fopen(argv[1], "r");
        if (!dictionary) {
            fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    trieNode* root = build_trie(dictionary);
    run_session(root);

    // frees data from created trie and closes dictionary file.
    free_tree(root);
    fclose(dictionary);

    return(EXIT_SUCCESS);
}

// Builds trie data structure by inserting every word within valid
// dictionary file into trie.
trieNode* build_trie(FILE *dict) {
    trieNode* root = createTrieNode();
    if (!root) {
        perror("Error creating TrieNode");
        exit(EXIT_FAILURE);
    }

    char buffer[MAXLEN + 1];

    while (fgets(buffer, sizeof(buffer), dict) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertWord(root, buffer);
    }

    return root;
}

// Runs interactive session where user can input t9 codes and be returned
// corresponding words, exits upon user request.
void run_session(trieNode *wordTrie) {
    printf("Enter \"exit\" to quit.\n");
	
    // Stores future user inputs to retrieve words from trie structure.
    char input[MAXLEN];
	
    // Stores previous valid t9 sequence input, ensures usability of
    // '#' to reach other t9onyms.
    char *prevInput = (char *)malloc(52);
    if (prevInput == NULL) {
        perror("Error allocating memory for prevWord");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n");
		
        // Ensures the user input is valid and formats input to ensure/
        // usability with other functions.
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0) {
            break;
        }
		
        // Stores pointer to word which will be returned to user if
        // t9onym is found.
        char *word = NULL;
        if (strcmp(input, "#") != 0) {
            word = get_word(wordTrie, input);
        } else {
            if (prevInput == NULL) {
                printf("There are no more T9onyms\n");
            } else {
                word = get_word(wordTrie, strcat(prevInput, "#"));
            }
        }
		
        // Updates previous input to ensure '#' functionality.
        strncpy(prevInput, input, strlen(input) +1);
		
        if (word != NULL) {
            printf("'%s'\n", word);
        } else if (strchr(input, '#')) {
            printf("There are no more T9onyms\n");
        } else {
            printf("Not found in the current dictionary.\n");
        }
    }
    free(prevInput);
}
