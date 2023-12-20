typedef struct {
    int* elements;
    int frontIndex;
    int rearIndex;
    int capacity;
} CustomCircularQueue;

CustomCircularQueue* createCircularQueue(int capacity) {
    CustomCircularQueue* circularQueue = (CustomCircularQueue*)malloc(sizeof(CustomCircularQueue));
    circularQueue->frontIndex = 0;
    circularQueue->rearIndex = 0;
    circularQueue->capacity = capacity + 1;
    circularQueue->elements = (int*)malloc(circularQueue->capacity * sizeof(int));
    return circularQueue;
}

bool enQueue(CustomCircularQueue* queue, int value) {
    if ((queue->rearIndex + 1) % queue->capacity != queue->frontIndex % queue->capacity) {
        queue->elements[queue->rearIndex] = value;
        queue->rearIndex = (queue->rearIndex + 1) % queue->capacity;
        return true;
    }
    return false;
}

bool deQueue(CustomCircularQueue* queue) {
    if (queue->frontIndex % queue->capacity != queue->rearIndex % queue->capacity) {
        queue->frontIndex = (queue->frontIndex + 1) % queue->capacity;
        return true;
    }
    return false;
}

int frontValue(CustomCircularQueue* queue) {
    if (queue->frontIndex % queue->capacity != queue->rearIndex % queue->capacity) {
        return queue->elements[queue->frontIndex];
    }
    return -1;
}

int rearValue(CustomCircularQueue* queue) {
    if (queue->frontIndex % queue->capacity != queue->rearIndex % queue->capacity) {
        int rearIndex = (queue->rearIndex - 1 + queue->capacity) % queue->capacity;
        return queue->elements[rearIndex];
    }
    return -1;
}

bool isEmptyQueue(CustomCircularQueue* queue) {
    return queue->frontIndex % queue->capacity == queue->rearIndex % queue->capacity;
}

bool isFullQueue(CustomCircularQueue* queue) {
    return (queue->rearIndex + 1) % queue->capacity == queue->frontIndex % queue->capacity;
}

void freeCircularQueue(CustomCircularQueue* queue) {
    free(queue->elements);
    free(queue);
}
