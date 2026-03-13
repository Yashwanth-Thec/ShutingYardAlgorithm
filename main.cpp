#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node*& top, Node* newNode){
  if (newNode == nullptr) {
    return;
  }
  newNode->next = top;

}

Node* pop(Node*& top){
  if (top == nullptr){
    return nullptr;
  }

  Node* temp = top;
  top = top->next;
  temp->next = nullptr;
  return temp;


}

Node* peek(Node* top){
  return top;
}

void enqueue(Node*& front, Node*& rear, Node* newNode){
  if (newNode == nullptr){
    return;
  }

  newNode->next = nullptr;

  if (rear == nullptr){
    front = newNode;
    rear = nowNode;
  }
  else {
    rear->next = newNode;
    rear = newNode;
  }

}

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

bool isOperator(const char* token){
  return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0;

}

bool isNumber(const char* token) {
  return strlen(token) == 1 && isdigit(token[0]);

}

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

bool isRightAssociative(const char* op) {
  return strcmp(op, "^") == 0;
		

}

int tokenize(char input[], char token[][20]){
  int count = 0;
  char* token = strtok(input, " ");

  while (token != nullptr){
    strcpy(tokens[count], token);
    count++;
    token =strtok(nullptr, " ");

  }
  return count;
}


void shuntingYard(char tokens[][20], int tokenCount, Node*& outputFront, Node*& outputRear){

  Node* operatorTop = nullptr;

  for (int i = 0; i < tokenCount; i++){
    if (isNumber(tokens[i])){
      enqueue(outputFront, outputRear, new Node(tokens[i]));

    }
    else if (isOperator(tokens[i])){
      while (peek(operatorTop) != nullptr && isOperator(peek(operatorTop)->data)){
	chat* topOp = peek(operatorTop)->data;

	bool popLeft = !isRightAssociative(tokens[i]) && precedence(tokes[i]) <= precedence(topOP);

	bool popRight = isRightassociative(tokens[i]) && precedence(tokens[i]) < precedence(topOp);

	if (popLeft || popRight){
	  enqueue(outputFront, outputRear, pop(operatorTop));
	  

	}
	else {
	  break;

	}
		       
      }

      push(operatorTop, new Node(tokens[i]));

    }
    else if (strcmp(tokens[i]), "(" == 0) {
      push(operatorTop, new Node(tokens[i]));

    }
    else if (strcmp(tokens[i], ")") == 0) {
      while (peek(operatorTop) != nullptr &&
	     strcmp(peek(operatorTop)->data, "(") != 0) {
             enqueue(outputFront, outputRear, pop(operatorTop));
      }
      if (peel(operatorTop) != nullptr && strcmp(peek(operatorTop)->data, "(")) == 0{
	  Node* temp = pop(operatorTop);
	  delete temp;
	}
    }
      

  }
    while (peek(operatorTop) != nullptr) {
      enqueue(outputFront, outputRear, pop(operatorTop));

    }

}
void print(Node*& front, Node*& rear){
  Node* tempTop = nullptr;
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

Node* expressionTree(Node*& postfixFront, Node*& postfixrear){
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

void printPrefix(Node* root){
  if(root == nullptr){
    return;
  }
  cout << root->data << " ";
  printPrefix(root->left);
  printPrefix(root->right);
}

void printPostfix(Node* root){
  if(root == nullptr){
    return;
  }
  cout << root->data << " ";
  printPostfix(root->left);
  printPostfix(root->right);

}

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
void deleteTree(Node* root){
  if(root == nullptr){
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}
