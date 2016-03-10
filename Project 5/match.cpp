#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 200;

void rotateLeft(char word[][MAX_WORD_LENGTH + 1], int nRules, int pos);
void deleteAndReset(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int &nRules, int &pos);
int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules);

void documentTrimmer(char newDocument[MAX_DOCUMENT_LENGTH + 1]);
int captureWords(const char newDocument[MAX_DOCUMENT_LENGTH + 1], char wordsInDocument[][MAX_DOCUMENT_LENGTH + 1]);
int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], int nRules, const char document[]);


int main()
{
	const int nRules = 11;
	int distance[nRules] = { 3, 3, 2, 0, 1, 2, 2, 8, 3, 2, 12 };
	char word1[nRules][MAX_WORD_LENGTH + 1] = { "UCLA", "USC", "Stanford", "Cal", "uSc", "USC", "UCLA", "USC", "UCSD", "", "USC" };
	//char word2[nRules][MAX_WORD_LENGTH + 1] = { "UCLA", "Yale", "Oxford", "UCLA", "USC", "USC", "AVR", "Yale", "UCSB", "a", "b" };
	char word2[nRules][MAX_WORD_LENGTH + 1] = { "USC", "UCLA", "Stanford", "Cal", "UCla", "ucla", "Usc", "USC", "UCSB", "", "UCLA" };

	//char document[MAX_DOCUMENT_LENGTH] = "UCLA beats USC in YALE, CALL oxford and STanford7, UW cuz# AVR is UCLAsl !!! UCasdLA!!";
	char document[MAX_DOCUMENT_LENGTH] = "UCLA UCLnA @stanford7 oxford873-(1,! AVR!! UW USC YAle USC yale USc yale usc yale UCSB h hf UCSD";
	//strcat(document, "");

	int rRules = standardizeRules(distance, word1, word2, nRules);

	for (int z = 0; z < rRules; z++)
	{
		cerr << word1[z];
		for (int a = 0; a < (15 - strlen(word1[z])); a++)
			cerr << " ";
		cerr << word2[z];
		for (int b = 0; b < (15 - strlen(word2[z])); b++)
			cerr << " ";
		cerr << distance[z] << endl;
	}

	cerr << endl;
	cerr << "There are " << rRules << " Rules" << endl;
	int matchquality = determineQuality(distance, word1, word2, rRules, document);
	cerr << "Match quality is " << matchquality << endl; cerr << endl;
}


void rotateLeft(char word[][MAX_WORD_LENGTH + 1], int nRules, int pos) // This function deletes the word in position 'pos' in an array of C strings and shifts all other words one place to the left
{
	for (int index = pos; index < nRules - 1; index++)
		strcpy(word[index], word[index + 1]);
}

void deleteAndReset(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int distance[], int &nRules, int &pos) // This function deletes the entire Match Rule at position 'pos' and shifts all other Math rules to the left
{
	rotateLeft(word1, nRules, pos);
	rotateLeft(word2, nRules, pos);
	for (int index = pos; index < nRules - 1; index++)
		distance[index] = distance[index + 1];
	pos--;
	nRules--;
}

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules)
{

	for (int pos = 0; pos < nRules; pos++)
	{
		//REMOVING NON-POSITIVE DISTANCES====================================

		if (distance[pos] <= 0)
		{
			deleteAndReset(word1, word2, distance, nRules, pos);
			continue; // the continue is neccessary so that the program moves on to the next match rule
		}

		//REMOVING WORDS WITHOUT EXCLUSIVELY ALPHABETIC CHARACTERS===========

		bool onlyChar = true;

		for (int i = 0; word1[pos][i] != 0; i++)
		{
			if (!isalpha(word1[pos][i]))
			{
				deleteAndReset(word1, word2, distance, nRules, pos);
				onlyChar = false;
				break;
			}
		}

		if (word1[pos][0] == 0) // This condition ensures that word1 is not empty
		{
			deleteAndReset(word1, word2, distance, nRules, pos);
			onlyChar = false;
		}

		if (!onlyChar)
			continue; // the continue is neccessary so that the program moves on to the next match rule

		for (int j = 0; word2[pos][j] != 0; j++)
		{
			if (!isalpha(word2[pos][j]))
			{
				deleteAndReset(word1, word2, distance, nRules, pos);
				onlyChar = false;
				break;
			}
		}

		if (word2[pos][0] == 0) // This condition ensures that word2 is not empty
		{
			deleteAndReset(word1, word2, distance, nRules, pos);
			onlyChar = false;
		}

		if (!onlyChar)
			continue;

		//CONVERTING ALL UPPERCASE LETTERS TO LOWER CASE======================

		for (int k = 0; word1[pos][k] != 0; k++)
		{
			word1[pos][k] = tolower(word1[pos][k]);
		}

		for (int m = 0; word2[pos][m] != 0; m++)
		{
			word2[pos][m] = tolower(word2[pos][m]);
		}

		//REMOVING ANY SIMILAR MATCH RULES==================================

		for (int newPos = 0; newPos < nRules && newPos != pos; newPos++)
		{
			if (strcmp(word1[pos], word1[newPos]) == 0)
			{
				if (strcmp(word2[pos], word2[newPos]) == 0)
				{
					if (distance[pos] <= distance[newPos])
					{
						deleteAndReset(word1, word2, distance, nRules, pos);
						break;
					}
					else
					{
						deleteAndReset(word1, word2, distance, nRules, newPos);
						pos--;
						break;
					}
				}
			}

			if (strcmp(word1[pos], word2[newPos]) == 0)
			{
				if (strcmp(word2[pos], word1[newPos]) == 0)
				{
					if (distance[pos] <= distance[newPos])
					{
						deleteAndReset(word1, word2, distance, nRules, pos);
						break;
					}
					else
					{
						deleteAndReset(word1, word2, distance, nRules, newPos);
						pos--;
						break;
					}
				}
			}
		}
		//====================================================================
	}
	return nRules;
}

