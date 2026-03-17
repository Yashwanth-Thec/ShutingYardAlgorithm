//Name: Yashwanth Narayan Shravanaboyina Besta
//Date: 3/17/26
//Description: This program takes a math expression and converts it from infix to postfix using the shunting yard algorithm, then builds an expression tree and lets the user print it in infix, prefix, or postfix order.

#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

// Adds a new node to the top of the stack
void push(Node*& top, Node* newNode){
  if (newNode == nullptr) {
    return;
  }
  newNode->next = top;
  top = newNode;

}

// Removes and returns the node at the top of the stack
Node* pop(Node*& top){
  if (top == nullptr){
    return nullptr;
  }

  Node* temp = top;
  top = top->next;
  temp->next = nullptr;
  return temp;


}

// Returns the node at the top of the stack without removing it
Node* peek(Node* top){
  return top;
}

// Adds a new node to the back of the queue
void enqueue(Node*& front, Node*& rear, Node* newNode){
  if (newNode == nullptr){
    return;
  }

  newNode->next = nullptr;

  if (rear == nullptr){
    front = newNode;
    rear = newNode;
  }
  else {
    rear->next = newNode;
    rear = newNode;
  }

}

// Removes and returns the node at the front of the queue
Node* dequeue(Node*& front, Node*& rear) {
  if (front == nullptr){
    return nullptr;
  }

  Node* temp = front;
  front = front->next;

  if(front == nullptr) {
    rear = nullptr;

  }

  temp->next = nullptr;
  return temp;


}

// Returns true if the token is a math operator (+, -, *, /)
bool isOperator(const char* token){
  return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0;

}

// Returns true if the token is a single digit number
bool isNumber(const char* token) {
  return strlen(token) == 1 && isdigit(token[0]);

}

// Returns a number representing how important an operator is (higher = runs first)
int precedence(const char* op){
  if(strcmp(op,"^") == 0){
    return 3;
  }
  if (strcmp(op,"*" )== 0 || strcmp(op,"/") == 0){
    return 2;
  }
  if(strcmp(op, "+") == 0 || strcmp(op,"-") == 0){
    return 1;
  }


}

// Returns true if the operator groups right-to-left (like exponents: 2^3^4 = 2^(3^4))
bool isRightAssociative(const char* op) {
  return strcmp(op, "^") == 0;


}

// Splits the input string into individual tokens (numbers, operators, parentheses)
int tokenize(char input[], char tokens[][20]){
  int count = 0;
  char* token = strtok(input, " ");

  while (token != nullptr){
    strcpy(tokens[count], token);
    count++;
    token = strtok(nullptr, " ");

  }
  return count;
}


// Converts an infix expression (like 3 + 4) into postfix (like 3 4 +) using the shunting yard algorithm
void shuntingYard(char tokens[][20], int tokenCount, Node*& outputFront, Node*& outputRear){

  Node* operatorTop = nullptr;

  for (int i = 0; i < tokenCount; i++){
    if (isNumber(tokens[i])){
      enqueue(outputFront, outputRear, new Node(tokens[i]));

    }
    else if (isOperator(tokens[i])){
      while (peek(operatorTop) != nullptr && isOperator(peek(operatorTop)->data)){
        char* topOp = peek(operatorTop)->data;

	bool popLeft = !isRightAssociative(tokens[i]) && precedence(tokens[i]) <= precedence(topOp);

	bool popRight = isRightAssociative(tokens[i]) && precedence(tokens[i]) < precedence(topOp);

	if (popLeft || popRight){
	  enqueue(outputFront, outputRear, pop(operatorTop));


	}
	else {
	  break;

	}

      }

      push(operatorTop, new Node(tokens[i]));

    }
    else if (strcmp(tokens[i], "(") == 0) {
      push(operatorTop, new Node(tokens[i]));

    }
    else if (strcmp(tokens[i], ")") == 0) {
      while (peek(operatorTop) != nullptr &&
	     strcmp(peek(operatorTop)->data, "(") != 0) {
             enqueue(outputFront, outputRear, pop(operatorTop));
      }
      if (peek(operatorTop) != nullptr && strcmp(peek(operatorTop)->data, "(") == 0){
	      Node* temp = pop(operatorTop);
	      delete temp;
	}
    }


  }
    while (peek(operatorTop) != nullptr) {
      enqueue(outputFront, outputRear, pop(operatorTop));

    }

}

// Prints all nodes in the queue from front to back
void print(Node*& front, Node*& rear){
  Node* tempFront = nullptr;
  Node* tempRear = nullptr;

  while (front != nullptr){
    Node* current = dequeue(front, rear);
    cout << current->data << " ";
    enqueue(tempFront, tempRear, current);

  }
  while (tempFront != nullptr){
    enqueue(front, rear, dequeue(tempFront, tempRear));
  }
}

// This builds a binary expression tree from a postfix expression where the numbers become leaf nodes and operators become parent nodes with two children
Node* buildExpressionTree(Node*& postfixFront, Node*& postfixRear){
  Node* treeTop = nullptr;

  while(postfixFront != nullptr){
    Node* current = dequeue(postfixFront, postfixRear);

    if (isNumber(current->data)){
      push(treeTop, current);

    }

    else if(isOperator(current->data)){
      Node* rightChild = pop(treeTop);
      Node* leftChild = pop(treeTop);

      current->left = leftChild;
      current->right = rightChild;

      push(treeTop, current);

    }

  }

  return pop(treeTop);

}

// This prints the tree in prefix order (operator first, then left, then right)
// Example: + 3 4
void printPrefix(Node* root){
  if(root == nullptr){
    return;
  }
  cout << root->data << " ";
  printPrefix(root->left);
  printPrefix(root->right);
}

// This prints the tree in postfix order (left, then right, then operator)
// Example: 3 4 +
void printPostfix(Node* root){
  if(root == nullptr){
    return;
  }
  printPostfix(root->left);
  printPostfix(root->right);
  cout << root->data << " ";

}

// This prints the tree in infix order (left, operator, right) with parentheses
// Example: (3 + 4)
void printInfix(Node* root){
  if(root == nullptr){
    return;
  }

  if(isOperator(root->data)){
    cout << "(";

  }
  printInfix(root->left);
  cout << root->data << " ";


  printInfix(root->right);
  if(isOperator(root->data)){
    cout << ")";

  }

}

// This frees all the memory used by the tree by deleting every node
void deleteTree(Node* root){
  if(root == nullptr){
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  char input[200];
  char tokens[100][20];

  cout << "Enter an infix expression with spaces between each token:" << endl;
  cin.getline(input, 200);

  int tokenCount = tokenize(input, tokens);

  Node* outputFront = nullptr;
  Node* outputRear = nullptr;

  shuntingYard(tokens, tokenCount, outputFront, outputRear);

  cout << "Postfix expression:" << endl;
  print(outputFront, outputRear);
  cout << endl;

  Node* root = buildExpressionTree(outputFront, outputRear);

  int choice = 0;
  while (choice != 4) {
      cout << endl;
      cout << "1. Print infix" << endl;
      cout << "2. Print prefix" << endl;
      cout << "3. Print postfix" << endl;
      cout << "4. Quit" << endl;
      cout << "Choice: ";
      cin >> choice;

      if (choice == 1) {
          printInfix(root);
          cout << endl;
      }
      else if (choice == 2) {
          printPrefix(root);
          cout << endl;
      }
      else if (choice == 3) {
          printPostfix(root);
          cout << endl;
      }
  }

  deleteTree(root);
  return 0;
}
