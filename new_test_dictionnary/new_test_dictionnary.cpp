// new_test_dictionnary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Dictionary.h"

// my str
void str_copy(char source[], char dest[])
{
	int i = 0;
	while (source[i] != '\0' && i < MAX_WORD_LENGTH - 1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = source[i];
}

// my str cmp
int str_cmp(char word1[], char word2[])
{
	int i = 0;
	while (word1[i] != '\0' && word2[i] != '\0')
	{
		if (word1[i] > word2[i])
			return 1; // word 1 on top of word 2

		if (word1[i] < word2[i])
			return -1; // word 1 behind word2

		i++;
	}

	if (word2[i] != '\0')
		return -1; // word 1 behind word 2 

	if (word1[i] != '\0')
		return 1; // word 1 on top of word 2 

	return 0;
}

// right_place
int right_place(dictionary* dico, char word[])
{
	// get right index for this word
	int i = 0;
	if (dico->m_count > 0)
	{
		if (str_cmp(dico->m_words[i], word) == 0)
			return -1;


		while (str_cmp(dico->m_words[i], word) == -1)
		{
			if (i +1 > dico->m_count)
				break;
			i++;
		}
		
	}

	return i;
}

// shift top
void shift_top(dictionary* dico, int index)
{
	for (int i = index; i < dico->m_count; i++)
	{
		str_copy(dico->m_words[i + 1], dico->m_words[i]);
	}
	dico->m_count--;
}

// shift bot
void shift_bot(dictionary* dico, int index)
{
	if (index > dico->m_count)
		return;

	for (int i = dico->m_count; i > index; i--)
	{
		str_copy(dico->m_words[i - 1], dico->m_words[i]);
	}
	dico->m_count++;
}

// add_world
void add_word(dictionary* dico, char word[])
{
	// get index
	int index = right_place(dico, word);
	if (index == -1) // eject doublon
		return;

	// shift bottom to add
	shift_bot(dico, index);
	str_copy(word, dico->m_words[index]);
}

// display
void display(dictionary dico)
{
	for (int i = 0; i < dico.m_count; i++)
		printf("%d %s\n", i, dico.m_words[i]);
}

void user_add_word(dictionary* dico)
{
	printf("entrez un mot\n");
	char input[MAX_WORD_LENGTH] = {'\0'};
	scanf_s("%s", &input, sizeof(char) * MAX_WORD_LENGTH);

	add_word(dico, input);
}

void delete_word(dictionary *dico, int index)
{
	shift_top(dico, index);
}

void user_delete_word(dictionary *dico)
{
	printf("entrez un index\n");
	int index = 0;
	scanf_s("%i", &index, sizeof(int));

	delete_word(dico, index);
}

void init_2darray(char arr[MAX_LIST_SIZE][MAX_WORD_LENGTH])
{
	for (int y = 0; y < MAX_LIST_SIZE; y++)
	{
		for(int x =0; x< MAX_WORD_LENGTH ; x++)
		{
			arr[y][x] = '\0';
		}
	}
}

int main()
{
	dictionary dico;
	dico.m_count = 0;
	init_2darray(dico.m_words);

	int choice = 0;
	while (true)
	{
		//system("cls");
		printf("[1] -> Add  \n[2] -> remove \n[3] -> display \n[0] -> exit\n");

		scanf_s("%i", &choice, sizeof(int));
		switch (choice)
		{
			case  1: user_add_word(&dico); break;
			case  2: user_delete_word(&dico); break;
			case  3: display(dico); break;

			case 0:  return 0;
		default: ;
		}
	}
}
