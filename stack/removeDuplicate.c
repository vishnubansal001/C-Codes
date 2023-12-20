typedef struct {
    int stackTop;
    char* charArray;
} CustomStack;

CustomStack* initializeStack(int size) {
    CustomStack* stack = (CustomStack*)malloc(sizeof(CustomStack));
    stack->stackTop = -1;
    stack->charArray = (char*)malloc(size * sizeof(char));
    return stack;
}

bool isStackEmpty(CustomStack* stack) {
    return stack->stackTop == -1;
}

void pushToStack(CustomStack* stack, char character) {
    stack->charArray[++stack->stackTop] = character;
}

void popFromStack(CustomStack* stack) {
    if (isStackEmpty(stack)) return;
    stack->stackTop--;
}

char peekStackTop(CustomStack* stack) {
    if (isStackEmpty(stack))
        return 0;
    return stack->charArray[stack->stackTop];
}

char* removeDuplicates(char* inputString) {
    int frequency[26] = {0};
    for (int i = 0; i < strlen(inputString); i++) {
        frequency[inputString[i] - 'a']++;
    }

    CustomStack* stack = initializeStack(strlen(inputString));
    bool exists[26];
    memset(exists, false, sizeof(exists));

    for (int i = 0; i < strlen(inputString); i++) {
        char currentChar = inputString[i];
        frequency[currentChar - 'a']--;

        if (exists[currentChar - 'a'] == true) continue;

        while (!isStackEmpty(stack) && peekStackTop(stack) > currentChar && frequency[peekStackTop(stack) - 'a'] > 0) {
            char removedChar = peekStackTop(stack);
            popFromStack(stack);
            exists[removedChar - 'a'] = false;
        }

        pushToStack(stack, currentChar);
        exists[currentChar - 'a'] = true;
    }

    char* result = (char*)malloc((stack->stackTop + 2) * sizeof(char));
    for (int i = 0; i < stack->stackTop + 1; i++) {
        result[i] = stack->charArray[i];
    }
    result[stack->stackTop + 1] = '\0';

    return result;
}
