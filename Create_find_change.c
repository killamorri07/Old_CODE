#include <stdio.h>
#include <string.h>
//Finding and change the word from original input setences.
#define MAX_LENGTH 1000

int replaceWords(char sentence[], char find[], char replace[], char newSentence[]) {
    char* position;
    int replacedCount = 0;
    int lengthDifference = 0;
    int newSentenceIndex = 0;

    // Find the first occurrence of the word to replace
    while ((position = strstr(sentence, find)) != NULL) {
        // Calculate the length difference before and after replacement
        lengthDifference += strlen(replace) - strlen(find);

        // Check if the replacement word is longer
        if (strlen(replace) > strlen(find)) {
            // Copy the part of the original sentence before the replaced word
            strncpy(newSentence + newSentenceIndex, sentence, position - sentence);
            newSentenceIndex += position - sentence;

            // Copy the replacement word to the new sentence
            strcpy(newSentence + newSentenceIndex, replace);
            newSentenceIndex += strlen(replace);

            // Move the sentence pointer to the next character after the replaced word
            sentence = position + strlen(find);
        } else {
            // Copy the part of the original sentence before and including the replaced word
            strncpy(newSentence + newSentenceIndex, sentence, position - sentence + strlen(find));
            newSentenceIndex += position - sentence + strlen(find);

            // Move the sentence pointer to the next character after the replaced word
            sentence = position + strlen(find);
        }

        replacedCount++;
    }

    // Copy the remaining part of the original sentence to the new sentence
    strcpy(newSentence + newSentenceIndex, sentence);
    newSentenceIndex += strlen(sentence);

    // Add null terminator to the new sentence
    newSentence[newSentenceIndex] = '\0';

    return newSentenceIndex;
}

int main() {
    char inputSentence[MAX_LENGTH];
    char inputFind[MAX_LENGTH];
    char inputReplace[MAX_LENGTH];
    char newSentence[MAX_LENGTH * 2]; // Increased buffer size to handle potential expansion

    //printf("Enter an English sentence: ");
    fgets(inputSentence, MAX_LENGTH, stdin);

   // printf("Enter the word to find: ");
    fgets(inputFind, MAX_LENGTH, stdin);

    //printf("Enter the replacement word: ");
    fgets(inputReplace, MAX_LENGTH, stdin);

    // Remove newline characters
    inputSentence[strcspn(inputSentence, "\n")] = '\0';
    inputFind[strcspn(inputFind, "\n")] = '\0';
    inputReplace[strcspn(inputReplace, "\n")] = '\0';

    int newLength = replaceWords(inputSentence, inputFind, inputReplace, newSentence);

    printf("Modified Sentence:\n%s\n", newSentence);

    return 0;
}
