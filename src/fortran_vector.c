#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "cvector.h"

/**
 * @param data_size The size of the element you are using this vector for.
 */
char *new_vector(size_t initial_size, size_t element_size)
{
  return cvector_init(initial_size, element_size);
}

/**
 * Free the underlying memory.
 */
void destroy_vector(char *vec)
{
  cvector_free(vec);
}

/**
 * Index into the vector.
 */
char *vector_get(char *vec, size_t index)
{
  return cvector_get(vec, index - 1);
}

/**
 * Set index of the vector.
 */
void vector_set(char *vec, size_t index, char *fortran_data)
{
  cvector_set(vec, index - 1, fortran_data);
}

/**
 * Check if the vector is empty.
 */
bool vector_is_empty(char *vec)
{
  return cvector_empty(vec);
}

/**
 * Get the number of elements in the vector.
 */
size_t vector_size(char *vec)
{
  return cvector_size(vec);
}

/**
 * Get the capacity of a vector.
 */
size_t vector_capacity(char *vec)
{
  return cvector_capacity(vec);
}

/**
 * Request that capacity is equal to size.
 */
void vector_shrink_to_fit(char **vec)
{
  cvector_shrink_to_fit(vec);
}

/**
 * Clear all elements in the vector.
 */
void vector_clear(char *vec)
{
  cvector_clear(vec);
}

/**
 * Insert an element into a index in the vector.
 */
void vector_insert(char **vec, size_t index, char *fortran_data, size_t element_size)
{
  cvector_insert(vec, index - 1, fortran_data);
}

/**
 * Remove an element at an index in the vector.
 */
void vector_remove(char *vec, size_t index)
{
  cvector_remove(vec, index - 1);
}

/**
 * Push an element to the back of the vector.
 */
void vector_push_back(char **vec, char *fortran_data, size_t element_size)
{
  cvector_push_back(vec, fortran_data);
}

/**
 * Removes the last element from the vector.
 */
void vector_pop_back(char *vec)
{
  cvector_pop_back(vec);
}

/**
 * Request the vector to reallocate to the new capacity.
 */
void vector_reserve(char **vec, size_t new_capacity)
{
  cvector_reserve(vec, new_capacity);
}

/**
 * Resize a vector to a new size.
 *
 * Requires a new default element.
 */
void vector_resize(char **vec, size_t new_size, char *default_element)
{
  cvector_resize(vec, new_size, default_element);
}

/**
 * Swap one vector's contents with another's.
 */
void vector_swap(char **vec, char **other, size_t element_size)
{
  cvector_swap(vec, other);
}
