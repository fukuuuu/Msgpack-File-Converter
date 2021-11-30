#include <msgpack.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define UNPACKED_BUFFER_SIZE 2048

// function to unpack msgcode(in binary file) and converthem into JSON format
void unpack(char const* buf, size_t len)
{
    /* buf is allocated by client. */
    msgpack_unpacked result;
    size_t off = 0;
    msgpack_unpack_return ret;
    int i = 0;
    char unpacked_buffer[UNPACKED_BUFFER_SIZE];
    msgpack_unpacked_init(&result); // initiate the variable result
    ret = msgpack_unpack_next(&result, buf, len, &off); // read the entire object and then next

    // while loop to unpack msgcode format
    while (ret == MSGPACK_UNPACK_SUCCESS) // if it(ret) returns smth and is successfully unpacked, the loop continues
    {
        msgpack_object obj = result.data; // unpack the data and store it in this variable(obj)

        /* Use obj. */
        printf("Object no %d:\n", ++i);
        /*msgpack_object_print(stdout, obj);
        printf("\n");*/          
        msgpack_object_print_buffer(unpacked_buffer, UNPACKED_BUFFER_SIZE, obj);
        printf("%s\n", unpacked_buffer);

        //If you want to allocate something on the zone, you can use zone
        //msgpack_zone* zone = result.zone;
        //The lifetime of the obj and the zone,

        ret = msgpack_unpack_next(&result, buf, len, &off);
    }
    // delete this variable form the RAM, to save the storage
    msgpack_unpacked_destroy(&result); 

    if (ret == MSGPACK_UNPACK_CONTINUE) 
        printf("All msgpack_object in the buffer is consumed.\n");   
    else if (ret == MSGPACK_UNPACK_PARSE_ERROR) 
        printf("The data in the buf is invalid format.\n");
}

int main() 
{
    FILE *fp;
    char buff[255];
    int buffLength;
    char *pos = buff;
    
    fp = fopen("../msg_pack_bin_test.dat", "rb"); // read binary
    fread(buff, sizeof(buff), 1, fp);
    
    buffLength = strlen(buff)/2;
    // use this variable(array) to store the real hex number
    unsigned char msgHexCode[buffLength];
    
    // loop convert hex (string) to real hex number
    for (size_t count = 0; count < sizeof msgHexCode/sizeof *msgHexCode; count++)
    {
        // read 2 chars (ex '93') from pos(buffer) using "%2hhx" and convert it into real hex and store it(real hex) in msgHexCode(array)
        sscanf(pos, "%2hhx", &msgHexCode[count]);
        // sscanf => read sth and store it
        pos += 2; // move pos by 2 to read the next 2 chars
    }
    unpack(msgHexCode, sizeof(msgHexCode));


    /* check */
    //printf("file => %s\n", buff);
    //printf("length => %d", strlen(buff));

}