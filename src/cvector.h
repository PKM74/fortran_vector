/*
 * Copyright (c) 2015 Evan Teran
 *
 * License: The MIT License (MIT)
 *
 * Completely broken by jordan4ibanez.
 */

#ifndef CVECTOR_H_
#define CVECTOR_H_

/* cvector heap implemented using C library malloc() */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct cvector_metadata_t
{
    size_t size;
    size_t capacity;
    size_t element_size;
} cvector_metadata_t;

/**
 * @brief cvector_vector_type - The vector type used in this library
 */
typedef cvector;

/**
 * @brief cvector_iterator - The iterator type used for cvector
 */
typedef cvector_iterator;

/**
 * @brief cvector_vec_to_base - For internal use, converts a vector pointer to a metadata pointer
 * @param vec - the vector
 * @return the metadata pointer of the vector
 * @internal
 */
cvector_metadata_t *cvector_vec_to_base(cvector *vec)
{
    return &((cvector_metadata_t *)(vec))[-1];
}

/**
 * @brief cvector_base_to_vec - For internal use, converts a metadata pointer to a vector pointer
 * @param ptr - pointer to the metadata
 * @return the vector
 * @internal
 */
void *cvector_base_to_vec(void *ptr)
{
    return (void *)&((cvector_metadata_t *)(ptr))[1];
}

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
size_t cvector_capacity(cvector *vec)
{
    return (vec ? cvector_vec_to_base(vec)->capacity : (size_t)0);
}

/**
 * @brief cvector_size - gets the current size of the vector
 * @param vec - the vector
 * @return the size as a size_t
 */
size_t cvector_size(cvector *vec)
{
    return (vec ? cvector_vec_to_base(vec)->size : (size_t)0);
}

/**
 * @brief cvector_element_size - gets the size of the elements
 * @param vec - the vector
 * @return the size as a size_t
 */
size_t cvector_element_size(cvector *vec)
{
    return (vec ? cvector_vec_to_base(vec)->element_size : (size_t)0);
}

/**
 * @brief cvector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
bool cvector_empty(cvector *vec)
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
void cvector_reserve(cvector *vec, size_t n)
{
    while (cvector_capacity(vec) < n)
    {
        cvector_grow(vec, n);
    }
}

/**
 * @brief cvector_init - Initialize a vector.  The vector must be NULL for this to do anything.
 * @param vec - the vector
 * @param capacity - vector capacity to reserve
 * @return void
 */
void cvector_init(cvector *vec, size_t capacity)
{

    while (!vec)
    {
        cvector_reserve(vec, capacity);
    }
}

/**
 * @brief cvector_erase - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
void cvector_erase(cvector *vec, size_t i)
{
    do
    {
        if (vec)
        {
            const size_t cv_sz__ = cvector_size(vec);
            if ((i) < cv_sz__)
            {
                cvector_set_size((vec), cv_sz__ - 1);
                memmove(
                    (vec) + (i),
                    (vec) + (i) + 1,
                    sizeof(*(vec)) * (cv_sz__ - 1 - (i)));
            }
        }
    } while (0);
}

/**
 * @brief cvector_clear - erase all of the elements in the vector
 * @param vec - the vector
 * @return void
 */
void cvector_clear(cvector *vec)
{
    do
    {
        if (vec)
        {
            cvector_set_size(vec, 0);
        }
    } while (0);
}

/**
 * @brief cvector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
void cvector_free(cvector *vec)
{
    do
    {
        if (vec)
        {
            free(cvector_vec_to_base(vec));
        }
    } while (0);
}

/**
 * @brief cvector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
void *cvector_begin(cvector *vec)
{
    return (vec);
}

/**
 * @brief cvector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
void *cvector_end(cvector *vec)
{
    ((vec) ? &((vec)[cvector_size(vec)]) : NULL);
}

/* user request to use logarithmic growth algorithm */
#ifdef CVECTOR_LOGARITHMIC_GROWTH

/**
 * @brief cvector_compute_next_grow - returns an the computed size in next vector grow
 * size is increased by multiplication of 2
 * @param size - current size
 * @return size after next vector grow
 */
size_t cvector_compute_next_grow(size_t size)
{
    return ((size) ? ((size) << 1) : 1);
}

#else

/**
 * @brief cvector_compute_next_grow - returns an the computed size in next vector grow
 * size is increased by 1
 * @param size - current size
 * @return size after next vector grow
 */
size_t cvector_compute_next_grow(size_t size)
{
    return ((size) + 1);
}

#endif /* CVECTOR_LOGARITHMIC_GROWTH */

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
void cvector_push_back(cvector *vec, void *value)
{
    do
    {
        size_t cv_cap__ = cvector_capacity(vec);
        if (cv_cap__ <= cvector_size(vec))
        {
            cvector_grow((vec), cvector_compute_next_grow(cv_cap__));
        }
        memcpy(vec[cvector_size(vec)], value, cvector_element_size(vec));
        cvector_set_size((vec), cvector_size(vec) + 1);
    } while (0);
}

/**
 * @brief cvector_insert - insert element at position pos to the vector
 * @param vec - the vector
 * @param pos - position in the vector where the new elements are inserted.
 * @param val - value to be copied (or moved) to the inserted elements.
 * @return void
 */
