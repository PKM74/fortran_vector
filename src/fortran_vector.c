#include <stdio.h>
#include <inttypes.h>
#include "cvector.h"
#include "cvector_utils.h"

#define CVECTOR_LOGARITHMIC_GROWTH

/**
 * @param data_size The size of the element you are using this vector for.
 */
void *new_vector(size_t initial_size, size_t element_size, cvector_elem_destructor_t gc)
{

  // This is what insanity looks like.
  uint8_t raw_data[element_size];
  // memcpy(&raw_data, t, data_size);

  // printf("data size: %d\n", data_size);
  // for (int i = 0; i < data_size; i++)
  // {
  //   printf("%d ", raw_data[i]);
  // }
  // printf("\n");

  cvector_vector_type(typeof(raw_data)) *v = NULL;

  // We need this to trick C into creating the underlying structure.
  cvector_init(v, initial_size, gc);

  return v;
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