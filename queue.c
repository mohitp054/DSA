//make linked list using queue
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include<ctype.h>
char stack[100];
int top=-1;

void push(char x)
{
    if (top < 99)
        stack[++top] = x;
}

char pop()
{
    if (top >= 0)
        return stack[top--];
    return '\0'; // Return null character for empty stack
}

int precedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '^')
        return 3;
    return 0;
}