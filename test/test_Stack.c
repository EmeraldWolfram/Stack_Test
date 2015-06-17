#include "unity.h"
#include "Stack.h"
#include <stdlib.h>

void setUp(void){}

void tearDown(void){}
/**
 *  createStack like this
 *
 *  ********
 *  * head *-------->NULL
 *  ********
 *  * tail *-------->NULL
 *  ********
 */
void test_createStack(void){
	Stack* testStack = createStack();

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NULL(testStack->head);
  TEST_ASSERT_NULL(testStack->tail);
  TEST_ASSERT_EQUAL(0, testStack->length);
}

/**
 *  createStackElement like this
 *
 *  *************
 *  * data = 10 *-------->NULL
 *  *************
 */
void test_createStackElement(void){
  StackElement* testElement = createStackElement(10);

  TEST_ASSERT_NOT_NULL(testElement);
  TEST_ASSERT_EQUAL(10, testElement->data);
  TEST_ASSERT_NULL(testElement->next);
}

/**
 *  Before:                 After stackAdd:
 *  ********                ********-------
 *  * head *----->NULL      * head *       \
 *  ********                ********       *************
 *  * tail *----->NULL      * tail * ----->* data = 10 *--->NULL
 *  ********                ********       *************
 *
 */
void test_stackAdd_add_1_Element_in_front(void){
  Stack* testStack = createStack();
  StackElement* testElement = createStackElement(10);
  stackAdd(testStack,testElement);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NOT_NULL(testElement);
  TEST_ASSERT_EQUAL(10, testStack->head->data);
  TEST_ASSERT_EQUAL(10, testStack->tail->data);
  TEST_ASSERT_NULL(testStack->tail->next);
  TEST_ASSERT_EQUAL(1,testStack->length);
}

/**
 *  if Stack is NULL while calling stackAdd
 *
 *  tell error
 *  ERROR: Stack cannot be NULL
 *  Then, jump out directly!
 */
void test_stackAdd_NULL_Stack_add_1_Element_should_return_error(void){
  Stack* testStack = NULL;
  StackElement* testElement = createStackElement(10);
  stackAdd(testStack,testElement);

  TEST_ASSERT_NULL(testStack);
}

/**
 *  If the Element add-in is NULL, stackAdd tell error and remain the stack unchanged.
 *
 *  Before:                                       After:
 *
 *  ********---------                             ********-----------
 *  * head *         \                            * head *           \
 *  ********      *************                   ********      *************
 *  * tail * ---> * data = 10 * -----> NULL       * tail * ---> * data = 10 * -----> NULL
 *  ********      *************                   ********      *************
 */
void test_stackAdd_add_NULL_Element_in_front(void){
  Stack* testStack = createStack();
  StackElement* testElement_1 = createStackElement(10);
  StackElement* testElement_2 = NULL;
  stackAdd(testStack,testElement_1);
  stackAdd(testStack,testElement_2);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NULL(testElement_2);
  TEST_ASSERT_NOT_NULL(testElement_1);
  TEST_ASSERT_EQUAL(10, testStack->head->data);
  TEST_ASSERT_NULL(testStack->head->next);
  TEST_ASSERT_EQUAL_PTR(testStack->head, testStack->tail);
  TEST_ASSERT_EQUAL(1,testStack->length);
}

/**
 *  Before:                 After 1st stackAdd:
 *  ********                ********-------
 *  * head *----->NULL      * head *       \
 *  ********                ********       *************
 *  * tail *----->NULL      * tail * ----->* data = 10 *--->NULL
 *  ********                ********       *************
 *
 *    After 2nd stackAdd
 *     ********--------------------------
 *     * tail *                          \
 *     ********       ************    *************
 *     * head * ----->* data = 5 *--->* data = 10 *----->NULL
 *     ********       ************    *************
 */
void test_stackAdd_add_2_Element_in_front(void){
  Stack* testStack = createStack();
  StackElement* testElement_1 = createStackElement(10);
  StackElement* testElement_2 = createStackElement(5);
  stackAdd(testStack,testElement_1);
  stackAdd(testStack,testElement_2);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NOT_NULL(testElement_1);
  TEST_ASSERT_NOT_NULL(testElement_2);
  TEST_ASSERT_EQUAL(5, testStack->head->data);
  TEST_ASSERT_EQUAL(10, testStack->head->next->data);
  TEST_ASSERT_EQUAL_PTR(testStack->head->next, testStack->tail);
  TEST_ASSERT_NULL(testStack->tail->next);
  TEST_ASSERT_EQUAL(2,testStack->length);
}

/**
 *  Before:                 After 1st stackAdd:
 *  ********                ********-------
 *  * head *----->NULL      * head *       \
 *  ********                ********       *************
 *  * tail *----->NULL      * tail * ----->* data = 10 *--->NULL
 *  ********                ********       *************
 *
 *    After 3rd stackAdd
 *     ********-------------------------------------------
 *     * tail *                                           \
 *     ********       ************     ************    *************
 *     * head * ----->* data = 2 *---> * data = 5 *--->* data = 10 *----->NULL
 *     ********       ************     ************    *************
 */
