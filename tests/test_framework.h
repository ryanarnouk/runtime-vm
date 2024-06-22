#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s\n", message); \
            return 0; \
        } \
    } while(0)

#define RUN_TEST(test_function) \
    do { \
        printf("Running test: %s\n", #test_function); \
        if (test_function()) { \
            printf("Test passed: %s\n", #test_function); \
        } else { \
            printf("Test failed: %s\n", #test_function); \
            return 1; \
        } \
    } while(0)

#endif
