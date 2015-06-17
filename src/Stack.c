#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Stack* createStack(){
  Stack* newStack = malloc(sizeof(Stack));
  assert(newStack != NULL);
  
  newStack->head = NULL;
  newStack->tail = NULL;
  newStack->length = 0;
  
  return newStack;
}

StackElement* createStackElement(int data){
  StackElement* newStackElement = malloc(sizeof(StackElement));
  assert(newStackElement != NULL);
  
  newStackElement->data = data;
  newStackElement->next = NULL; //To make sure the pointer is not floating
  
  return newStackElement; 
}


void stackAdd(Stack* stack, StackElement *elem){ 
  if(elem == NULL){
    printf("ERROR: Element cannot be NULL!");
  }
  else if(stack == NULL){
    printf("ERROR: STACK cannot be NULL!");
  }
  else{
    StackElement* prevHead = malloc(sizeof(StackElement));
    prevHead = stack->head;
    stack->head = elem; //No matter what, the head always point to the new added Element
    
    if(stack->length == 0){
      stack->head->next = NULL;
      stack->tail = elem;
    }
    else
      stack->head->next = prevHead;
    
    (stack->length)++;
    stack->tail->next = NULL; //Tail->next permanently pointing to NULL
  }
}
  
StackElement* stackRemove(Stack* stack){
  StackElement* removedElement;


  if(stack == NULL){    
    removedElement = NULL;
    printf("ERROR: STACK cannot be NULL!");
  }
  else if(stack->head == NULL){
    removedElement = NULL;
    printf("Nothing to remove, empty stack here! Return empty element");
  }
  else{
    removedElement = malloc(sizeof(StackElement));
    removedElement = stack->head;
    if(stack->head->next != NULL)
      stack->head = stack->head->next;
    else{
      stack->head = NULL;
      stack->tail = NULL;
    } 
    removedElement->next = NULL;
    stack->length --;
  }
  return removedElement;
}


