#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
#define MAX 100
 
int values[MAX];
char operators[MAX];
 
int vtop = -1;
int otop = -1;
 
void pushValue(int x)
{
    values[++vtop] = x;
}
 
int popValue()
{
    return values[vtop--];
}
 
void pushOperator(char ch)
{
    operators[++otop] = ch;
}
 
char popOperator()
{
    return operators[otop--];
}
 
char peekOperator()
{
    return operators[otop];
}
 
int precedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;
 
    if (ch == '+' || ch == '-')
        return 1;
 
    return 0;
}
 
int calculate(int a, int b, char op)
{
    if (op == '+')
        return a + b;
 
    if (op == '-')
        return a - b;
 
    if (op == '*')
        return a * b;
 
    if (op == '/')
        return a / b;
 
    return 0;
}
 
void performOperation()
{
    int b = popValue();
    int a = popValue();
    char op = popOperator();
 
    pushValue(calculate(a, b, op));
}
 
int main(int argc, char *argv[])
{
    int i = 0;
    char ch;
 
    if (argc < 2)
    {
        printf("Enter expression as command line argument\n");
        return 0;
    }
 
    while (argv[1][i] != '\0')
    {
        ch = argv[1][i];
 
        if (isdigit(ch))
        {
            int num = 0;
 
            while (isdigit(argv[1][i]))
            {
                num = num * 10 + (argv[1][i] - '0');
                i++;
            }
 
            pushValue(num);
            continue;
        }
 
        if (ch == '(')
        {
            pushOperator(ch);
        }
 
        else if (ch == ')')
        {
            while (peekOperator() != '(')
                performOperation();
 
            popOperator();
        }
 
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/')
        {
            while (otop != -1 &&
                   peekOperator() != '(' &&
                   precedence(peekOperator()) >= precedence(ch))
            {
                performOperation();
            }
 
            pushOperator(ch);
        }
 
        i++;
    }
 
    while (otop != -1)
        performOperation();
 
    printf("%d\n", popValue());
 
    return 0;
}