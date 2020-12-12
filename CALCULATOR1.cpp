//
// Created by Hamidou Wara Ballo on 5/10/20.
//

#include "CALCULATOR1.h"
#include<iostream>
#include<stack>
#include <regex>
using namespace std;
//Calculate two values
int calculate(char Ops, int Value1 , int Value2)
{
    if(Ops == '+')
    {
        return Value1 + Value2;
    }
    else if(Ops == '-')
    {
        return Value1 - Value2 ;
    }
    else if(Ops == '*')
    {
        return Value1 * Value2;
    }
    else if(Ops == '/' || Value2>0)
    {
        return Value1/Value2;
    }
    return 0;
}

//set the precedent of the operator.
int precedent(char c)
{
    switch (c)
    {
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        default: return -1;
    }
}

//Check if the character is an operator
bool is_Operator(char c)
{
    return ( c == '+' || c == '-' || c == '*' || c == '/' ||c== '('|| c==')'||c== '['|| c==']'||c== '{'|| c=='}');
}

//Checks if the parenthesis match up
//From the professor repl.it Stack_Project
bool checkParenthesis(const string& S){
    int parenthesis=0;
    int block=0;
    int brace=0;

    for (char i : S){
        switch (i) {
            case '(':
                parenthesis++;
                break;
            case ')':
                parenthesis--;
                break;
            case '[':
                block++;
                break;
            case ']':
                block--;
                break;
            case '{':
                brace++;
                break;
            case '}':
                brace--;
                break;
            default:
                break;
        }

    }
    // check if the parenthesis match
    if(parenthesis==0 && block==0 && brace==0){
        cout <<"Parenthesis correct"<< endl;
        return true;
    }else{
        cout<< "Parenthesis error. Please re enter"<< endl;

    }
    return false;
}

//Makes sure that only number from 0-9 and parenthesis are accepted
//From the professor repl.it Stack_Project
bool inputValidation(const string& S){

    if (regex_match(S,regex("^[-*+/()\[\\]\{\\}0-9]+$")))
    {
        return true;
    }
    cout<<"Invalid Expression"<< endl;
    return false;
}

//Evaluates the arithmetic expression
void evaluate()
{
    stack<char> Operators;
    stack<int> Numbers;
    string S;
    while(S!="N")
    {
        cout << "Enter the equation(+,-,*,/,()). Enter N to exit." << endl;
        getline(cin,S);
        if(checkParenthesis(S) && inputValidation(S))
        {
            int K = 0;
            while (S[K] != '\0')
            {

                //Check if the character is a digit and transforms it in to a number
                if (isdigit(S[K]))
                {
                    int val = 0;
                    int x = K;
                    while (isdigit(S[x]))
                    {
                        val = (val * 10) + (int) (S[x] - '0');// in case more than one digits
                        x++;
                    }
                    Numbers.push(val);
                }


                //Steps to take when we encounter an operator
                else if (is_Operator(S[K]))
                {

                    //Ignore spaces between the characters
                    if (S[K] == ' ')
                    {

                    }

                    //Runs when we encounter an open parenthesis
                    else if (S[K] == '(' || S[K] == '[' || S[K] == '{')
                    {
                        Operators.push(S[K]);
                    }

                    //When encounter a closed parenthesis
                    else if (S[K] == ')' || S[K] == ']' || S[K] == '}')
                    {

                        //Calculates until the top of the stack is open parenthesis'('
                        // I try to add brackets just to add something extra but it wasn't working when I added (||Operators.top() != '(')
                        //to the while loop.
                        while (Operators.top() != '(')
                        {
                            int right_num = Numbers.top();
                            Numbers.pop();
                            int left_num = Numbers.top();
                            Numbers.pop();
                            int answer = calculate(Operators.top(), left_num, right_num);
                            Numbers.push(answer);
                            Operators.pop();
                        }
                        Operators.pop();
                    }

                    //Calculate an expression depending on the precedent
                    else
                    {
                        int prev_precedent = precedent(S[K]);
                        while (!Operators.empty() && precedent(Operators.top()) >= prev_precedent)
                        {
                            int right_num = Numbers.top();
                            Numbers.pop();
                            int left_num = Numbers.top();
                            Numbers.pop();
                            int answer = calculate(Operators.top(),  left_num, right_num);
                            Numbers.push(answer);
                            Operators.pop();
                        }
                        Operators.push(S[K]);
                    }
                }
                K++;
            }
            //Takes care of the operator left in the Operators stack
            while (!Operators.empty())
            {
                int right_num = Numbers.top();
                Numbers.pop();
                int left_num = Numbers.top();
                Numbers.pop();
                int answer = calculate(Operators.top(), left_num, right_num);
                Numbers.push(answer);
                Operators.pop();
            }
            //Prints the value left in the Number stack and that is the result.
            cout << "The result is: " << Numbers.top() << endl;
        }

    }
}
