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
