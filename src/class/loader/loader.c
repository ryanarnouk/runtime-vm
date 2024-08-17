#include "loader.h"

ClassFile* load_class_file(const char* filename) {
    // One difference of this file compared to the old "class.c" file
    // is the fact this is reading a binary file ("rb" read & binary flag)
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file \n");
        return 0;
    }

    // // Get the file size
    // fseek(file, 0, SEEK_END); // moves file pointer to the end of the file
    // long file_size = ftell(file); // retrieves current position of the file pointer
    // fseek(file, 0, SEEK_SET); // sets the file pointer to the beginning of the file again

    // // Allocate memory for the buffer
    // char *buffer = (char *) malloc(file_size * sizeof(char));
    // if (buffer == NULL) {
    //     fprintf(stderr, "Failed to allocate memory for file buffer \n");
    //     fclose(file);
    //     return 0;
    // }

    // // Read the file into the buffer
    // long read_size = fread(buffer, sizeof(char), file_size, file);
    // if (read_size != file_size) {
    //     fprintf(stderr, "Failed to read file into buffer \n");
    //     fclose(file);
    //     free(buffer);
    //     return 0;
    // }

    // TODO: The parser/reading needs to be fixed for to account for the pointers and other structures
    // within the main struct
    ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));

    fread(&class->minor_version, sizeof(uint16_t), 1, file);
    fread(&class->major_version, sizeof(uint16_t), 1, file);

    class->class_name = (Utf8 *) malloc(sizeof(Utf8));
    fread(&class->class_name->length, sizeof(uint16_t), 1, file);
    class->class_name->bytes = (char *) malloc(class->class_name->length * sizeof(char));
    fread(class->class_name->bytes, sizeof(char), class->class_name->length, file);

    class->flags = (Flags *) malloc(sizeof(Flags));
    fread(&class->flags->access_flags, sizeof(uint16_t), 1, file);

    // Read the constant pool
    fread(&class->constant_pool_count, sizeof(uint16_t), 1, file);
    fread(&class->constant_pool_capacity, sizeof(uint16_t), 1, file);
    class->constant_pool_entries = (ConstantPoolEntry *) malloc(class->constant_pool_count * sizeof(ConstantPoolEntry));

    // iterate through and add each enrty to the constant pool
    for (int i = 0; i < class->constant_pool_count; i++) {
        fread(&class->constant_pool_entries[i].tag, sizeof(uint8_t), 1, file);
        printf("Constant pool tag: %d", class->constant_pool_entries[i].tag);
        switch (class->constant_pool_entries[i].tag) {
            case CONSTANT_METHOD_REF:
                class->constant_pool_entries[i].info.method_ref_info = (MethodRef *) malloc(sizeof(MethodRef));
                fread(&class->constant_pool_entries[i].info.method_ref_info->class_name.length, sizeof(uint16_t), 1, file);
                fread(&class->constant_pool_entries[i].info.method_ref_info->class_name.bytes,
                    sizeof(char),
                    class->constant_pool_entries[i].info.method_ref_info->class_name.length,
                    file);
                break;
            case CONSTANT_UTF8:
                class->constant_pool_entries[i].info.utf8_info = (Utf8 *) malloc(sizeof(Utf8));
                fread(&class->constant_pool_entries[i].info.utf8_info->length, sizeof(uint16_t), 1, file);
                fread(&class->constant_pool_entries[i].info.utf8_info->bytes,
                    sizeof(char),
                    class->constant_pool_entries[i].info.utf8_info->length,
                    file);
                break;
            default:
                printf("Constant pool entry not supported yet");
                break;
        }
    }

    // Print the constant pool
    for (uint16_t i = 0; i < class->constant_pool_count; i++) {
        printf("Constant pool tag: %d \n", class->constant_pool_entries[i].tag);
        printf("Constant pool entry %d with value %s \n", i, class->constant_pool_entries[i].info.utf8_info->bytes);
        printf("Constant pool length %d \n", class->constant_pool_entries[i].info.utf8_info->length);;
    }


    printf("\n");

    // Clean up
    // free(buffer);
    fclose(file);

    return class;
}