void cvector_insert(cvector *vec, size_t pos, void *val)
{
    do
    {
        size_t cv_cap__ = cvector_capacity(vec);
        if (cv_cap__ <= cvector_size(vec))
        {
            cvector_grow((vec), cvector_compute_next_grow(cv_cap__));
        }
        if ((pos) < cvector_size(vec))
        {
            memmove(
                (vec) + (pos) + 1,
                (vec) + (pos),
                sizeof(*(vec)) * ((cvector_size(vec)) - (pos)));
        }
        (vec)[(pos)] = (val);
        cvector_set_size((vec), cvector_size(vec) + 1);
    } while (0);
}

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
void cvector_pop_back(cvector *vec)
{
    do
    {
        cvector_set_size((vec), cvector_size(vec) - 1);
    } while (0);
}

/**
 * @brief cvector_copy - copy a vector
 * @param from - the original vector
 * @param to - destination to which the function copy to
 * @return void
 */
void cvector_copy(cvector *from, cvector *to)
{
    do
    {
        if ((from))
        {
            cvector_grow(to, cvector_size(from));
            cvector_set_size(to, cvector_size(from));
            memcpy((to), (from), cvector_size(from) * sizeof(*(from)));
        }
    } while (0);
}

/**
 * @brief cvector_swap - exchanges the content of the vector by the content of another vector of the same type
 * @param vec - the original vector
 * @param other - the other vector to swap content with
 * @param type - the type of both vectors
 * @return void
 */
void cvector_swap(cvector *vec, cvector *other)
{
    do
    {
        if (vec && other)
        {
            cvector cv_swap__ = vec;
            vec = other;
            other = cv_swap__;
        }
    } while (0);
}

/**
 * @brief cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_capacity(cvector *vec, size_t size)
{
    do
    {
        if (vec)
        {
            cvector_vec_to_base(vec)->capacity = (size);
        }
    } while (0);
}

/**
 * @brief cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 * @internal
 */
void cvector_set_size(cvector *vec, size_t _size)
{
    do
    {
        if (vec)
        {
            cvector_vec_to_base(vec)->size = (_size);
        }
    } while (0);
}

/**
 * @brief cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param count - the new capacity to set
 * @return void
 * @internal
 */
void cvector_grow(cvector *vec, size_t count)
{

    const size_t NEW_SIZE = count * cvector_element_size(vec) + sizeof(cvector_metadata_t);

    if (vec)
    {
        void *old_vec_pointer = cvector_vec_to_base(vec);
        void *new_vec_pointer = realloc(old_vec_pointer, NEW_SIZE);
        assert(new_vec_pointer);
        vec = cvector_base_to_vec(new_vec_pointer);
    }
    else
    {
        void *new_vector = malloc(NEW_SIZE);
        assert(new_vector);
        vec = cvector_base_to_vec(new_vector);
        cvector_set_size(vec, 0);
    }

    cvector_set_capacity(vec, count);
}

/**
 * @brief cvector_shrink_to_fit - requests the container to reduce its capacity to fit its size
 * @param vec - the vector
 * @return void
 */
void cvector_shrink_to_fit(cvector *vec)
{
    do
    {
        if (vec)
        {
            const size_t cv_sz___ = cvector_size(vec);
            cvector_grow(vec, cv_sz___);
        }
    } while (0);
}

/**
 * @brief cvector_at - returns a reference to the element at position n in the vector.
 * @param vec - the vector
 * @param n - position of an element in the vector.
 * @return the element at the specified position in the vector.
 */
void *cvector_at(cvector *vec, size_t n)
{
    return ((vec) ? (((int)(n) < 0 || (size_t)(n) >= cvector_size(vec)) ? NULL : &(vec)[n]) : NULL);
}

/**
 * @brief cvector_front - returns a reference to the first element in the vector. Unlike member cvector_begin, which returns an iterator to this same element, this function returns a direct reference.
 * @return a reference to the first element in the vector container.
 */
void *cvector_front(cvector *vec)
{
    return ((vec) ? ((cvector_size(vec) > 0) ? cvector_at(vec, 0) : NULL) : NULL);
}

/**
 * @brief cvector_back - returns a reference to the last element in the vector.Unlike member cvector_end, which returns an iterator just past this element, this function returns a direct reference.
 * @return a reference to the last element in the vector.
 */
void *cvector_back(cvector *vec)
{
    return ((vec) ? ((cvector_size(vec) > 0) ? cvector_at(vec, cvector_size(vec) - 1) : NULL) : NULL);
}

/**
 * @brief cvector_resize - resizes the container to contain count elements.
 * @param vec - the vector
 * @param count - new size of the vector
 * @param value - the value to initialize new elements with
 * @return void
 */
void cvector_resize(cvector *vec, size_t count, void *value)
{
    do
    {
        if (vec)
        {
            size_t cv_sz_count__ = count;
            size_t cv_sz__ = cvector_vec_to_base(vec)->size;

            if (cv_sz_count__ > cv_sz__)
            {
                cvector_reserve((vec), cv_sz_count__);
                cvector_set_size((vec), cv_sz_count__);
                do
                {
                    memcpy(&vec[cv_sz__++], value, cvector_element_size(vec));
                } while (cv_sz__ < cv_sz_count__);
            }
            else
            {
                while (cv_sz_count__ < cv_sz__--)
                {
                    cvector_pop_back(vec);
                }
            }
        }
    } while (0);
}

#endif /* CVECTOR_H_ */
