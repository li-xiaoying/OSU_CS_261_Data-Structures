/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Xiaoying Li
 * Date: 12/04/2019
 */


#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}


/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
	char* word = nextWord(file);
	while (word != 0) {
		hashMapPut(map, word, 1);
		free(word);
		word = nextWord(file);
	}
	free(word);
}


/** 
 * Adapted from https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
 */
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
int levenshtein(char* s1, char* s2) {
	unsigned int x, y, s1len, s2len;
	s1len = strlen(s1);
	s2len = strlen(s2);
	unsigned int matrix[s2len + 1][s1len + 1];
	matrix[0][0] = 0;
	for (x = 1; x <= s2len; x++)
		matrix[x][0] = matrix[x - 1][0] + 1;
	for (y = 1; y <= s1len; y++)
		matrix[0][y] = matrix[0][y - 1] + 1;
	for (x = 1; x <= s2len; x++)
		for (y = 1; y <= s1len; y++)
			matrix[x][y] = MIN3(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1, matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));
	return(matrix[s2len][s1len]);
}


/**
 * Checks the spelling of the word provded by the user. If the word is spelled incorrectly,
 * print the 5 closest words as determined by a metric like the Levenshtein distance.
 * Otherwise, indicate that the provded word is spelled correctly. Use dictionary.txt to
 * create the dictionary.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
	// FIXME: implement
	HashMap* map = hashMapNew(1000);

	FILE* file = fopen("dictionary.txt", "r");
	clock_t timer = clock();
	loadDictionary(file, map);
	timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	fclose(file);

	char inputBuffer[256];
	int quit = 0;
	while (!quit)
	{
		printf("Enter a word or \"quit\" to quit: ");
		scanf("%s", inputBuffer);

		// Implement the spell checker code here..
		for (int i = 0; i < strlen(inputBuffer); i++) {
			inputBuffer[i] = tolower(inputBuffer[i]);
		}

		if (hashMapContainsKey(map, inputBuffer))
		{
			if (strcmp(inputBuffer, "quit") == 0){}
			else
			{
				printf("The inputted word %s is spelled correctly.\n", inputBuffer);
			}
		}

		else {
			printf("The inputted word %s is spelled incorrectly. Did you mean:\n", inputBuffer);
			struct HashLink* current;
			for (int i = 0; i < map->capacity; i++) {
				current = map->table[i];
				while (current != 0) {
					hashMapPut(map, current->key, -1);
					current = current->next;
				}
			}
			for (int i = 0; i < map->capacity; i++) {
				current = map->table[i];
				while (current != 0) {
					hashMapPut(map, current->key, levenshtein(inputBuffer, current->key));
					current = current->next;
				}
			}
			int candidate = 0;
			int distance = 1;
			while (candidate < 5) {
				for (int i = 0; i < map->capacity; i++) {
					current = map->table[i];
					while (current != 0 && candidate < 5) {
						if (current->value == distance) {
							printf("%s\n", current->key);
							candidate++;
						}
						current = current->next;
					}
				}
				distance++;
			}
		}

		if (strcmp(inputBuffer, "quit") == 0)
		{
			quit = 1;
		}
	}

	hashMapDelete(map);
	return 0;
}