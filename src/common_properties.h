#ifndef COMMON_PROPERTIES_H
#define COMMON_PROPERTIES_H

#define FEATURE_FLAG_NEW_PARSER 1

// Version for the IL code generation in the
// .rvmc (class) files of the code
// Current generator version is 0.1

// Note: once CI/CD is implemented, this should match the GitHub
// release version number
#define IL_MAJOR_VERSION 0
#define IL_MINOR_VERSION 1

// The constant pool for a program will default to 10 and double
// for every resize operation that is needed for the program
#define CONSTANT_POOL_INIT_SIZE 10

// When flagged, more verbose printing will occur
#define VERBOSE_MODE 1

#endif
