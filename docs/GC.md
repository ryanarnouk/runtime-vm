# Garbage Collection

Garbage collection is not implemented like the JVM and C# Runtime for this project (despite being my inspiration). Instead, I took example from Swift, Rust's Arc, and C++'s Smart Pointers to use Atomic Reference Counting instead.

For sake of simplicity, I named this documentation "garbage collection" despite it not being a full-fledged out garbage collector in the traditional sense. Eventually, I may tinker with algorithms to do *actual* garbage collection.

## API
