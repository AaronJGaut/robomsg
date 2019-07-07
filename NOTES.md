# Message transmission plan

* Add uint8 OPCODE at start of message
* frame consits of
    * 4 byte header: uint32 body length
    * body: 0 or more messages


# Improving message gen

* Each field type/language has a class that knows how to write lines for that field and that language
* For C, use `buffer_stream`
