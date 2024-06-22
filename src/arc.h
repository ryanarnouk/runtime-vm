#ifndef ARC_H
#define ARC_H

// Note: for this project I am using Atomic Reference Counting for Garbage Collection
// This is in line more with Swift, Objective-C, and C++ Smart Pointer examples.
// Whereas, Java and C# tend to use algorithms like mark-and-sweep (which I may implement in the future)
// For sake of simplicity, I have implemented reference counting for this language
// This is the sole garbage collector

#include <pthread.h>

// This is the metadata that is wrapped around any object that is
// added onto the heap in the runtime environment (as part of the NEW
// instruction and it's corresponding opcode)
typedef struct {
    int count;
    pthread_mutex_t mutex;
    void *data;
    size_t size;
} Arc;

// The linked list structure of the Arc garbage collector uses a
// doubly linked list, which increases memory overhead and metadata
// required per object on the heap. But, there is faster overall deletion
typedef struct Node {
    Arc* arc;
    struct Node* next;
    struct Node* prev;
} ArcNode;

ArcNode* arc_create(ArcNode** list, size_t size);
void arc_retain(ArcNode *node);
void arc_release(ArcNode** list, ArcNode *node);

void arc_cleanup(ArcNode **node);
void print_list(ArcNode *list);

#endif