void test_stackAdd_add_3_Element_in_front(void){
  Stack* testStack = createStack();
  StackElement* testElement_1 = createStackElement(10);
  StackElement* testElement_2 = createStackElement(5);
  StackElement* testElement_3 = createStackElement(2);
  stackAdd(testStack,testElement_1);
  stackAdd(testStack,testElement_2);
  stackAdd(testStack,testElement_3);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NOT_NULL(testElement_1);
  TEST_ASSERT_NOT_NULL(testElement_2);
  TEST_ASSERT_NOT_NULL(testElement_3);
  TEST_ASSERT_EQUAL(2, testStack->head->data);
  TEST_ASSERT_EQUAL(5, testStack->head->next->data);
  TEST_ASSERT_EQUAL(10, testStack->tail->data);
  TEST_ASSERT_EQUAL_PTR(testStack->head->next->next, testStack->tail);
  TEST_ASSERT_NULL(testStack->tail->next);
  TEST_ASSERT_EQUAL(3,testStack->length);
}
/**
 *    Before
 *     ********-------------------------------------------
 *     * tail *                                           \
 *     ********       ************     ************    *************
 *     * head * ----->* data = 2 *---> * data = 5 *--->* data = 10 *----->NULL
 *     ********       ************     ************    *************
 *
 *
 *    After stackRemove
 *     ********--------------------------
 *     * tail *                          \
 *     ********       ************    *************
 *     * head * ----->* data = 5 *--->* data = 10 *----->NULL
 *     ********       ************    *************
 *
 */
void test_stackRemove_given_Stack_with_3_Element_should_return_stack_with_2_element(void){
  Stack* testStack = createStack();
  StackElement* removedElement = malloc(sizeof(StackElement));
  StackElement* testElement_1 = createStackElement(10);
  StackElement* testElement_2 = createStackElement(5);
  StackElement* testElement_3 = createStackElement(2);
  stackAdd(testStack,testElement_1);
  stackAdd(testStack,testElement_2);
  stackAdd(testStack,testElement_3);

  removedElement = stackRemove(testStack);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NOT_NULL(testElement_1);
  TEST_ASSERT_NOT_NULL(testElement_2);
  TEST_ASSERT_NOT_NULL(testElement_3);
  TEST_ASSERT_NOT_NULL(removedElement);
  TEST_ASSERT_EQUAL(2, removedElement->data);
  TEST_ASSERT_NULL(removedElement->next);
  TEST_ASSERT_EQUAL(5, testStack->head->data);
  TEST_ASSERT_EQUAL(10, testStack->tail->data);
  TEST_ASSERT_NULL(testStack->tail->next);
  TEST_ASSERT_EQUAL(2,testStack->length);
}

void test_stackRemove_given_Stack_with_1_Element_should_return_empty_stack(void){
  Stack* testStack = createStack();
  StackElement* removedElement = malloc(sizeof(StackElement));
  StackElement* testElement_1 = createStackElement(10);
  stackAdd(testStack,testElement_1);

  removedElement = stackRemove(testStack);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NOT_NULL(testElement_1);
  TEST_ASSERT_NOT_NULL(removedElement);
  TEST_ASSERT_NULL(testStack->head);
  TEST_ASSERT_NULL(testStack->tail);
  TEST_ASSERT_EQUAL(10,removedElement->data);
  TEST_ASSERT_EQUAL(0,testStack->length);
}

/**
 *  if Stack is NULL while calling stackRemove
 *
 *  tell error
 *  ERROR: Stack cannot be NULL
 *  Then, return NULL!
 */
void test_stackRemove_NULL_Stack_remove_Element_should_return_error(void){
  Stack* testStack = NULL;
  StackElement* removedElement = malloc(sizeof(StackElement));
  removedElement = stackRemove(testStack);

  TEST_ASSERT_NULL(testStack);
}

/**
 *  If the Stack is empty, stackRemove tell error and return a NULL
 *
 *  Before:                     After:
 *
 *  ********                    ********
 *  * head *-------->NULL       * head *-------->NULL
 *  ********                    ********
 *  * tail *-------->NULL       * tail *-------->NULL
 *  ********                    ********
 *
 *                              Return NULL
 */
void test_stackRemove_given_NULL_Stack_should_return_Empty_element(void){
  Stack* testStack = createStack();
  StackElement* removedElement = malloc(sizeof(StackElement));

  removedElement = stackRemove(testStack);

  TEST_ASSERT_NOT_NULL(testStack);
  TEST_ASSERT_NULL(removedElement);
  TEST_ASSERT_EQUAL(0,testStack->length);
}