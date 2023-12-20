#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> 

typedef struct {
    int stackTop;
    int stackSize;
    int *stackArray;
} CustomStack;

CustomStack* initializeStack(int size) {
    CustomStack* customStack = (CustomStack*)malloc(sizeof(CustomStack));
    customStack->stackTop = -1;
    customStack->stackSize = size;
    customStack->stackArray = (int*)malloc(size * sizeof(int));
    return customStack;
}

bool isStackEmpty(CustomStack* customStack) {
    return customStack->stackTop == -1;
}

int peekStack(CustomStack* customStack) {
    if (isStackEmpty(customStack)) return 0;
    return customStack->stackArray[customStack->stackTop];
}

int popStack(CustomStack* customStack) {
    return customStack->stackArray[customStack->stackTop--];
}

void pushStack(CustomStack* customStack, int item) {
    customStack->stackArray[++customStack->stackTop] = item;
}

int performCalculation(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2; 
        case '-':
            return operand1 - operand2;  
        case '*':
            return operand1 * operand2;  
        case '/':
            return operand1 / operand2;  
    }
    return 0;
}

void evaluateExpression() {
    int result = 0;
    char inputExpression[1000];
    scanf(" %[^\n]", inputExpression);  
    char* token = strtok(inputExpression, " ");

    CustomStack* customStack = initializeStack(1000);

    while (token != NULL) {
        if (token[0] == '?') {
            result = peekStack(customStack);
            break;
        } else if (isdigit(token[0])) {
            int value = atoi(token);
            pushStack(customStack, value);
        } else {
            int calculationResult = performCalculation(popStack(customStack), popStack(customStack), token[0]);
            pushStack(customStack, calculationResult);
        }
        token = strtok(NULL, " ");
    }

    free(customStack->stackArray);
    free(customStack);

    printf("%d\n", result);
}

int main() {
    int numberOfTestCases;
    scanf("%d", &numberOfTestCases);
    
    for (int i = 0; i < numberOfTestCases; i++) {
        evaluateExpression();
    }

    return 0;
}
