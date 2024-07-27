#include "loader.h"

ClassFile* load_class_file(const char* filename) {
    // One difference of this file compared to the old "class.c" file
    // is the fact this is reading a binary file ("rb" read & binary flag)
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file \n");
        return 0;
    }

    // Get the file size
    fseek(file, 0, SEEK_END); // moves file pointer to the end of the file
    long file_size = ftell(file); // retrieves current position of the file pointer
    fseek(file, 0, SEEK_SET); // sets the file pointer to the beginning of the file again

    // Allocate memory for the buffer
    char *buffer = (char *) malloc(file_size * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for file buffer \n");
        fclose(file);
        return 0;
    }

    // Read the file into the buffer
    size_t read_size = fread(buffer, sizeof(char), file_size, file);
    if (read_size != file_size) {
        fprintf(stderr, "Failed to read file into buffer \n");
        fclose(file);
        free(buffer);
        return 0;
    }

    // Process the data
    for (long i = 0; i < file_size; i++) {
        printf("%02X ", (unsigned char) buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    // Clean up
    free(buffer);
    fclose(file);

    ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));
    return class;
}
