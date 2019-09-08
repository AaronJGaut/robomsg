# Message transmission plan

* Add uint8 OPCODE at start of message
* transport frame consists of
    * 4 byte length (value is sizeof(length, opcode, message))
    * 2 byte opcode
    * 1 message contents


# Improving message gen

* Each field type/language has a class that knows how to write lines for that field and that language
* For C, use `buffer_stream`
