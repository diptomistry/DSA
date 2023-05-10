#include <iostream>
#include <string>

using namespace std;

class Stack {
    private:
        char* arr;
        int topIndex;
        int capacity;
    
    public:
        Stack(int cap) {
            capacity = cap;
            arr = new char[capacity];
            topIndex = -1;
        }
        
        ~Stack() {
            delete[] arr;
        }
        
        void push(char value) {
            if (isFull()) {
                cout << "Stack overflow" << endl;
                return;
            }
            
            topIndex++;
            arr[topIndex] = value;
        }
        
        char pop() {
            if (isEmpty()) {
                cout << "Stack underflow" << endl;
                return '\0';
            }
            
            char poppedValue = arr[topIndex];
            topIndex--;
            
            return poppedValue;
        }
        
        char peek() {
            if (isEmpty()) {
                cout << "Stack is empty" << endl;
                return '\0';
            }
            
            return arr[topIndex];
        }
        
        bool isEmpty() {
            return topIndex == -1;
        }
        
        bool isFull() {
            return topIndex == capacity - 1;
        }
};

bool isOperand(char c) {
    return isalpha(c) || isdigit(c);
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int getOperatorPriority(char c) {
    if (c == '^') {
        return 3;
    }
    else if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

string infixToPostfix(string expression) {
    Stack stack(expression.length());
    string postfix = "";
    
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (isOperand(c)) {
            postfix += c;
        }
        else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.peek() != '(' && getOperatorPriority(c) <= getOperatorPriority(stack.peek())) {
                postfix += stack.pop();
            }
            
            stack.push(c);
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            
            stack.pop();
        }
    }
    
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }
    
    return postfix;
}

int main() {
    string infixExpression;
    cout << "Enter infix expression: ";
    cin >> infixExpression;
    
    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;
    
    return 0;
}
