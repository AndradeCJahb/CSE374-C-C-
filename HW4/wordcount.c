/* wordcount.c
   Counts and outputs number of words, lines, and/or chars based on
   command line options.
   CSE 374 HW4
   Copyright 2022 C. Andrade
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 500

// Declares processFile function which outputs number of lines,
// words, or chars based on command line options.
void processFile(char *filename, int statusLines, int statusWords,
                 int statusChars, int *totalLines, int *totalWords,
                 int *totalChars);

void totals(int totalLines, int totalWords, int totalChars, int statusLines,
            int statusWords, int statusChars);

// Checks for minimum number of arguments and accounts for options.
int main(int argc, char *argv[]) {
    // Checks for at least one input file
    if (argc < 2) {
        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        exit(1);
    }

    // Checks for at least one input file given that an option is within
    // the command line.
    if (argc == 2 && argv[1][0] == '-') {
        if (argv[1][1] == 'l' || argv[1][1] == 'w' ||
            argv[1][1] == 'c') {
            fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
            exit(1);
        }
    }

    // Declares variables which determine what to output
    // (Lines, Words, Chars), can be edited through options.
    int statusLines = 1, statusWords = 1, statusChars = 1, flag = 0,
            totalLines = 0, totalWords = 0, totalChars = 0;

    // Checks for options which output only number of lines,
    // words or characters.
    if (argv[1][0] == '-') {
        if (argv[1][1] == 'l') {
            statusWords = 0;
            statusChars = 0;
            flag = 1;
        } else if (argv[1][1] == 'w') {
            statusLines = 0;
            statusChars = 0;
            flag = 1;
        } else if (argv[1][1] == 'c') {
            statusLines = 0;
            statusWords = 0;
            flag = 1;
        }
    }

    // Processes through the remaining arguments/possible files through
    // processFile function.
    for (int i = flag + 1; i < argc; i++) {
        processFile(argv[i], statusLines, statusWords, statusChars,
                    &totalLines, &totalWords, &totalChars);
    }

    if (argc - flag -1 > 1) {
        totals(totalLines, totalWords, totalChars, statusLines, statusWords,
               statusChars);
    }

    return EXIT_SUCCESS;
}


// Outputs number of lines, words, or chars based on command line options.
void processFile(char *filename, int statusLines, int statusWords,
                 int statusChars, int *totalLines, int *totalWords,
                 int *totalChars) {
    // Declares FILE variable containing the current file being processed
    // for lines, words and/or chars count.
    FILE *currFile = fopen(filename, "r");

    // Checks for null/non-existent file
    if (currFile == NULL) {
        fprintf(stderr, "%s will not open. Skipping.\n", filename);
        return;
    }

    // Declares lines, words, chars variables which can be output to user
    // depending on command line options. Buffer containing first 500 chars
    // in Line is also declared.
    int lines = 0, words = 0, chars = 0;
    char buffer[MAXLINE];

    // Counts each line until end of file, if words or chars are to be
    // outputted according to possible inputted options then they will
    // also be counted.
    while (fgets(buffer, MAXLINE, currFile) != NULL) {
        lines++;
        if (statusWords || statusChars) {
            // Creates pointer to buffer which is now split into word
            // and updates chars count appropriately.
            chars += strlen(buffer);
            char *token = strtok(buffer, " \t\n");
            // Loops through each token/word until there are no more within
            // the buffer, updates words count appropriately.
            while (token != NULL) {
                words++;
                token = strtok(NULL, " \t\n");
            }
        }
    }

    // Checks if number of lines, words, or chars should be output according
    // to command line options.

    *totalChars += chars;
    *totalLines += lines;
    *totalWords += words;

    if (statusLines) {
        printf("%d", lines);
    }
    if (statusWords) {
        printf(" %d", words);
    }
    if (statusChars) {
        printf(" %d", chars);
    }
    printf(" %s\n", filename);

    fclose(currFile);
}

void totals(int totalLines, int totalWords, int totalChars, int statusLines,
            int statusWords, int statusChars) {
    if (statusLines) {
        printf("%d", totalLines);
    }
    if (statusWords) {
        printf(" %d", totalWords);
    }
    if (statusChars) {
        printf(" %d", totalChars);
    }
    printf(" total\n");
}
