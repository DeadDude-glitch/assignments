#include <iostream>
#include <cmath>
#include <student.h>
using namespace std;
/*
    TODO:
        // create template functions
            // (merge or quick)
            // quadratic sorting algorithm
*/

// sort functions
template <class dataType>
dataType insertion_Sort (dataType arr[], int size);
template <class dataType>
dataType shell_sort (dataType arr[], int n);

int main()
{
    cout << "no errors yet" << endl;
    return 0;
}

template <class dataType>
dataType& insertion_Sort(dataType arr[], int size)
{
	int i, j; 
    dataType key;

	for (i=1; i<size; i++){
		key = arr[i];
		j = i-1;
		// shift values greater than key to it's left
		while (j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j--;
		}
		// putting the key in last shifted index
		arr[j + 1] = key;
	}
	return arr;
}

 // Hibbard's increments
int hibbard_increment         (int k) { return 2**k-1; }
int hibbard_increment_inverse (int x) { return log2(x)-1; }


template <class dataType>
dataType shell_sort(dataType arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = hibbard_increment_inverse(n); hibbard_increment(gap) > 0; gap--)
    {
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            dataType temp = arr[i];
 
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;           
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
             
            // put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}