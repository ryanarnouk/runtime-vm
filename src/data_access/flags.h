#ifndef FLAGS_h
#define FLAGS_h

#include <stdint.h>

// TODO: Modify the flags and potentially
// reduce the number of bits. 16 is not necessary
// for every possibility in the current implementation
#define ACC_PUBLIC (1 << 0)
#define ACC_PRIVATE (2 << 0)
#define ACC_SUPER (1 << 1)
#define ACC_FINAL (1 << 2)
#define ACC_STATIC (1 << 3)

// Structure for a flag which is represented as a hex character with 4 hexits
// Using bitwise operators, a combination of flags can be represented using the single integer
// Example:
//  A super private class: 0x0011
//  A class cannot be public and private. A hex value must be 0x...1 or 0x...2, but not both
typedef struct {
    uint16_t access_flags; // 2 bytes access flags
} Flags;

#endif
