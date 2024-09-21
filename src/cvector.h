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

// Forward declaration.
size_t cvector_capacity(void *vec);
size_t cvector_size(void *vec);
size_t cvector_element_size(void *vec);
bool cvector_empty(void *vec);
void cvector_reserve(void **vec, size_t n);
void *cvector_init(size_t capacity, size_t element_size);
void cvector_erase(void *vec, size_t i);
void cvector_clear(void *vec);
void cvector_free(void *vec);
void *cvector_begin(void *vec);
void *cvector_end(void *vec);
size_t cvector_compute_next_grow(size_t size);
void cvector_push_back(void **vec, void *value);
void cvector_insert(void *vec, size_t pos, void *val);
void cvector_pop_back(void *vec);
void cvector_copy(void *from, void *to);
void cvector_swap(void *vec, void *other);
void cvector_set_capacity(void *vec, size_t size);
void cvector_set_size(void *vec, size_t _size);
void cvector_grow(void **vec, size_t count);
void cvector_shrink_to_fit(void *vec);
void *cvector_at(void *vec, size_t n);
void *cvector_front(void *vec);
void *cvector_back(void *vec);
void cvector_resize(void *vec, size_t count, void *value);

typedef struct cvector_metadata_t
{
    size_t size;
    size_t capacity;
    size_t element_size;
} cvector_metadata_t;

