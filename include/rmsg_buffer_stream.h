#ifndef BUFFER_STREAM_H
#define BUFFER_STREAM_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rmsg_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct buffer_stream
{
    uint8_t *bytes;
    size_t length;
    uint32_t offset;
} buffer_stream;

typedef enum buffer_stream_status {
    BUFFER_STREAM_SUCCESS = 0,
    BUFFER_STREAM_ERROR_NULL_POINTER = 1,
    BUFFER_STREAM_ERROR_OUT_OF_BOUNDS = 2,
    BUFFER_STREAM_ERROR_OVERFLOW = 4,
    BUFFER_STREAM_ERROR_UNKNOWN = 128,
} buffer_stream_status;

buffer_stream_status buffer_stream_create(buffer_stream **bs_ptr, uint8_t *bytes, size_t length);
buffer_stream_status buffer_stream_init(buffer_stream *bs_ptr, uint8_t *bytes, size_t length);
buffer_stream_status buffer_stream_free(buffer_stream *bs);

buffer_stream_status buffer_stream_advance(buffer_stream *bs, uint32_t delta);
buffer_stream_status buffer_stream_check_space(buffer_stream *bs, uint32_t delta);
buffer_stream_status buffer_stream_seek(buffer_stream *bs, uint32_t new_offset);

buffer_stream_status buffer_stream_read_bytes(buffer_stream *bs, void *val, uint32_t n);
buffer_stream_status buffer_stream_read_bool(buffer_stream *bs, bool *val);
buffer_stream_status buffer_stream_read_uint8(buffer_stream *bs, uint8_t *val);
buffer_stream_status buffer_stream_read_uint32(buffer_stream *bs, uint32_t *val);
buffer_stream_status buffer_stream_read_float32(buffer_stream *bs, float32_t *val);
buffer_stream_status buffer_stream_read_float64(buffer_stream *bs, float64_t *val);
buffer_stream_status buffer_stream_read_string(buffer_stream *bs, char **val);

buffer_stream_status buffer_stream_write_bytes(buffer_stream *bs, void *val, uint32_t n);
buffer_stream_status buffer_stream_write_bool(buffer_stream *bs, bool val);
buffer_stream_status buffer_stream_write_uint8(buffer_stream *bs, uint8_t val);
buffer_stream_status buffer_stream_write_uint32(buffer_stream *bs, uint32_t val);
buffer_stream_status buffer_stream_write_float32(buffer_stream *bs, float32_t val);
buffer_stream_status buffer_stream_write_float64(buffer_stream *bs, float64_t val);
buffer_stream_status buffer_stream_write_string(buffer_stream *bs, char *val);

buffer_stream_status buffer_stream_create(buffer_stream **bs_ptr, uint8_t *bytes, size_t length)
{
    buffer_stream *bs = malloc(sizeof(buffer_stream));
    buffer_stream_status status = buffer_stream_init(bs, bytes, length);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        free(bs);
        return status;
    }
    *bs_ptr = bs;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_init(buffer_stream *bs, uint8_t *bytes, size_t length)
{
    if (!bytes)
    {
        return BUFFER_STREAM_ERROR_NULL_POINTER;
    }
    bs->bytes = bytes;
    bs->length = length;
    bs->offset = 0;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_free(buffer_stream *bs)
{
    free(bs);
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_advance(buffer_stream *bs, uint32_t delta)
{
    buffer_stream_status status = buffer_stream_check_space(bs, delta);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    bs->offset += delta;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_check_space(buffer_stream *bs, uint32_t delta)
{
    if (bs->offset + delta < bs->offset)
    {
        return BUFFER_STREAM_ERROR_OVERFLOW;
    }
    if (bs->offset + delta > bs->length)
    {
        return BUFFER_STREAM_ERROR_OUT_OF_BOUNDS;
    }
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_seek(buffer_stream *bs, uint32_t new_offset)
{
    if (new_offset > bs->length)
    {
        return BUFFER_STREAM_ERROR_OUT_OF_BOUNDS;
    }
    bs->offset = new_offset;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_read_bytes(buffer_stream *bs, void *val, uint32_t n)
{
    if (!val)
    {
        return BUFFER_STREAM_ERROR_NULL_POINTER;
    }
    buffer_stream_status status = buffer_stream_check_space(bs, n);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    memcpy(val, bs->bytes + bs->offset, n);
    bs->offset += n;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_read_bool(buffer_stream *bs, bool *val)
{
    return buffer_stream_read_bytes(bs, val, 1);
}

buffer_stream_status buffer_stream_read_uint8(buffer_stream *bs, uint8_t *val)
{
    return buffer_stream_read_bytes(bs, val, 1);
}

buffer_stream_status buffer_stream_read_uint32(buffer_stream *bs, uint32_t *val)
{
    return buffer_stream_read_bytes(bs, val, 4);
}

buffer_stream_status buffer_stream_read_float32(buffer_stream *bs, float32_t *val)
{
    return buffer_stream_read_bytes(bs, val, 4);
}

buffer_stream_status buffer_stream_read_float64(buffer_stream *bs, float64_t *val)
{
    return buffer_stream_read_bytes(bs, val, 8);
}

buffer_stream_status buffer_stream_read_string(buffer_stream *bs, char **val)
{
    uint32_t str_len;
    buffer_stream_status status;
    status = buffer_stream_read_uint32(bs, &str_len);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    *val = malloc(sizeof(char) * (str_len + 1));
    status = buffer_stream_read_bytes(bs, *val, str_len);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        free(*val);
        return status;
    }
    (*val)[str_len] = 0;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_write_bytes(buffer_stream *bs, void *val, uint32_t n)
{
    if (!val)
    {
        return BUFFER_STREAM_ERROR_NULL_POINTER;
    }
    buffer_stream_status status = buffer_stream_check_space(bs, n);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    memcpy(bs->bytes + bs->offset, val, n);
    bs->offset += n;
    return BUFFER_STREAM_SUCCESS;
}

buffer_stream_status buffer_stream_write_bool(buffer_stream *bs, bool val)
{
    return buffer_stream_write_bytes(bs, &val, 1);
}

buffer_stream_status buffer_stream_write_uint8(buffer_stream *bs, uint8_t val)
{
    return buffer_stream_write_bytes(bs, &val, 1);
}

buffer_stream_status buffer_stream_write_uint32(buffer_stream *bs, uint32_t val)
{
    return buffer_stream_write_bytes(bs, &val, 4);
}

buffer_stream_status buffer_stream_write_float32(buffer_stream *bs, float32_t val)
{
    return buffer_stream_write_bytes(bs, &val, 4);
}

buffer_stream_status buffer_stream_write_float64(buffer_stream *bs, float64_t val)
{
    return buffer_stream_write_bytes(bs, &val, 8);
}

buffer_stream_status buffer_stream_write_string(buffer_stream *bs, char *val)
{
    if (!val)
    {
        return BUFFER_STREAM_ERROR_NULL_POINTER;
    }
    uint32_t str_len = strlen(val);
    buffer_stream_status status;
    status = buffer_stream_write_uint32(bs, str_len);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    status = buffer_stream_write_bytes(bs, val, str_len);
    if (status != BUFFER_STREAM_SUCCESS)
    {
        return status;
    }
    return BUFFER_STREAM_SUCCESS;
}

#ifdef __cplusplus
}
#endif


#endif  // BUFFER_STREAM_H
