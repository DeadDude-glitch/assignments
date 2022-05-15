#include <iostream>
#include <cmath>
#include "StackSLL.h"
#include "QueueSLL.h"
#include "SLL.h"
using namespace std;

bool chkBalanced (string text); // done
template <class T>
void reverseQueue(QueueSLL<T>& q); // done
template <class T>
bool moveNthElem (QueueSLL<T>& Q, int n);
string convertToBinary (int value); // done
string convertInfixToPostfix (string text); // done
int evaluatePostfix (string text);

// function oriented design functions (not required for grades)
int displayOptions(); // done
template <class T>
void fillQueue(QueueSLL<T>& queue); 
bool isOperator(char);  
bool isOperand(char);  
bool eqlOrhigher(char, char);  

int main() 
{
    bool forever = true;
    string expression;
    int num = 0;
    QueueSLL<double> q;
    while (forever){
        
        switch (displayOptions())
        {
            // user forgot to enter digit
            case 0:
                cout << "please choose one of the following options!" << endl;
                break;

            case 1:
            // read expression
                cout << "expression:\t"; 
                cin  >> expression;
            // return answer
                if (chkBalanced (expression)) 
                    cout << "the expression is balanced\n";
                else 
                    cout << "the expression is not balanced\n";
                cin.ignore();
                break;
            
            case 2:
                cout << "number:\t";
                cin >> num;
                cout << convertToBinary (num) << endl;
                cin.ignore();
                break;

            case 3: 
                cout << " Enter an infix expression: ";  
                cin >> expression;    
                cout << "\n Infix   expression:\t"   << expression;  
                cout << "\n Postfix expression:\t" << convertInfixToPostfix (expression);   
                cout << "\n Postfix Evaluation:\t" << evaluatePostfix (convertInfixToPostfix (expression));
                cout << endl;
                cin.ignore();   
                break;

            case 4:
                fillQueue(q);
                cout << "enter N value:\t";
                cin >> num;
                cout << endl;
                if (moveNthElem (q, num)) 
                    cout << "\n[!] done" <<endl;
                else 
                    cout << "\n[!] element not found" << endl;
                q.clear();
                break;

            case 5:
                fillQueue(q);
                //cout << "queue:\t\t" << q.getList() << "\n"; // does not print the list elements but memory locations and sometimes errors
                reverseQueue(q);
                //cout << "reverse queue:\t" << q.getList() << endl;
                q.clear();
                break;

            case 99:
                forever = false;
                break;

            default:
                cout << "[!] INVALID INPUT [!]" << endl;
                break;
        }
    } 
    cout << "[~] process stopped, program haulted as planned." << endl;
    return 0;
}



























/////////////////////////////////////////////////////////////////
/// not requested functions, written for clean code prerequest
///////////////////////////////////////////////////////////////

// display options of user and get his interaction
int displayOptions()
{
    // pirnt menu of options line by line
        cout << "[01] check for balanced brackets\n";
        cout << "[02] convert to binary\n";
        cout << "[03] convert infix to postfix  expression and evaluate\n";
        cout << "[04] move Nth element to front in a queue of strings\n";
        cout << "[05] reverse elements of a queue of doubles\n";
        cout << "[99] EXIT";
        cout << endl;
    // read user input
        int option = 0;
        cout << "Enter selected option number >>";
    // ask again about options if error is found
        try{
            cin  >> option;
            return option;
            throw;
        }
        catch(...){
            cout << "[!] INVALID INPUT [!]" << endl;
            return displayOptions();    
        }
}

// fill a queue 
template <class T>
void fillQueue(QueueSLL<T>& queue)
{
    int iterations;
    T tmp;
    cout << "number of elements: "; cin >> iterations;
    for (int i=1; i <= iterations; i++)
    {
        cout << "enter the " << i <<" element: ";
        cin >> tmp;
        queue.enqueue(tmp);
        //cin.ignore();
    }
}


// If the symbol is operator, it returns true, otherwise false. */  
bool isOperator(char c)  
{  
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' )  
    return true;     
    return false;  
}  
  
// validate operands
// character is  operand --> true
// character not operand --> false  
bool isOperand(char c)  
{  
    // Define the character in between A to Z. If not, it returns False.  
        if( c >= 'A' && c <= 'Z')  
            return true;  
    // Define the character in between a to z. If not, it returns False. 
        if (c >= 'a' && c <= 'z')  
            return true;  
    // Define the character in between 0 to 9. If not, it returns False. 
        if(c >= '0' && c <= '9')   
            return true;  
        return false;  
}  

// define the priorty level to the operator.  
int priority(char op)  
{  
    if(op == '+' || op == '-')
        return 1;  
    if (op == '*' || op == '/')  
        return 2;  
    if(op == '^')
        return 3;       
    return 0; 
} 

// compare two operator's priorty in infix expression
// if operator 1 priorty > operator 2 priorty return true
bool eqlOrhigher (char op1, char op2)  
{  
    int p1 = priority(op1);  
    int p2 = priority(op2);  
    if (p1 == p2){  
        if (op1 == '^' )  
            return false;  
        return true;  
    }  
    return  (p1>p2 ? true : false);  
}  



























