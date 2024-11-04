#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h" // Include the header file for declarations

namespace cop4530
{

    template <typename T>
    Node<T>::Node(T value)
    {
        this->value = value; // Use this-> to access class member
        next = nullptr;
    }

    template <typename T>
    Stack<T>::Stack()
    {
        _top = nullptr;
        height = 0;
    }

    template <typename T>
    Stack<T>::~Stack()
    {
        clear(); // Reuse clear function for cleanup
    }

    template <typename T>
    Stack<T>::Stack(const Stack<T> &otherStack)
    {
        _top = nullptr;
        height = 0;

        if (otherStack._top == nullptr)
        {
            return;
        }

        Node<T> *currentOther = otherStack._top;
        _top = new Node<T>(currentOther->value);
        Node<T> *currentNew = _top;
        currentOther = currentOther->next;

        while (currentOther != nullptr)
        {
            Node<T> *newNode = new Node<T>(currentOther->value);
            currentNew->next = newNode;
            currentNew = newNode;
            currentOther = currentOther->next;
        }
    }

    template <typename T>
    Stack<T>::Stack(Stack<T> &&otherStack)
    {
        _top = otherStack._top;
        height = otherStack.height;
        otherStack._top = nullptr;
        otherStack.height = 0;
    }

    template <typename T>
    void Stack<T>::clear()
    {
        Node<T> *current = _top;
        Node<T> *temp;

        while (current != nullptr)
        {
            temp = current;
            current = current->next;
            delete temp;
        }

        _top = nullptr;
        height = 0;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator=(const Stack<T> &otherStack)
    {
        if (this == &otherStack)
        {
            return *this;
        }

        clear(); // Clean up existing nodes

        Node<T> *currentOther = otherStack._top;
        Node<T> *previousNew = nullptr; // Correct type

        while (currentOther != nullptr)
        {
            Node<T> *newNode = new Node<T>(currentOther->value);
            if (_top == nullptr)
            {
                _top = newNode;
            }
            else
            {
                previousNew->next = newNode;
            }
            previousNew = newNode;
            currentOther = currentOther->next;
        }

        return *this;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator=(Stack<T> &&otherStack)
    {
        if (this == &otherStack)
        {
            return *this;
        }

        clear(); // Clean up existing nodes

        _top = otherStack._top;
        height = otherStack.height;
        otherStack._top = nullptr;
        otherStack.height = 0;

        return *this;
    }

    template <typename T>
    bool Stack<T>::empty() const
    {
        return height == 0; // Simplified return
    }

    template <typename T>
    void Stack<T>::push(const T &x)
    {
        Node<T> *newNode = new Node<T>(x);
        newNode->next = _top;
        _top = newNode;
        height++;
    }

    template <typename T>
    void Stack<T>::pop()
    {
        if (height == 0)
        {
            return;
        }
        Node<T> *temp = _top;
        _top = _top->next;
        delete temp;
        height--;
    }

    template <typename T>
    T &Stack<T>::top()
    {
        if (height == 0)
        {
            throw std::out_of_range("Stack is empty, there is no top.");
        }
        return _top->value;
    }

    template <typename T>
    const T &Stack<T>::top() const
    {
        if (height == 0)
        {
            throw std::out_of_range("Stack is empty, there is no top.");
        }
        return _top->value;
    }

    template <typename T>
    int Stack<T>::size() const
    {
        return height;
    }

    template <typename T>
    void Stack<T>::print(std::ostream &os, const Stack<T> &a)
    {
        Node<T> *current = a._top;

        while (current != nullptr)
        {
            os << current->value << std::endl; // Fixed to use 'value'
            current = current->next;
        }
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Stack<T> &a)
    {
        Node<T> *current = a._top;

        while (current != nullptr)
        {
            os << current->value << std::endl; // Use 'value'
            current = current->next;
        }

        return os; // Return the output stream
    }

    template <typename T>
    bool operator==(const Stack<T> &a, const Stack<T> &b)
    {
        if (a.size() != b.size())
        {
            return false;
        }

        Node<T> *currentA = a._top;
        Node<T> *currentB = b._top;

        while (currentA != nullptr && currentB != nullptr)
        {
            if (currentA->value != currentB->value)
            {
                return false;
            }
            currentA = currentA->next;
            currentB = currentB->next;
        }

        return true;
    }

    template <typename T>
    bool operator!=(const Stack<T> &a, const Stack<T> &b)
    {
        return !(a == b);
    }

    template <typename T>
    bool operator<=(const Stack<T> &a, const Stack<T> &b)
    {
        Node<T> *currentA = a._top;
        Node<T> *currentB = b._top;

        while (currentA != nullptr && currentB != nullptr)
        {
            if (currentA->value > currentB->value)
            {
                return false;
            }
            currentA = currentA->next;
            currentB = currentB->next;
        }

        return currentA == nullptr; // Return true if currentA is null, meaning a is empty
    }

}

#endif