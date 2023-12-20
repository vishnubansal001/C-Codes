struct ParenthesesStack {
    int topIndex;
    int capacity;
    char* elements;
};

struct ParenthesesStack* createStack(int capacity) {
    struct ParenthesesStack* parenthesesStack = (struct ParenthesesStack*)malloc(sizeof(struct ParenthesesStack));
    parenthesesStack->capacity = capacity;
    parenthesesStack->topIndex = -1;
    parenthesesStack->elements = (char*)malloc(parenthesesStack->capacity * sizeof(char));
    return parenthesesStack;
}

bool isStackEmpty(struct ParenthesesStack* stack) {
    return stack->topIndex == -1;
}

void pushToStack(struct ParenthesesStack* stack, char item) {
    stack->elements[++stack->topIndex] = item;
}

void popFromStack(struct ParenthesesStack* stack) {
    if (isStackEmpty(stack)) return;
    stack->topIndex--;
}

char peekStack(struct ParenthesesStack* stack) {
    if (isStackEmpty(stack))
        return 0;
    return stack->elements[stack->topIndex];
}

bool isPair(char openBracket, char closeBracket) {
    return (openBracket == '(' && closeBracket == ')') || (openBracket == '[' && closeBracket == ']') || (openBracket == '{' && closeBracket == '}');
}

bool isValidParentheses(char* expression) {
    int length = strlen(expression);
    struct ParenthesesStack* stack = createStack(length);

    for (int i = 0; i < length; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            pushToStack(stack, expression[i]);
        } else {
            if (isStackEmpty(stack)) {
                free(stack->elements);
                free(stack);
                return false;
            } else if (!isPair(peekStack(stack), expression[i])) {
                free(stack->elements);
                free(stack);
                return false;
            }
            popFromStack(stack);
        }
    }

    bool result = isStackEmpty(stack);
    free(stack->elements);
    free(stack);

    return result;
}