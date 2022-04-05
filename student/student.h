#include <iostream>

class Student
{
    private:
        string name;
        string id; 
        double gpa;
    public:
    // contstructors
        Student (string name, string id, double gpa)
        {
            this-> name = name;
            this-> id   = id;
            this-> gpa  = gpa;
            std::cout << "[#] student created\n";
        }

        Student () { name = ""; id = ""; gpa = 0; }
    // utility functions
    // requested functions
        void print ()
        {
            cout << "Name: " << name << "\n";
            cout << "ID: "   << id   << "\n";
            cout << "GPA: "  << gpa  << "\n";
        }
        
         // compare s1.name and s2.name according to alphabitic order
        friend bool operator < (Student& s1, Student& s2 )
            { return (s1.name < s2.name);}

        friend bool operator <= (Student& s1, Student& s2 )
            { return (s1.name <= s2.name); }

        friend bool operator > (const Student& s1, const Student& s2)
            { return (s1.name > s2.name); }

        friend bool operator >= (const Student& s1, const Student& s2)
            { return (s1.name >= s2.name); }
};