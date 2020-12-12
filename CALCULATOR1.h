//
// Created by Hamidou Wara Ballo on 5/10/20.
//

#ifndef STACK_PROJECT_1_CALCULATOR1_H
#define STACK_PROJECT_1_CALCULATOR1_H
#include<string>
using namespace std;
int calculate(char Ops, int Value1 , int Value2);
int precedent(char ch);
bool is_Operator(char c);
void evaluate();
#endif //STACK_PROJECT_1_CALCULATOR1_H
