#include <stdlib.h>
#include <string.h>
#include "vec.h"

#define MIN_SIZE 64

int grow(vec_t * vector) {
    void * tmp = realloc(vector->array, vector->allocated_slots * 2 * vector->element_size);
    if (tmp == NULL) 
        return VEC_COULD_NOT_ALLOCATE_MEMORY;

    vector->array = tmp;
    vector->allocated_slots *= 2;

    return VEC_SUCCESS;
}

int shrink(vec_t * vector) {
    void * tmp = realloc(vector->array, vector->allocated_slots * vector->element_size / 2);
    if (tmp == NULL) 
        return VEC_COULD_NOT_ALLOCATE_MEMORY;

    vector->array = tmp;
    vector->allocated_slots /= 2;

    return VEC_SUCCESS;
}

int init (vec_t * vector, size_t element_size) {
    //check already initialized
    if (vector->array != NULL && vector->allocated_slots > 0) 
        return VEC_ALREADY_INITIALIZED;

    vector->element_size = element_size;
    vector->size = 0;

    vector->allocated_slots = MIN_SIZE;
    vector->array = calloc(MIN_SIZE, element_size);

    //check memory allocation
    if (vector->array == NULL) 
        return VEC_COULD_NOT_ALLOCATE_MEMORY;

    //everything is good
    return VEC_SUCCESS;
}
int insert(vec_t * vector, void * element_ptr, int idx) {
    int i;
    //check that have enough space, grow if necesary
    if (vector->size == vector->allocated_slots - 1) {
        if (grow(vector)) 
            return VEC_COULD_NOT_ALLOCATE_MEMORY;
    }

    //check bounds
    if (!(idx >=0 && (size_t)idx <= vector->size))
        return VEC_INDEX_OUT_OF_BOUNDS;
    
    //move everything over one
    for (i = vector->size; i > idx; i--) {
        memcpy(vector->array + (i) * vector->element_size,
                vector->array + (i - 1) * vector->element_size,
                vector->element_size);
    }
    //insert
    memcpy(vector->array + idx * vector->element_size, element_ptr, vector->element_size);

    vector->size++;

    return VEC_SUCCESS;

}

int replace(vec_t * vector, void * element_ptr, int idx) {

    //check bounds
    if (!(idx >=0 && (size_t)idx < vector->size))
        return VEC_INDEX_OUT_OF_BOUNDS;

    //overwrite the other thing
    memcpy(vector->array + idx * vector->element_size, element_ptr, vector->element_size);
    return VEC_SUCCESS;

}

int append(vec_t * vector, void * element_ptr) {
    return insert(vector, element_ptr, vector->size);
}

__attribute__((unused)) int veclen(vec_t * vector) {
    return vector->size;
}
int remove_index(vec_t * vector, int idx) {
    int i;
    //check bounds
    if (!(idx >=0 && (size_t)idx < vector->size))
        return VEC_INDEX_OUT_OF_BOUNDS;
    
    //move everything over one
    for (i = idx; (size_t)i < vector-> size; i++) {
        memcpy(vector->array + (i) * vector->element_size,
                vector->array + (i + 1) * vector->element_size,
                vector->element_size);
    }

    //zero out what was last
    memset(vector->array + (--vector->size) * vector->element_size, 0, vector->element_size);

    //shrink if now use 1/4 space as allocated
    if (vector->size < vector->allocated_slots / 4 && vector->allocated_slots > MIN_SIZE) {
        if (!shrink(vector))
            return VEC_COULD_NOT_ALLOCATE_MEMORY;
    }

    return VEC_SUCCESS;
}
int remove_element(vec_t * vector, void * element_ptr) {
    int i;
    if (element_ptr == NULL) 
        return VEC_NULL_BUFFER;

    for (i = 0; (size_t)i < vector->size; i++) {
        if (memcmp(vector->array + i * vector->element_size, element_ptr, vector->element_size) == 0) {
            return remove_index(vector, i);
        }
    }
    return VEC_NOT_FOUND;
}
int get(vec_t * vector, int idx, void * element_buffer) {
    if (element_buffer == NULL) 
        return VEC_NULL_BUFFER;

    //check bounds
    if (!(idx >=0 && (size_t)idx < vector->size))
        return VEC_INDEX_OUT_OF_BOUNDS;

    memcpy(element_buffer, vector->array + idx * vector->element_size, vector->element_size);

    return VEC_SUCCESS;
}
int destroy(vec_t * vector) {
    if (vector->array == NULL)
        return VEC_ALREADY_DESTROYED;

    free(vector->array);
    memset(vector, 0,sizeof(vec_t));

    return VEC_SUCCESS;
}

int sort(vec_t * vector, cmpfn cmp) {
    qsort(vector->array, vector->size, vector->element_size, cmp);
    return VEC_SUCCESS;
}