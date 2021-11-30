#include <stdio.h>
#include <stdlib.h>

// wirte msgpack code in binary form using fwrite
int main()
{
    FILE *fp;
    //msgpack code
    char msgCode[] = "9301c3a76578616d706c65a67365636f6e64922ac2";
    fp = fopen("../msg_pack_bin_test.dat", "wb"); // "wb" is write binary
    fwrite(msgCode, sizeof(msgCode), 1, fp);

    fclose(fp);
    return 0;
}