// Cache this.
const static size_t METADATA_SIZE = sizeof(cvector_metadata_t);

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
size_t cvector_capacity(void *vec)
{
    if (vec)
    {
        return ((cvector_metadata_t *)vec)->capacity;
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
size_t cvector_size(void *vec)
{
    if (vec)
    {
        return ((cvector_metadata_t *)vec)->size;
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
size_t cvector_element_size(void *vec)
{
    if (vec)
    {
        return ((cvector_metadata_t *)vec)->element_size;
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
bool cvector_empty(void *vec)
{
    return cvector_size(vec) == 0;
}

/**
 * @brief cvector_reserve - Requests that the vector capacity be at least enough
 * to contain n elements. If n is greater than the current vector capacity, the
 * function causes the container to reallocate its storage increasing its
 * capacity to n (or greater).
 * @param vec - the vector
 * @param n - Minimum capacity for the vector.
 * @return void
 */
void cvector_reserve(void **vec, size_t n)
{
    if (cvector_capacity(*vec) < n)
    {
        cvector_grow(vec, n);
    }
}

/**
 * @brief cvector_init - Initialize a vector.  The vector must be NULL for this to do anything.
 * @param capacity - vector capacity to reserve
 * @return void
 */
void *cvector_init(size_t capacity, size_t element_size)
{
    void *vec = malloc(sizeof(cvector_metadata_t));

    ((cvector_metadata_t *)vec)->capacity = 0;
    ((cvector_metadata_t *)vec)->size = 0;
    ((cvector_metadata_t *)vec)->element_size = element_size;

    if (!vec)
    {
        cvector_reserve(vec, capacity);
    }

    return vec;
}

/**
 * @brief cvector_erase - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
void cvector_erase(void *vec, size_t i)
{
    if (vec)
    {
        const size_t vector_size = cvector_size(vec);
        if (i < vector_size)
        {
            const size_t new_size = vector_size - 1;

            cvector_set_size(vec, new_size);

            const size_t el_size = cvector_element_size(vec);
            void *min = vec + METADATA_SIZE + (i * el_size);
            void *max = min + el_size;
            const size_t length = (new_size - i) * el_size;

            memmove(min, max, length);
        }
    }
}

/**
 * @brief cvector_clear - erase all of the elements in the vector
 * @param vec - the vector
 * @return void
 */
void cvector_clear(void *vec)
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
void cvector_free(void *vec)
{
    if (vec)
    {
        free(vec);
    }
}

/**
 * @brief cvector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
void *cvector_begin(void *vec)
{
    //! fixme: this is wrong!
    return vec;
}

/**
 * @brief cvector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
void *cvector_end(void *vec)
{
    if (vec)
    {
        //! fixme: this is wrong!
        return &(vec)[cvector_size(vec)];
    }
    else
    {
        return NULL;
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
void cvector_push_back(void **vec, void *value)
{

    size_t current_capacity = cvector_capacity(*vec);

    if (current_capacity <= cvector_size(*vec))
    {
        cvector_grow(vec, cvector_compute_next_grow(current_capacity));
    }

    // printf("current cap: %i\n", cvector_capacity(*vec));
    // printf("size: %i\n", cvector_size(*vec));

    void *current_element = *vec + METADATA_SIZE + (cvector_element_size(*vec) * cvector_size(*vec));

    memcpy(current_element, value, cvector_element_size(*vec));
    cvector_set_size(*vec, cvector_size(*vec) + 1);
}

/**
 * @brief cvector_insert - insert element at position pos to the vector
 * @param vec - the vector
 * @param pos - position in the vector where the new elements are inserted.
 * @param val - value to be copied (or moved) to the inserted elements.
 * @return void
 */
void cvector_insert(void *vec, size_t pos, void *val)
{

    size_t vec_capacity = cvector_capacity(vec);
    if (vec_capacity <= cvector_size(vec))
    {
        cvector_grow(vec, cvector_compute_next_grow(vec_capacity));
    }
    if (pos < cvector_size(vec))
    {
        //! fixme: this is wrong!
        memmove(
            (vec) + (pos) + 1,
            (vec) + (pos),
            sizeof(*(vec)) * ((cvector_size(vec)) - (pos)));
    }

    const size_t el_size = cvector_element_size(vec);
    memcpy(vec + sizeof(cvector_metadata_t) + (el_size * pos), val, el_size);
    cvector_set_size((vec), cvector_size(vec) + 1);
}

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
void cvector_pop_back(void *vec)
{
    cvector_set_size(vec, cvector_size(vec) - 1);
}

/**
 * @brief cvector_copy - copy a vector
 * @param from - the original vector
 * @param to - destination to which the function copy to
 * @return void
 */
void cvector_copy(void *from, void *to)
{
    if (from)
    {
        cvector_grow(to, cvector_size(from));
        cvector_set_size(to, cvector_size(from));
        //! this is wrong!
        memcpy(to, from, cvector_size(from) * sizeof(*(from)));
    }
}

/**
 * @brief cvector_swap - exchanges the content of the vector by the content of another vector of the same type
 * @param vec - the original vector
 * @param other - the other vector to swap content with
 * @param type - the type of both vectors
 * @return void
 */
void cvector_swap(void *vec, void *other)
{
    if (vec && other)
    {
        //! fixme: this needs to use pointer pointers!
        void *swapper = vec;
        vec = other;
        other = swapper;
    }
}

/**
 * @brief cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param new_capacity - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_capacity(void *vec, size_t new_capacity)
{
    if (vec)
    {
        ((cvector_metadata_t *)vec)->capacity = (new_capacity);
    }
}

/**
 * @brief cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param new_size - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_size(void *vec, size_t new_size)
{
    if (vec)
    {
        ((cvector_metadata_t *)vec)->size = (new_size);
    }
}

/**
 * @brief cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param new_capacity - the new capacity to set
 * @return void
 * @internal
 */
void cvector_grow(void **vec, size_t new_capacity)
{
    const size_t NEW_SIZE = METADATA_SIZE + (new_capacity * cvector_element_size(*vec));
    void *temp = realloc(*vec, NEW_SIZE);
    assert(temp);
    cvector_set_capacity(temp, new_capacity);

    *vec = temp;
}

/**
 * @brief cvector_shrink_to_fit - requests the container to reduce its capacity to fit its size
 * @param vec - the vector
 * @return void
 */
void cvector_shrink_to_fit(void *vec)
{
    if (vec)
    {
        const size_t vec_size = cvector_size(vec);
        cvector_grow(vec, vec_size);
    }
}

/**
 * @brief cvector_at - returns a reference to the element at position n in the vector.
 * @param vec - the vector
 * @param n - position of an element in the vector.
 * @return the element at the specified position in the vector.
 */
void *cvector_at(void *vec, size_t n)
{
    if (vec)
    {
        if (n < 0 || n >= cvector_size(vec))
        {
            return NULL;
        }
        else
        {
            return vec + METADATA_SIZE + (n * cvector_element_size(vec));
        }
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief cvector_front - returns a reference to the first element in the vector. Unlike member cvector_begin, which returns an iterator to this same element, this function returns a direct reference.
 * @return a reference to the first element in the vector container.
 */
void *cvector_front(void *vec)
{
    if (vec)
    {
        if (cvector_size(vec) > 0)
        {
            return cvector_at(vec, 0);
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
void *cvector_back(void *vec)
{
    if (vec)
    {
        if (cvector_size(vec) > 0)
        {
            return cvector_at(vec, cvector_size(vec) - 1);
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
void cvector_resize(void *vec, size_t count, void *value)
{

    if (vec)
    {
        size_t cv_sz_count__ = count;
        size_t cv_sz__ = ((cvector_metadata_t *)vec)->size;

        if (cv_sz_count__ > cv_sz__)
        {
            cvector_reserve((vec), cv_sz_count__);
            cvector_set_size((vec), cv_sz_count__);
            while (cv_sz__ < cv_sz_count__)
            {
                //!!FIXME: THIS IS WRONG!
                memcpy(&vec[cv_sz__++], value, cvector_element_size(vec));
            }
        }
        else
        {
            while (cv_sz_count__ < cv_sz__--)
            {
                cvector_pop_back(vec);
            }
        }
    }
}

#endif /* CVECTOR_H_ */
