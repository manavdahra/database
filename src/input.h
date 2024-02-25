#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* input_buffer);

#endif