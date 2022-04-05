#include <iostream>
#include <cmath>
#include <fstream>
#include <Student.h>
#include <output.h>
using namespace std;

// sort functions
template <class dataType>
int insertion_Sort (dataType arr[], int size);
template <class dataType>
int shell_sort (dataType arr[], int n);

// file functions
fileData read();
void write(fileData& data, string name);

// driver function
int main()
{
	fileData info = read();
	info.comparisions( insertion_Sort (info.data(), info.fileData::size() ) );   // unreasonable errors messages since size() is a public function
	write(info, "insertion.txt");
	info = read();
	info.comparisions(shell_sort (info.data(), info.fileData::size() ));    // same prevously mentioned error in line 22
	write (info, "shell.txt");
	return 0;
}
 
 
// sort fucntions insertion, shell with hibbards increment and quick sort
template <class dataType>
int insertion_Sort(dataType arr[], int size)
{
	int i, j, count;
	dataType key;
	for (i=1; i<size; i++){
		key = arr[i];
		j = i-1;
		// shift values greater than key to it's left
		while (j >= 0 && arr[j] > key){
			count++;
			arr[j+1] = arr[j];
			j--;
		}
		// putting the key in last shifted index
		arr[j + 1] = key;
	}
	return count;
}

 // Hibbard's increments
int hibbard_increment (int k) { return pow(2,k)-1;}
int hibbard_increment_inverse (int x) { return log2(x)-1; }

template <class dataType>
int shell_sort(dataType arr[], int n)
{
	int count;
	// Start with a big gap, then reduce the gap
	for (int gap = hibbard_increment_inverse(n); hibbard_increment(gap) > 0; gap--){
		for (int i = gap; i < n; i += 1){
			// add a[i] to the elements that have been gap sorted
			// // save a[i] in temp and make a hole at position i
			dataType temp = arr[i];
			// shift earlier gap-sorted elements up until the correct
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
				arr[j] = arr[j - gap];
				count++;
			}
			// put temp (the original a[i]) in its correct location
			arr[j] = temp;
		}
	}
	return count;
}

// file handling functions to open file, read student objects, write student objects

const string fileName="data";   // single line edit for future usage

fileData read(){
	fileData data;
	ifstream file;
	file.open(fileName, ios::app);
	file >> data;    // operator is implemented
	file.close();
	return data;
}
void write(fileData& data, string name)
{
	ofstream file;
	file.open(name, ios::out);
	file << data;     // operator is implemented
}
