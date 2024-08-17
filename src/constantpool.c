// DEPRECATED - will remove soon

// #include "constantpool.h"
// #include "arc.h"

// ConstantPool* create_constant_pool() {
//     ConstantPool* pool = (ConstantPool *) malloc(sizeof(ConstantPool));
//     pool->size = 0;
//     pool->capacity = MAX_CP_ENTRIES;
//     pool->entries = (ConstantPoolEntry *) malloc(sizeof(ConstantPoolEntry) * MAX_CP_ENTRIES);

//     return pool;
// }

// // The following method doubles the size of the constant pool
// // when it is required (due to it filling up)
// void adjust_pool_capacity_if_needed(ConstantPool *pool) {
//     if (pool->size >= pool->capacity) {
//         pool->capacity *= 2;
//         pool->entries = (ConstantPoolEntry *) realloc(pool->entries, sizeof(ConstantPoolEntry) * pool->capacity);
//     }
// }

// void clean_constant_pool(ConstantPool *pool) {
//     for (int i = 0; i < pool->size; i++) {
//         if (pool->entries[i].tag == TAG_STRING) {
//             free(pool->entries[i].info.str);
//         }
//     }
//     free(pool->entries);
//     free(pool);
// }

// int add_string(ConstantPool *pool, const char *value) {
//     for (int i = 0; i < pool->size; i++) {
//         if (pool->entries[i].tag == TAG_STRING && strcmp(pool->entries[i].info.str, value) == 0) {
//             return i;
//         }
//     }

//     adjust_pool_capacity_if_needed(pool);

//     pool->entries[pool->size].tag = TAG_STRING;
//     pool->entries[pool->size].info.str = strdup(value);
//     return pool->size++;
// }

// int add_class(ConstantPool *pool, const char *class_name) {
//     int string_index = add_string(pool, class_name);
//     adjust_pool_capacity_if_needed(pool);

//     pool->entries[pool->size].tag = TAG_CLASS;
//     pool->entries[pool->size].info.class_index = string_index;
//     return pool->size++;
// }

// int add_field(ConstantPool *pool, int class_index, const char *field_name, const char *field_type) {
//     int field_name_index = add_string(pool, field_name);
//     int field_type_index = add_string(pool, field_type);

//     adjust_pool_capacity_if_needed(pool);

//     pool->entries[pool->size].tag = TAG_FIELD;
//     pool->entries[pool->size].info.field.class_index = class_index;
//     pool->entries[pool->size].info.field.name_index = field_name_index;
//     pool->entries[pool->size].info.field.type_index = field_type_index;
//     return pool->size++;
// }

// int add_object(ConstantPool *pool, const char *class_name) {
//     int class_index = add_class(pool, class_name);

//     adjust_pool_capacity_if_needed(pool);

//     pool->entries[pool->size].tag = TAG_OBJECT;
//     pool->entries[pool->size].info.class_index = class_index;
//     return pool->size++;
// }

// void print_constant_pool(ConstantPool *pool) {
//     for (int i = 0; i < pool->size; i++) {
//         printf("%d: ", i);
//         switch (pool->entries[i].tag) {
//             case TAG_STRING:
//                 printf("String: %s\n", pool->entries[i].info.str);
//                 break;
//             case TAG_CLASS:
//                 printf("Class: %d\n", pool->entries[i].info.class_index);
//                 break;
//             case TAG_FIELD:
//                 printf("Field: Class index: %d, Field name index: %d, Field type index: %d\n",
//                     pool->entries[i].info.field.class_index,
//                     pool->entries[i].info.field.name_index,
//                     pool->entries[i].info.field.type_index);
//                 break;
//             case TAG_OBJECT:
//                 printf("Object: Class index: %d\n", pool->entries[i].info.class_index);
//                 break;
//             default:
//                 printf("Unknown tag: %d\n", pool->entries[i].tag);
//         }
//     }
// }

// ClassTable* create_class_table() {
//     ClassTable* table = (ClassTable *) malloc(sizeof(ClassTable));
//     table->size = 0;
//     table->capacity = MAX_CLASS_ENTRIES;
//     table->classes = (ClassInfo *) malloc(sizeof(ClassInfo) * table->capacity);

//     return table;
// }

// void add_class_fields(ClassTable *table, int class_index, FieldInfo *fields, int field_count) {
//     if (table->size >= table->capacity) {
//         table->capacity *= 2;
//         table->classes = (ClassInfo *) realloc(table->classes, sizeof(ClassInfo) * table->capacity);
//     }

//     table->classes[class_index].fields = (FieldInfo *) malloc(sizeof(FieldInfo) * field_count);
//     memcpy(table->classes[class_index].fields, fields, sizeof(FieldInfo) * field_count);
//     table->classes[class_index].field_count = field_count;
// }

// Object* allocate_object(ConstantPool *pool, ClassTable *table, ArcNode* list, int class_index) {
//     ArcNode* node = arc_create(&list, sizeof(Object));
//     Object *object = (Object *) node->arc->data;
//     object->class_index = class_index;
//     object->arc = node;

//     // Allocate the fields
//     ClassInfo *class_info = &table->classes[class_index];
//     object->field_count = class_info->field_count;
//     object->fields = (Field *) malloc(sizeof(Field) * class_info->field_count);

//     for (int i = 0; i < object->field_count; i++) {
//         object->fields[i].field_name_index = class_info->fields[i].field_name_index;
//         object->fields[i].field_type = class_info->fields[i].field_type_index;
//         object->fields[i].value = NULL;
//     }

//     return object;
// }

// void retain_object(Object *object) {
//     arc_retain(object->arc);
// }

// void release_object(ArcNode* list, Object *object) {
//     arc_release(&list, object->arc);
// }
