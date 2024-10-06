/*
 * Copyright (c) 2015 Evan Teran
 *
 * License: The MIT License (MIT)
 *
 * Turned into this monstrosity by jordan4ibanez.
 */

#ifndef CVECTOR_H_
#define CVECTOR_H_

/* cvector heap implemented using C library malloc() */

#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

// Forward declaration.
typedef struct cvector_header cvector_header;

size_t cvector_capacity(char *vec);
size_t cvector_size(char *vec);
size_t cvector_element_size(char *vec);

bool cvector_empty(char *vec);
void cvector_reserve(char **vec, size_t new_capacity);
char *cvector_init(size_t capacity, size_t element_size);
void cvector_remove(char *vec, size_t index);
void cvector_clear(char *vec);
void cvector_free(char *vec);
size_t cvector_compute_next_grow(size_t size);
void cvector_push_back(char **vec, char *value);
void cvector_insert(char **vec, size_t pos, char *fortran_data);
void cvector_pop_back(char *vec);
void cvector_copy(char *from, char **to);
void cvector_swap(char **vec, char **other);
void cvector_set_capacity(char *vec, size_t size);
void cvector_set_size(char *vec, size_t _size);
void cvector_grow(char **vec, size_t count);
void cvector_shrink_to_fit(char **vec);
char *cvector_get(char *vec, size_t index);
void cvector_set(char *vec, size_t index, void *fortran_data);
char *cvector_front(char *vec);
char *cvector_back(char *vec);
void cvector_resize(char **vec, size_t count, char *value);

struct cvector_header
{
    size_t size;
    size_t capacity;
    size_t element_size;
};

