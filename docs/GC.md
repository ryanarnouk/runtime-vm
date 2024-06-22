# Garbage Collection

Garbage collection is not implemented like the JVM and C# Runtime for this project (despite being my inspiration). Instead, I took example from Swift, Rust's Arc, and C++'s Smart Pointers to use Atomic Reference Counting instead.

For sake of simplicity, I named this documentation "garbage collection" despite it not being a full-fledged out garbage collector in the traditional sense. Eventually, I may tinker with algorithms to do garbage collection in a way more similar to C# and Java.

Overall, for performance and simplicity, I favoured a reference-counting approach.

## ARC API
The Arc API that is incorporated is an "Atomic Reference Count"

It contains the follow methods, inspired by Swift and Objective-C.

```c
ArcNode* arc_create(ArcNode** list, size_t size);
void arc_retain(ArcNode *node);
void arc_release(ArcNode** list, ArcNode *node);
void arc_cleanup(ArcNode **node);
```

### Logic
Final clean up with linked list data structure

### Thread Safety
The reference counter is implemented as an atomic reference counter despite the original version of this project being only available for single-threaded environments where a reference counter (without using a Mutex and the `pthread.h` library) should suffice. I have future plans to introduce concurrency into the runtime and so for future-proofing purposes, I have structured the counter in a way that should avoid race conditions and other issues.
