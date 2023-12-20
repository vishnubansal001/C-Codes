struct Stack {
    int topIndex;
    int capacity;
    int* elements;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->topIndex = -1;
    stack->elements = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

bool isStackEmpty(struct Stack* stk) {
    return stk->topIndex == -1;
}

void pushToStack(struct Stack* stack, int item) {
    stack->elements[++stack->topIndex] = item;
}

void popFromStack(struct Stack* stack) {
    if (isStackEmpty(stack)) return;
    stack->topIndex--;
}

int peekStack(struct Stack* stack) {
    if (isStackEmpty(stack))
        return 0;
    return stack->elements[stack->topIndex];
}

typedef struct {
    struct Stack* primaryStack;
    struct Stack* secondaryStack;
} MyQueue;

MyQueue* createQueue() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->primaryStack = createStack(101);
    queue->secondaryStack = createStack(101);
    return queue;
}

void enqueue(MyQueue* obj, int x) {
    pushToStack(obj->primaryStack, x);
}

int dequeue(MyQueue* obj) {
    while (!isStackEmpty(obj->primaryStack)) {
        pushToStack(obj->secondaryStack, peekStack(obj->primaryStack));
        popFromStack(obj->primaryStack);
    }
    
    int result = peekStack(obj->secondaryStack);
    popFromStack(obj->secondaryStack);
    
    while (!isStackEmpty(obj->secondaryStack)) {
        pushToStack(obj->primaryStack, peekStack(obj->secondaryStack));
        popFromStack(obj->secondaryStack);
    }
    
    return result;
}

int peekQueue(MyQueue* obj) {
    while (!isStackEmpty(obj->primaryStack)) {
        pushToStack(obj->secondaryStack, peekStack(obj->primaryStack));
        popFromStack(obj->primaryStack);
    }
    
    int result = peekStack(obj->secondaryStack);
    
    while (!isStackEmpty(obj->secondaryStack)) {
        pushToStack(obj->primaryStack, peekStack(obj->secondaryStack));
        popFromStack(obj->secondaryStack);
    }
    
    return result;
}

bool isQueueEmpty(MyQueue* obj) {
    return isStackEmpty(obj->primaryStack);
}

void freeQueue(MyQueue* obj) {
    free(obj->primaryStack->elements);
    free(obj->primaryStack);
    free(obj->secondaryStack->elements);
    free(obj->secondaryStack);
    free(obj);
}
