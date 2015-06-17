#ifndef Stack_H
#define Stack_H

typedef struct StackElement StackElement;
struct StackElement{
  int data;
  struct StackElement* next;
};

typedef struct{
  StackElement* head;
  StackElement* tail;
  int length;
}Stack;

Stack* createStack();
StackElement* createStackElement(int data);
void stackAdd(Stack* stack, StackElement *elem);
StackElement* stackRemove(Stack* stack);


#endif // Stack_H
