#include <iostream>
#include <fstream>
#include <Student.h>
using namespace std;

class fileData{
pirvate:
		int comparisions;
		Student* arr;
		int size;
public:
	// constructors
		fileData(size){
			comparisions = 0;
			this -> size = size;
			arr = new Student[size];
		}
		FileData(){
			comparisions = 0;
			size = 0;
		}
	// utility
	Student* data() 
		{return arr;}
	void data(Student* data) 
		{arr=data;}
	void size(int num) {
		Student newArr = new Student[size];
		if (size==0) {this->size=size; return;}
		for (int i=0; i<this->size; i++) {newArr[i] = arr[i];}
	int size() 
		{return size;}
	void comparisions(int count) 
		{comparisions = count;}
	int comparisions() 
		{return comparisions;}
	}

	friend ofstream operator << (ofstream& output, fileData* data){
		output << comparisions << "\n";
		for (int i=0; i<data.size(); i++)
			{output << arr[i];}
		return output;
	}
	friend ifstream operator >> (ifstream& input, fileData* data){
		input >> data.size;
		for (int i=0; i<data.size; i++){
			input >> arr[i];
		}
	}
};
