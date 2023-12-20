typedef struct {
    int* array;
    int top;
    int capacity;
} CustomStack;

CustomStack* createStack(int capacity) {
    CustomStack* stack = (CustomStack*)malloc(sizeof(CustomStack));
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void pushToStack(CustomStack* stack, int value) {
    stack->array[++stack->top] = value;
}

void popFromStack(CustomStack* stack) {
    if (!isStackEmpty(stack)) {
        stack->top--;
    }
}

int peekStackTop(CustomStack* stack) {
    return stack->array[stack->top];
}

int isStackEmpty(CustomStack* stack) {
    return stack->top == -1;
}

int findLongestValidParentheses(char* expression) {
    int maxLength = 0;
    CustomStack* stack = createStack(strlen(expression) + 1);
    pushToStack(stack, -1);

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == '(') {
            pushToStack(stack, i);
        } else {
            popFromStack(stack);
            if (!isStackEmpty(stack)) {
                maxLength = (i - peekStackTop(stack) > maxLength) ? i - peekStackTop(stack) : maxLength;
            } else {
                pushToStack(stack, i);
            }
        }
    }

    free(stack->array);
    free(stack);

    return maxLength;
}

