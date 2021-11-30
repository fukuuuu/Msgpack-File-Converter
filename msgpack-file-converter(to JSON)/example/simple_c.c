#include <msgpack.h>
#include <stdio.h>

void print(char const* buf,size_t len)
{
    for(size_t i = 0; i < len ; ++i)
        printf("%02x ", 0xff & buf[i]);
    printf("\n");
}

int main(void)
{
    msgpack_sbuffer sbuf; // for packing format
    msgpack_packer pk; // store packed format
    msgpack_zone mempool; // for packing data (memmory pool)
    msgpack_object deserialized; // store unpacked format

    /* msgpack::sbuffer is a simple buffer implementation. */
    msgpack_sbuffer_init(&sbuf);

    /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_pack_array(&pk, 3); // pack 3 spaces array
    msgpack_pack_int(&pk, 1); // 1st place is int 1
    msgpack_pack_true(&pk); // 2nd place is bool true
    msgpack_pack_str(&pk, 7); // 3rd place is str of 7 chars
    msgpack_pack_str_body(&pk, "example", 7); // which is 'example'

    // the packed msg is "93 01 c3 a7"

    print(sbuf.data, sbuf.size);

    /* deserialize the buffer into msgpack_object instance. */
    /* deserialized object is valid during the msgpack_zone instance alive. */
    msgpack_zone_init(&mempool, 2048);

    msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

    /* print the deserialized object. */
    msgpack_object_print(stdout, deserialized);
    puts("");

    // destroy the variables to get back the RAM sotrage
    msgpack_zone_destroy(&mempool);
    msgpack_sbuffer_destroy(&sbuf);

    return 0;
}
