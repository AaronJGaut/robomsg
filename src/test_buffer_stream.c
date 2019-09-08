#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rmsg_buffer_stream.h"

struct Foo
{
    uint32_t n;
    float32_t pi;
    char *qwer;
    bool is_valid;
} typedef Foo;

int main()
{
    Foo foo1;
    uint32_t size = 0;

    foo1.n = 5;
    size += 4;

    foo1.pi = 3.14159;
    size += 4;

    foo1.qwer = "qwer";
    size += 8;

    foo1.is_valid = true;
    size += 1;

    uint8_t *buffer = malloc(sizeof(uint8_t) * size);

    buffer_stream bs;
    buffer_stream_status status;

    status = buffer_stream_init(&bs, buffer, size);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_write_uint32(&bs, foo1.n);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_write_float32(&bs, foo1.pi);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_write_string(&bs, foo1.qwer);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_write_bool(&bs, foo1.is_valid);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_seek(&bs, 0);
    assert(status == BUFFER_STREAM_SUCCESS);

    for (size_t i = 0; i < size; ++i)
    {
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    Foo foo2;

    status = buffer_stream_read_uint32(&bs, &foo1.n);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_read_float32(&bs, &foo1.pi);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_read_string(&bs, &foo1.qwer);
    assert(status == BUFFER_STREAM_SUCCESS);

    status = buffer_stream_read_bool(&bs, &foo1.is_valid);
    assert(status == BUFFER_STREAM_SUCCESS);

    printf("n: %d\npi: %f\nqwer: %s\nis_valid: %s\n", foo1.n, foo1.pi, foo1.qwer,
        foo1.is_valid ? "true" : "false");

    free(buffer);

    return 0;
}
