#include "arc.h"
#include <stdlib.h>
#include <stdio.h>

// Linked list to hold all objects created as a reference
// For the final cleanup when the program is terminated

ArcNode* arc_create(ArcNode** list, size_t size) {
    ArcNode *node = (ArcNode *) malloc(sizeof(ArcNode));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for Arc\n");
        return NULL;
    }
    node->arc = (Arc *) malloc(sizeof(Arc));
    if (node->arc == NULL) {
        free(node);
        fprintf(stderr, "Failed to allocate memory for Arc\n");
        return NULL;
    }

    node->arc->count = 1;
    node->arc->data = malloc(size);
    if (node->arc->data == NULL) {
        free(node->arc);
        free(node);
        fprintf(stderr, "Failed to allocate memory for Arc data\n");
        return NULL;
    }
    node->arc->size = size;

    if (pthread_mutex_init(&node->arc->mutex, NULL) != 0) {
        free(node->arc->data);
        free(node->arc);
        free(node);
        fprintf(stderr, "Failed to initialize atomic structure\n");
        return NULL;
    }

    // Add the arc to the list
    node->prev = NULL;
    node->next = *list;
    if (*list != NULL) {
        (*list)->prev = node;
    }

    *list = node;
    return node;
}

void arc_retain(ArcNode* node) {
    pthread_mutex_lock(&node->arc->mutex);
    node->arc->count++;
    pthread_mutex_unlock(&node->arc->mutex);
}

void arc_release(ArcNode** list, ArcNode *node) {
    pthread_mutex_lock(&node->arc->mutex);
    node->arc->count--;
    if (node->arc->count == 0) {
        pthread_mutex_unlock(&node->arc->mutex);
        pthread_mutex_destroy(&node->arc->mutex);
        free(node->arc->data);
        free(node->arc);

        // Remove the arc from the list
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            *list = node->next;
        }

        if (node->next != NULL) {
            node->next->prev = node->prev;
        }

        free(node);
    } else {
        // Allow other threads to access the arc if release fails
        pthread_mutex_unlock(&node->arc->mutex);
    }
}

void arc_cleanup(ArcNode** list) {
    // Clean up all the Arc objects
    ArcNode *curr = *list;
    while (curr != NULL) {
        ArcNode *next = curr->next;
        curr->arc->count = 1; // Force release
        arc_release(list, curr);
        curr = next;
    }
}

void print_list(ArcNode* list) {
    ArcNode *node = list;
    while (node != NULL) {
        printf("Arc: %p, count: %d\n", node->arc->data, node->arc->count);
        node = node->next;
    }
}
