
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctype.h>
#include <iomanip>
using namespace std;

//A struct that will hold each unique word and the number of times it has been encountered.
struct words
{
	int frequency;
	string word;
};

//This function swaps two elements in a words array
void swap(words* a, words* b)
{
	words t = *a;
	*a = *b;
	*b = t;
}

//This function places the last element as the pivot,
//and finds the correct placement for the pivot
//leaving all smaller elements to the right and larger elements to the left
int partition(words arr[], int low, int high)
{
	words pivot = arr[high]; 
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		//If element is greater than pivot, it is moved to the correct side
		if (arr[j].frequency > pivot.frequency)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


void quickSort(words arr[], int low, int high)
{
	if (low < high)
	{
		
		int p = partition(arr, low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(arr, low, p - 1);
		quickSort(arr, p + 1, high);
	}
}

int main() {

	ifstream input ("input.txt");
	
	map<string, int> wordsCount;


	while (input.good())
	{
		// Store the next word in the file in a local variable.
		string word;
		input >> word;
		// Remove punctuation and make all characters lowercase. 
		for (int i = 0, length = word.size(); i < length; i++)
		{
			word[i] = tolower(word[i]);
			if (ispunct(word[i]))
				word.erase(i--, 1);
			length = word.size();
		}

		//If this is a new word, store it in the wordsCount map and initialize the amount of times seen as 1
		if (wordsCount.find(word) == wordsCount.end()) 
			wordsCount[word] = 1; 
		else // If this word is already in the map, increment the number of times we have seen it
			wordsCount[word]++; 
	}
	input.close();

	const int size = wordsCount.size();
	//Creates a words array
	words * mapCopy = new words[size];


	typedef std::map<string, int>::iterator iterator;
	
	//Iterates through the map, and copies this information onto our array
	int i = 0;
	for (iterator p = wordsCount.begin(); p != wordsCount.end(); p++)
	{
		mapCopy[i].word = p->first;
		mapCopy[i].frequency = p->second;
		i++;
	}
	
	//Calls the quickSort function to sort the array.
	quickSort(mapCopy, 0, size - 1);

	//Create the output file
	ofstream output;
	output.open("output.txt");

	//Loop through the array and write the information to the output file in the appropriate format
	for (int i = 0; i < size; i++)
	{
		output << setw(10) <<  mapCopy[i].word << " | ";

		for (int i = 0; i < mapCopy[i].frequency; i++)
		{
			output << "=";
		}
		output << " (" <<  mapCopy[i].frequency << ")" << endl;
	}
	
	output.close();
	return 0;
	
}