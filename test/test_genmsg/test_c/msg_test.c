#include <stdio.h>
#include <stdbool.h>
#include "MyMessage.h"

int main()
{
    struct MyMessage *m = MyMessage_create();
    m->asdf = 5;
    m->qwer = strdup("qwer");
    m->myfoo.foo = 10;
    m->myfoo.pi = 3.14159;
    m->myfoo.i = strdup("hi");
    m->mybar.is_valid = true;

    unsigned int length;
    unsigned char *bytes = MyMessage_serialize(m, &length);

    for (size_t i = 0; i < length; ++i)
    {
        printf("%02x ", bytes[i]);
    }
    printf("\n");

    struct MyMessage *m2 = MyMessage_deserialize(bytes, length);

    MyMessage_free(m);
    MyMessage_free(m2);
    free(bytes);
    return 0;
}