// Cache this.
const static size_t HEADER_SIZE = sizeof(cvector_header);

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
size_t cvector_capacity(char *vec)
{
    if (vec)
    {
        return ((cvector_header *)vec)->capacity;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief cvector_size - gets the current size of the vector
 * @param vec - the vector
 * @return the size as a size_t
 */
size_t cvector_size(char *vec)
{
    if (vec)
    {
        return ((cvector_header *)vec)->size;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief cvector_element_size - gets the size of the elements
 * @param vec - the vector
 * @return the size as a size_t
 */
size_t cvector_element_size(char *vec)
{
    if (vec)
    {
        return ((cvector_header *)vec)->element_size;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief cvector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
bool cvector_empty(char *vec)
{
    return cvector_size(vec) == 0;
}

/**
 * @brief cvector_reserve - Requests that the vector capacity be at least enough
 * to contain new_capacity elements. If new_capacity is greater than the current vector capacity, the
 * function causes the container to reallocate its storage increasing its
 * capacity to new_capacity (or greater).
 * @param vec - the vector
 * @param new_capacity - Minimum capacity for the vector.
 * @return void
 */
void cvector_reserve(char **vec, size_t new_capacity)
{
    if (cvector_capacity(*vec) < new_capacity)
    {
        cvector_grow(vec, new_capacity);
    }
}

/**
 * @brief cvector_init - Initialize a vector.  The vector must be NULL for this to do anything.
 * @param capacity - vector capacity to reserve
 * @return void
 */
char *cvector_init(size_t capacity, size_t element_size)
{
    char *vec = malloc(HEADER_SIZE);

    ((cvector_header *)vec)->capacity = 0;
    ((cvector_header *)vec)->size = 0;
    ((cvector_header *)vec)->element_size = element_size;

    if (!vec)
    {
        cvector_reserve(&vec, capacity);
    }

    return vec;
}

/**
 * @brief cvector_remove - removes the element at index i from the vector
 * @param vec - the vector
 * @param index - index of element to remove
 * @return void
 */
void cvector_remove(char *vec, size_t index)
{
    // Null pointer.
    if (!vec)
    {
        return;
    }
    const size_t vector_size = cvector_size(vec);

    // Out of bounds.
    if (index >= vector_size)
    {
        return;
    }

    // Benchmark ~3.6 with 10,000,000 elements.
    const size_t new_size = vector_size - 1;
    cvector_set_size(vec, new_size);
    const size_t element_size = cvector_element_size(vec);
    const size_t array_size = (index * element_size);
    const size_t size = HEADER_SIZE + array_size;
    char *min = vec + size;
    const char *max = min + element_size;
    const size_t length = (new_size - index) * element_size;

    memmove(min, max, length);
}

/**
 * @brief cvector_clear - erase all of the elements in the vector
 * @param vec - the vector
 * @return void
 */
void cvector_clear(char *vec)
{
    if (vec)
    {
        cvector_set_size(vec, 0);
    }
}

/**
 * @brief cvector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
void cvector_free(char *vec)
{
    if (vec)
    {
        free(vec);
    }
}

/**
 * @brief cvector_compute_next_grow - returns an the computed size in next vector grow
 * size is increased by multiplication of 2
 * @param size - current size
 * @return size after next vector grow
 */
size_t cvector_compute_next_grow(size_t size)
{
    if (size)
    {
        return size << 1;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
void cvector_push_back(char **vec, char *value)
{

    size_t current_capacity = cvector_capacity(*vec);

    if (current_capacity <= cvector_size(*vec))
    {
        cvector_grow(vec, cvector_compute_next_grow(current_capacity));
    }

    char *current_element = *vec + HEADER_SIZE + (cvector_element_size(*vec) * cvector_size(*vec));

    memcpy(current_element, value, cvector_element_size(*vec));
    cvector_set_size(*vec, cvector_size(*vec) + 1);
}

/**
 * @brief cvector_insert - insert element at index pos to the vector
 * @param vec - the vector
 * @param index - index in the vector where the new elements are inserted.
 * @param fortran_data - value to be copied (or moved) to the inserted elements.
 * @return void
 */
void cvector_insert(char **vec, size_t index, char *fortran_data)
{
    size_t vec_capacity = cvector_capacity(*vec);

    if (vec_capacity <= cvector_size(*vec))
    {
        cvector_grow(vec, cvector_compute_next_grow(vec_capacity));
    }

    size_t current_size = cvector_size(*vec);

    const size_t element_size = cvector_element_size(*vec);

    // If we're inserting into the middle, shove everything forwards.
    if (index < current_size)
    {
        char *min = *vec + HEADER_SIZE + (index * element_size);
        char *max = min + element_size;
        const size_t length = (current_size - index) * element_size;

        memmove(max, min, length);
    }

    memcpy(*vec + HEADER_SIZE + (element_size * index), fortran_data, element_size);
    cvector_set_size(*vec, current_size + 1);
}

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
void cvector_pop_back(char *vec)
{
    cvector_set_size(vec, cvector_size(vec) - 1);
}

/**
 * @brief cvector_copy - copy a vector
 * @param from - the original vector
 * @param to - destination to which the function copy to
 * @return void
 */
void cvector_copy(char *from, char **to)
{
    if (from)
    {
        cvector_grow(to, cvector_size(from));
        cvector_set_size(*to, cvector_size(from));

        // If they're not the same size, this will blow up.
        assert(cvector_element_size(from) == cvector_size(*to));

        memcpy(to, from, HEADER_SIZE + (cvector_size(from) * cvector_element_size(from)));
    }
}

/**
 * @brief cvector_swap - exchanges the content of the vector by the content of another vector of the same type
 * @param vec - the original vector
 * @param other - the other vector to swap content with
 * @param type - the type of both vectors
 * @return void
 */
void cvector_swap(char **vec, char **other)
{
    if (vec && other)
    {
        char *swapper = *vec;
        *vec = *other;
        *other = swapper;
    }
}

/**
 * @brief cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param new_capacity - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_capacity(char *vec, size_t new_capacity)
{
    if (vec)
    {
        ((cvector_header *)vec)->capacity = (new_capacity);
    }
}

/**
 * @brief cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param new_size - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_size(char *vec, size_t new_size)
{
    if (vec)
    {
        ((cvector_header *)vec)->size = (new_size);
    }
}

/**
 * @brief cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param new_capacity - the new capacity to set
 * @return void
 * @internal
 */
void cvector_grow(char **vec, size_t new_capacity)
{
    const size_t NEW_SIZE = HEADER_SIZE + (new_capacity * cvector_element_size(*vec));
    char *temp = realloc(*vec, NEW_SIZE);
    assert(temp);
    cvector_set_capacity(temp, new_capacity);

    *vec = temp;
}

/**
 * @brief cvector_shrink_to_fit - requests the container to reduce its capacity to fit its size
 * @param vec - the vector
 * @return void
 */
void cvector_shrink_to_fit(char **vec)
{
    if (vec)
    {
        const size_t vec_size = cvector_size(*vec);
        cvector_grow(vec, vec_size);
    }
}

/**
 * @brief cvector_get - returns a reference to the element at index new_capacity in the vector.
 * @param vec - the vector
 * @param index - index of an element in the vector.
 * @return the element at the specified index in the vector.
 */
char *cvector_get(char *vec, size_t index)
{
    if (vec)
    {
        if (index < 0 || index >= cvector_size(vec))
        {
            return NULL;
        }
        else
        {
            return vec + HEADER_SIZE + (index * cvector_element_size(vec));
        }
    }
    else
    {
        return NULL;
    }
}

/**
 * Overwrite the memory of an index.
 */
void cvector_set(char *vec, size_t index, void *fortran_data)
{
    // Safety implemented in Fortran.

    size_t current_size = cvector_size(vec);
    const size_t element_size = cvector_element_size(vec);
    memcpy(vec + HEADER_SIZE + (element_size * index), fortran_data, element_size);
}

/**
 * @brief cvector_front - returns a reference to the first element in the vector. Unlike member cvector_begin, which returns an iterator to this same element, this function returns a direct reference.
 * @return a reference to the first element in the vector container.
 */
char *cvector_front(char *vec)
{
    if (vec)
    {
        if (cvector_size(vec) > 0)
        {
            return cvector_get(vec, 0);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief cvector_back - returns a reference to the last element in the vector.Unlike member cvector_end, which returns an iterator just past this element, this function returns a direct reference.
 * @return a reference to the last element in the vector.
 */
char *cvector_back(char *vec)
{
    if (vec)
    {
        if (cvector_size(vec) > 0)
        {
            return cvector_get(vec, cvector_size(vec) - 1);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief cvector_resize - resizes the container to contain count elements.
 * @param vec - the vector
 * @param count - new size of the vector
 * @param value - the value to initialize new elements with
 * @return void
 */
void cvector_resize(char **vec, size_t new_size, char *value)
{
    if (vec)
    {
        size_t old_size = ((cvector_header *)vec)->size;

        if (new_size > old_size)
        {
            cvector_reserve(vec, new_size);
            cvector_set_size(*vec, new_size);

            while (old_size < new_size)
            {
                cvector_push_back(vec, value);
                old_size++;
            }
        }
        else
        {
            while (new_size < old_size)
            {
                cvector_pop_back(*vec);
                old_size--;
            }
        }
    }
}

#endif /* CVECTOR_H_ */
