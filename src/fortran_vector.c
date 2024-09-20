#include <stdio.h>
#include <inttypes.h>
#include "cvector.h"
#include "cvector_utils.h"

/**
 * @param data_size The size of the element you are using this vector for.
 */
void *new_vector(size_t data_size)
{

  // This is what insanity looks like.
  uint8_t raw_data[data_size];
  // memcpy(&raw_data, t, data_size);

  // printf("data size: %d\n", data_size);
  // for (int i = 0; i < data_size; i++)
  // {
  //   printf("%d ", raw_data[i]);
  // }
  // printf("\n");

  cvector_vector_type(typeof(raw_data)) v = NULL;

  return v;
}

void push_back(cvector(void) * vec, void *new_element, size_t data_size)
{
  uint8_t raw_data[data_size];
  memcpy(&raw_data, new_element, data_size);

  cvector_push_back(vec, raw_data);
}