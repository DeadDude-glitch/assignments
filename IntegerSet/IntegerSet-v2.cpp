#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Integerset{
private:
	int* state;
	int size;

public:
// constructors
	Integerset(){   // default
		for (int i=0; i<101; i++)
			{state[i] = 0;}
	}

	Integerset(int s){
		state = new int[s];
		for (int i=0; i<s; i++)
			{state[i] = 0;}
	}

	Integerset(const Integerset& obj){
		state = new int[101];
		for(int i=0;i<101;i++)
			state[i] = obj.state[i];
	}

// methods
	bool isInRange(int num){
		if (num >= 0 && num <=100)
			{return true;}
		return false;
	}

	bool insertElement(int element){
		if (isInRange(element)){
			state[element] = 1;
			return true;
		}
		return false;
	}

	bool deleteElement(int element){
		if (isInRange(element)){
			state[element] = 0;
			return true;
		}
		return false;
	}

	Integerset unionOfSets(const Integerset& f){
		Integerset un(size*2);
		for (int i = 0; i <= size; i++)
			{un.state[i] = state[i];}
		for (int k = size+1; k <= size*2; k++) 
			{un.state[k] = f.state[k];}
		return un;
	}

	Integerset intersectionOfSets(const Integerset& l){
		Integerset in(size);
		for (int i = 0; i <= size; i++)
			{in.state[i] = state[i];}
		for (int k = 0; k <= size; k++) {
			if (in.state[k] == l.state[k])
				{in.state[k] = l.state[k];}
		}
		return in;
	}

	void printSet(){
		cout << "[";
		for(int i=0; i<101; i++){
			if (state[i]>0)
				{cout << i << " ";} 
		}
		cout << "]" << endl;
	}

	bool isEqualTo(const Integerset& e ){
		int counter_1 = 0;
		int counter_2 = 0;
		for (int i = 0; i < 101; i++){
			if (state[i] == 1) {counter_1++;}
		}
		for (int j = 0; j < 101; j++){
			if (state[j] == e.state[j])
				{counter_2++;}
		}
		if(counter_1 == counter_2)
			{return true;}
		else
			{return false;}
	}

// operators
	Integerset operator-(const Integerset& x){
		Integerset temp(size);
		for (int i = 0; i <= size; i++)
			{temp.state[i] = state[i];}
		for (int k = 0; k <= size; k++){
			if (temp.state[k] != x.state[k])
				{temp.state[k] = x.state[k];}
		}
		return temp;
	}

	Integerset operator!(){
		Integerset solution;
		for (int i=0; i<101; i++){
			if (state[i]==0)
				{solution.state[i]=1;}
			else if (state[i]==1)
				{solution.state[i]=0;}
		}
		return solution;
	}
};

int main()
{
	cout << "[*] driver program initiated" << endl;
	// testing constructors
	cout << "[+] creating object" << endl;
	Integerset s1;
	int input;
	cout << "[+] filling the set" << endl;
	for (int i=0; i<5; i++){
		cout << "Enter digit >>> ";
		cin >> input;
		cout << endl;
		s1.insertElement(i);
	}
	cout << "[!] printing created object" << endl;
	s1.printSet();
	return 0;
}