///////////////////////////////////////////////////////////
// requested functions (were required in the assignment)
/////////////////////////////////////////////////////////

// uses a stack to check if the brackets entered within an expression are balanced
// The brackets handled should include { } ,< > , [ ], ( )
bool chkBalanced (string text)
{
    StackSLL<char> var;
    char starter, terminator;
    int counter = 0;
    // Traverse the string characters
        do{
            starter = text[counter];
        // fill the stack with the starting brackets
            if(starter == '(' || starter == '[' || starter == '{' || starter == '<')
            {
                var.push(starter);
            }
        // removes the starting bracket if found its terminator
            else if(starter == ')' || starter == ']' || starter == '}' || starter == '>')
            {
                terminator = var.top();
                var.pop();
                // if the poped terminator bracket != the pushed starting bracket --> return false 
                if ( (starter == ')' && terminator != '(' ) || (starter ==']' && terminator != '[' ) || (starter=='}' && terminator!='{') )
                    {return false;}
            }
        // moves to the next value    
            counter++;
    }while (counter < text.length());
    
    // stack empty   -->  true
    // stack ! empty -->  false    
        if (var.isEmpty ()) 
            {return true ;}
        return false;
}

// uses a stack to convert a decimal number to a binary number returned as a string
string convertToBinary (int value)
{
    // calculating the size of the required string to increase preformance
        int size = floor (log2 (value));
    // converting into binary by flipping all the a 1s smaller than the remainder of the value
        StackSLL <char> stack;
        while (size>0 || value>0)
        {
            if (pow(2,size) <= value){
                stack.push('1');
                value -= pow(2,size--);
            }
            else {
                stack.push('0');
                size--;
            }
        }
    // concatinate all stack characters into the returning string 
    string binary = "";
    while (!stack.isEmpty()) {binary += stack.pop();}
    return binary;
}

// reverse the Queue nodes by exploiting the first-in-last-out logic of the stack, and its inverse last-in-first-out of the queue
template <class T>
void reverseQueue (QueueSLL<T>& queue)
{
    StackSLL <T> stack;
    // push all queue nodes into the stack
        while ( !queue.isEmpty() ) {
            stack.push (queue.dequeue());
        }
    // enqueue all the stack nodes back into the queue
        while ( !stack.isEmpty() ) {
            queue.enqueue (stack.pop());
        }
}

int evaluatePostfix (string text)
{
    StackSLL<int> stack;
    int i;
    // check each character
    for (i = 0; text[i]; ++i)
    {
        // If  character is an operand,
        // push it to the stack.
            if (isdigit(text[i])){
                // turn the char datatype into int datatype then
                // push it into the stack
                    stack.push(text[i] - '0');
            }
        // If character is an operator, pop two
        // elements from stack apply the operator
            else
            {
                switch (text[i])
                {
                case '+': stack.push ( stack.pop() + stack.pop()); break;
                case '-': stack.push ( stack.pop() - stack.pop()); break;
                case '*': stack.push ( stack.pop() * stack.pop()); break;
                case '/': stack.push ( stack.pop() / stack.pop()); break;
                case '^': stack.push ( pow(stack.pop() , stack.pop()) ); break;
                }
            }
    }
    return stack.pop();
}

  
// convert the infix expression to the postfix expression of the Stack  
string convertInfixToPostfix(string infix)  
{  
    StackSLL <char> S;  
    string postfix ="";    
    char ch;  
    
    S.push( '(' );  
    infix += ')';  
    
    for(int i = 0; i<infix.length(); i++)  
    {  
        ch = infix[i];  
        
        // empty space condition
            if(ch == ' ')  
                continue;  
        // start brackets encounter
            else if(ch == '(')  
                S.push(ch);  
        // add oprand to the string if found
            else if(isOperand(ch))  
                postfix += ch;  
        // operators encounter
            else if(isOperator(ch))  
            {
                while(!S.isEmpty() && eqlOrhigher(S.top(), ch))  
                {  
                    postfix += S.top();  
                    S.pop();  
                }  
                S.push(ch);  
            }
        // if terminal bracket encountered
            else if(ch == ')')  
            {
                // add characters to postfix till the stack is empty or a new starting bracket is found
                    while(!S.isEmpty() && S.top() != '(')  
                    {  
                        postfix += S.top();  
                        S.pop();  
                    }  
                    S.pop();  
            }  
    }  
    return postfix;  
} 

template <class T>
bool moveNthElem (QueueSLL<T>& Q, int n)
{
    bool found = false;
    QueueSLL<T> temp, hold;
    // keep empty original queue
    while (!Q.isEmpty()){
        // if at nth element enque into the temp queue
        if (n==0)
        {
            temp.enqueue(Q.dequeue());
            found = true;
        }
        // store element in another queue
        else 
            hold.enqueue(Q.dequeue());
    }
    if (found){
        // empty the hold queue into the temp queue
            while (!hold.isEmpty())
                {temp.enqueue(hold.dequeue());}
        // copy the temp queue into the orignal queue
            while (!temp.isEmpty())
                {Q.enqueue(temp.dequeue());}
    }
    else{
        // undo dequeue effect
            while (!hold.isEmpty())
                {Q.enqueue(hold.dequeue());}
    }
    return found;
}


