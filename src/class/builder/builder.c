#include "builder.h"
#include "../../common_properties.h"
#include <stdlib.h>

ClassFile *create_class_file(char* name) {
    if (name == NULL) {
        return NULL;
    }

    ClassFile* class_file = malloc(sizeof(ClassFile));
    class_file->major_version = IL_MAJOR_VERSION;
    class_file->minor_version = IL_MINOR_VERSION;

    class_file->class_name = malloc(sizeof(Utf8));
    class_file->class_name->length = strlen(name);
    class_file->class_name->bytes = malloc(sizeof(char) * class_file->class_name->length);
    strncpy(name, class_file->class_name->bytes, class_file->class_name->length);

    // Stub - Implement flags later
    class_file->flags = (Flags *) malloc(sizeof(Flags));
    class_file->flags->access_flags = 0; // TODO later

    // Init the counters
    class_file->constant_pool_count = 0;
    class_file->constant_pool_capacity = CONSTANT_POOL_INIT_SIZE;
    // class_file->method_count = 0;

    ConstantPoolEntry* entries = (ConstantPoolEntry *) malloc(sizeof(ConstantPoolEntry) * class_file->constant_pool_capacity);
    class_file->constant_pool_entries = entries;

    class_file->method_table = malloc(sizeof(VirtualMethodTable));
    // Default method count is 0 and as instructions are added, increment as added and resize
    // accordingly
    class_file->method_table->method_count = 1;
    // TODO: set a default method size (only 1 for now to support print)
    // and resize based on the count as needed
    class_file->method_table->methods_code = malloc(sizeof(CodeAttribute) * 1);

    class_file->super_class = 0; // TODO: implement this
    class_file->this_class = 0; // TODO: implement this

    return class_file;
}
