#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

int precedence(const string &operate)
{
    if (operate == "+" || operate == "-")
    {
        return 1;
    }
    if (operate == "*" || operate == "/")
    {
        return 2;
    }
    return 0;
}

string infixToPostfix(const string &infix)
{
    cop4530::Stack<string> operatorStack;
    string output;
    istringstream inputStream(infix);
    string token;

    if(infix[0]== '+' ||infix[0]== '-' ||infix[0]== '*' ||infix[0]== '/'){
        return "Error: Missing operands in the expression.";
    }

    while (inputStream >> token)
    {
        if (isdigit(token[0]) || isalpha(token[0]))
        {
            output += token + " ";
        }
        else if (token == "(")
        {
            operatorStack.push(token);
        }
        else if (token == ")")
        {
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                output += operatorStack.top() + " ";
                operatorStack.pop();
            }
            if (!operatorStack.empty())
                operatorStack.pop();
        }
        else
        {
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token))
            {
                output += operatorStack.top() + " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty())
    {
        output += operatorStack.top() + " ";
        operatorStack.pop();
    }

    if(output[-1] == '('){
        return "Error: Infix expression " + infix + " has mismatched parens!";
    }

    return output;
}

string evaluatePostfix(string postfix)
{
    istringstream inputStream(postfix);
    string token;
    cop4530::Stack<float> operandStack;
    while (inputStream >> token)
    {
        if (isalpha(token[0]) || token[0] == '_')
        {
            return postfix + "= " + postfix;
        }
        if (token != "*" && token != "/" && token != "+" && token != "-")
        {
            operandStack.push(stof(token));
        }
        else
        {
            if (operandStack.size() < 2)
            {
                return "Error: Missing operands in the expression.";
            }
            float right = operandStack.top();
            operandStack.pop();
            float left = operandStack.top();
            operandStack.pop();
            float result;
            if (token == "-")
            {
                result = left - right;
            }
            if (token == "+")
            {
                result = left + right;
            }
            if (token == "*")
            {
                result = left * right;
            }
            if (token == "/")
            {
                result = left / right;
            }
            operandStack.push(result);
        }
    }
    if (operandStack.size() > 1)
    {
        return "There was an error because there are too many operands.";
    }
    if (operandStack.size() == 0)
    {
        return "0";
    }

    return postfix + "= " + to_string(operandStack.top());
}

int main()
{
    string input;

    while (true)
    {
        cout << "Enter infix expression ('exit' to quit): ";
        getline(cin, input);
        cout<<input<<endl;

        if (input == "exit")
        {
            cout << "Exiting program." << endl;
            break;
        }

        string postfix = infixToPostfix(input);
        if(postfix.find("Error") == std::string::npos){
        cout << "Postfix expression: " << postfix << endl;
        cout << "Postfix evaluation: " << evaluatePostfix(postfix) << endl;
        }
        else{
            cout<< postfix <<endl;
        }
    }
    return 0;
}