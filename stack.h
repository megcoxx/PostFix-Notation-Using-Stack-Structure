#ifndef STACK_H
#define STACK_H

#include <iostream>

namespace cop4530
{

    template <typename T>
    class Node
    {
    public:
        T value;
        Node *next;
        Node(T value);
    };

    template <typename T>
    class Stack
    {
    private:
        Node<T>* _top;
        int height;

    public:
        Stack();
        ~Stack();
        Stack(const Stack<T> &otherStack);
        Stack(Stack<T> &&otherStack);
        void clear();
        Stack<T> &operator=(const Stack<T> &otherStack);
        Stack<T> &operator=(Stack<T> &&otherStack);
        bool empty() const;
        void push(const T &x);
        void pop();
        T& top();
        const T &top() const;
        int size() const;
        void print(std::ostream &os, const Stack<T> &a);
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Stack<T> &a);

    template <typename T>
    bool operator==(const Stack<T> &a, const Stack<T> &b);

    template <typename T>
    bool operator!=(const Stack<T> &a, const Stack<T> &b);

    template <typename T>
    bool operator<=(const Stack<T> &a, const Stack<T> &b);

}

#include "stack.hpp"
#endif