#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "cvector.h"
#include "cvector_utils.h"

#define CVECTOR_LOGARITHMIC_GROWTH

/**
 * @param data_size The size of the element you are using this vector for.
 */
void *new_vector(size_t initial_size, size_t element_size, cvector_elem_destructor_t gc)
{
  // Tell C how big our data type is.
  uint8_t raw_data[element_size];

  cvector_vector_type(typeof(raw_data)) *v = NULL;

  // We need this to force C into creating the underlying structure.
  cvector_init(v, initial_size, gc);

  return v;
}

/**
 * Free the underlying memory.
 */
void destroy_vector(cvector(void) vec)
{
  cvector_free(vec);
}

/**
 * Index into the vector.
 */
void *vector_at(cvector(void) vec, size_t i)
{
  return cvector_at(vec, i);
}

/**
 * Check if the vector is empty.
 */
bool vector_is_empty(cvector(void) vec)
{
  return cvector_empty(vec);
}

/**
 * Get the number of elements in the vector.
 */
size_t vector_size(cvector(void) * vec)
{
  return cvector_size(vec);
}

/**
 * Get the capacity of a vector.
 */
size_t vector_capacity(cvector(void) * vec)
{
  return cvector_capacity(vec);
}

/**
 * Request that capacity is equal to size.
 */
void vector_shrink_to_fit(cvector(void) * vec)
{
  cvector_shrink_to_fit(vec);
}

/**
 * Clear all elements in the vector.
 */
void vector_clear(cvector(void) * vec)
{
  cvector_clear(vec);
}



/**
 * Push an element to the back of the vector.
 */
void vector_push_back(cvector(void) * vec, void *new_element, size_t element_size)
{
  uint8_t raw_data[element_size];
  memcpy(&raw_data, new_element, element_size);

  cvector_push_back(vec, raw_data);
}
