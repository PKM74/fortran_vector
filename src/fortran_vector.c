#include <stdio.h>
#include "cvector.h"
#include "cvector_utils.h"

void *new_vector(void *input_type, size_t data_size)
{

  // This is what insanity looks like.
  size_t raw_data[data_size];
  memcpy(&raw_data, input_type, data_size);

  // printf("data size: %d\n", data_size);
  // for (int i = 0; i < data_size; i++)
  // {
  //   printf("%d ", florf[i]);
  // }
  // printf("\n");

  cvector_vector_type(typeof(raw_data)) v = NULL;
}