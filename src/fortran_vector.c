#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "cvector.h"

/**
 * @param data_size The size of the element you are using this vector for.
 */
void *new_vector(size_t initial_size, size_t element_size)
{
  return cvector_init(initial_size, element_size);
}

/**
 * Free the underlying memory.
 */
void destroy_vector(void *vec)
{
  cvector_free(vec);
}

/**
 * Index into the vector.
 */
void *vector_get(void *vec, size_t index)
{
  return cvector_get(vec, index - 1);
}

/**
 * Set index of the vector.
 */
void vector_set(void *vec, size_t index, void *fortran_data)
{
  cvector_set(vec, index - 1, fortran_data);
}

/**
 * Check if the vector is empty.
 */
bool vector_is_empty(void *vec)
{
  return cvector_empty(vec);
}

/**
 * Get the number of elements in the vector.
 */
size_t vector_size(void *vec)
{
  return cvector_size(vec);
}

/**
 * Get the capacity of a vector.
 */
size_t vector_capacity(void *vec)
{
  return cvector_capacity(vec);
}

/**
 * Request that capacity is equal to size.
 */
void vector_shrink_to_fit(void *vec)
{
  cvector_shrink_to_fit(vec);
}

/**
 * Clear all elements in the vector.
 */
void vector_clear(void *vec)
{
  cvector_clear(vec);
}

/**
 * Insert an element into a index in the vector.
 */
void vector_insert(void *vec, size_t index, void *fortran_data, size_t element_size)
{
  cvector_insert(vec, index - 1, fortran_data);
}

/**
 * Remove an element at an index in the vector.
 */
void vector_remove(void *vec, size_t index)
{
  cvector_remove(vec, index - 1);
}

/**
 * Push an element to the back of the vector.
 */
void vector_push_back(void **vec, void *fortran_data, size_t element_size)
{
  cvector_push_back(vec, fortran_data);
}

/**
 * Removes the last element from the vector.
 */
void vector_pop_back(void *vec)
{
  cvector_pop_back(vec);
}

/**
 * Request the vector to reallocate to the new capacity.
 */
void vector_reserve(void **vec, size_t new_capacity)
{
  cvector_reserve(vec, new_capacity);
}

/**
 * Resize a vector to a new size.
 *
 * Requires a new default element.
 */
void vector_resize(void *vec, size_t new_size, void *default_element, size_t element_size)
{
  cvector_resize(vec, new_size, default_element);
}

/**
 * Swap one vector's contents with another's.
 */
void vector_swap(void *vec, void *other, size_t element_size)
{
  cvector_swap(vec, other);
}
