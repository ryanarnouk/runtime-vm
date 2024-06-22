#include "test_framework.h"

int test() {
    ASSERT(1 == 1, "Failed to run test properly");
    return 1;
}

int main() {
    RUN_TEST(test);
}
