/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"


void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
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

    free_tree(root);
    fclose(dictionary);

    return(EXIT_SUCCESS);
}

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

void run_session(trieNode *wordTrie) {
    printf("Enter \"exit\" to quit.\n");

    char input[MAXLEN];
    char *prevInput = (char *)malloc(52);

    if (prevInput == NULL) {
        perror("Error allocating memory for prevWord");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0) {
            break;
        }

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

        strcpy(prevInput, input);
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
