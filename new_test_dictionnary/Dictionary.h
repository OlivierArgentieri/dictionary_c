#pragma once

#define MAX_WORD_LENGTH 30
#define MAX_LIST_SIZE 30

struct dictionary
{
	char m_words[MAX_LIST_SIZE][MAX_WORD_LENGTH];
	int m_count;
};
