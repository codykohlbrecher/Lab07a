// WordCount.cpp

#include "WordCount.h"
#include <sstream>
using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total = 0;
    for (size_t i = 0; i < CAPACITY; ++i) 
	{
        for (const auto& j : table[i]) 
		{
            total += j.second;
        }
    }
    return total;
}

int WordCount::getNumUniqueWords() const 
{
	int total = 0;
    for (size_t i = 0; i < CAPACITY; ++i)
	{
        total += table[i].size();
    }
    return total;
}

int WordCount::getWordCount(std::string word) const 
{
	string validWord = makeValidWord(word);
    if (validWord == "") 
	{
		return 0;
	}

    int index = hash(validWord);
    const vector<pair<string, int>>& bucket = table[index];

    for (const auto& j : bucket) 
	{
        if (j.first == validWord) 
		{
            return j.second;
        }
    }

    return 0;
}
	
int WordCount::incrWordCount(std::string word)
 {
	string validWord = makeValidWord(word);
    if (validWord == "") 
	{
		return 0;
	}

    int index = hash(validWord);
    vector<pair<string, int>>& bucket = table[index];

    for (auto& j : bucket)
	{
        if (j.first == validWord) 
		{
			j.second++;
            return j.second;
        }
    }
	bucket.push_back(std::make_pair(validWord, 1));
    return 1;
}

int WordCount::decrWordCount(std::string word) 
{
 
	string validWord = makeValidWord(word);
    if (validWord == "") 
	{
		return -1;
	}

    int index = hash(validWord);
    vector<pair<string, int>>& bucket = table[index];
	for (size_t i = 0; i < bucket.size(); ++i)
    {
        if (bucket[i].first == validWord)
        {
            if (bucket[i].second == 1)
            {
                bucket.erase(bucket.begin() + i);  
                return 0;
            }
            else
            {
                bucket[i].second--;
				return bucket[i].second;
            }
        }
    }
    return -1;
}


bool WordCount::isWordChar(char c) 
{
	return isalpha(c);
}

std::string WordCount::makeValidWord(std::string word) {
	std::string str = "";
	size_t i = 0;
	for(char c: word)
	{
		
		if(isalpha(c))
		{
			str += tolower(c);
		}
		else if((c == '\'' || c == '-') && i > 0 && i < word.length() - 1 && isalpha(word[i - 1]) && isalpha(word[i + 1]))
		{
			str += c;

		}
		i++;
	}

	if((str.empty() || !isalpha(str.front()) || !isalpha(str.back()))) 
	{
        return "";
    }
	return str;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const
 {
    std::vector<std::pair<std::string, int>> total;

    for (int i = 0; i < CAPACITY; ++i)
	 {
        for (const auto &entry : table[i])
		{
            total.push_back(entry);
        }
    }

    std::sort(total.begin(), total.end());

    for (const auto &entry : total)
	{
        out << entry.first << "," << entry.second << std::endl;
    }
}


void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
    std::vector<std::pair<std::string, int>> total;

    for (int i = 0; i < CAPACITY; ++i)
	 {
        for (const auto &entry : table[i]) 
		{
            total.push_back(entry);
        }
    }

    std::sort(total.begin(), total.end(),
        [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
		{
            if (a.second != b.second)
                return a.second > b.second;  // Higher count comes first
            return a.first < b.first;        // Tie: sort alphabetically
        }
    );

    for (const auto &entry : total) 
	{
        out << entry.first << "," << entry.second << std::endl;
    }
}


void WordCount::addAllWords(std::string text) {
	std::stringstream ss(text);
	std::string word;
	while (ss >> word) 
	{
		std::string validWord = makeValidWord(word);
		if (!validWord.empty())
		{
			incrWordCount(validWord);
		}
	}
	
}