void documentTrimmer(char newDocument[MAX_DOCUMENT_LENGTH + 1]) //This function removes all non-alphabetic and non-space characters and converts uppercase letters to lowercase
{
	for (int x = 0; newDocument[x] != 0; x++)
	{
		newDocument[x] = tolower(newDocument[x]);

		if (!isalpha(newDocument[x]) && newDocument[x] != ' ' || newDocument[x - 1] == ' ' && newDocument[x] == ' ' || newDocument[0] == ' ') //The first condition checks if the character is non-alphabetic and non-space, the second condition checks if a space character has been repeated, and the third checks if the first character is a space
		{
			for (int index = x; newDocument[index] != 0; index++)
			{
				newDocument[index] = newDocument[index + 1];
			}
			x--;
		}
	}
}

int captureWords(const char newDocument[MAX_DOCUMENT_LENGTH + 1], char wordsInDocument[][MAX_DOCUMENT_LENGTH + 1]) //This function takes each word from the 'document' C string and puts it in an array of C strings called 'wordsInDocument'
{
	int pos = 0;
	int index = 0;
	int wordNo = 0;

	for (wordNo = 0; newDocument[index] != 0; wordNo++)
	{
		pos = 0;
		while (newDocument[index] != ' ' && newDocument[index] != 0)
		{
			wordsInDocument[wordNo][pos] = newDocument[index];
			pos++;
			index++;
		}
		index++;
		wordsInDocument[wordNo][pos] = 0; // This line is neccessary to mark the end of a word in this C string in an array, which was initially not assigned any value (as it was declared as an empty array of C strings)
	}

	return wordNo;
}

int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], int nRules, const char document[])
{
	char newDocument[MAX_DOCUMENT_LENGTH + 1];
	strcpy(newDocument, document);

	documentTrimmer(newDocument); 

	char wordsInDocument[MAX_DOCUMENT_LENGTH + 1][MAX_DOCUMENT_LENGTH + 1]; // Although the document is unlikely to have 1 character words or a word 200 characters long, the maximum possible dimesions have been used to define this array
	int wordCount = captureWords(newDocument, wordsInDocument);
	int quality = 0;
	bool hasQualityChanged = false;


	for (int wordPos = 0; wordPos < nRules; wordPos++)
	{
		for (int index = 0; index < wordCount; index++)
		{
			if (strcmp(wordsInDocument[index], word1[wordPos]) == 0)
			{
				for (int newIndex = index - distance[wordPos]; newIndex <= index + distance[wordPos]; newIndex++) // Ensures that the match for word2 is being searched for within a given distance
				{
					if (strcmp(wordsInDocument[newIndex], word2[wordPos]) == 0 && newIndex != index)
					{
						quality++;
						hasQualityChanged = true;
						break;
					}
				}
			}
			if (hasQualityChanged) // This check is important as it allows the program to move to the next match rule once the current match rule has been satisfied
			{
				hasQualityChanged = false;
				break;
			}
		}
	}
	return quality;
}

