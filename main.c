#include "aes_table.c"


#define GETU32(pt) (\
        ((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^\
        ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]) )
        
#define PUTU32(ct, st) {\
        (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16);\
        (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }


void printstate(unsigned char * in, int eol){
        for(int i = 0; i < 16; i++) {
                printf("%.2X", in[i]);

        }
        if (eol) {
            printf("\n");
        }

        return;
}

char ascii2hex(char in){
    char out = -1;

    if (('0' <= in) && (in <= '9'))
        out = in - '0';

    if (('A' <= in) && (in <= 'F'))
        out = in - 'A' + 10;

    if (('a' <= in) && (in <= 'f'))
        out = in - 'a' + 10;

    return out;
}

void asciiStr2hex (const char * in, char * out, int len){
    int j = 0;
    for (int i = 0; i < len; i += 2)
        out[j++]  = (ascii2hex(in[i ]) << 4) +  ascii2hex(in[i+1]);
}

int main(int argc, char * argv[]){
        unsigned char OUT[32];
        unsigned char IN[32];
        unsigned char CIPHER[32] = "00112233445566778899aabbccddeeff"; // default cipher text
        const char *p;
        if (argc <= 1) {
            p = (char*)CIPHER;
        } else {
            p = argv[1];
        }
        asciiStr2hex(p, (char *)IN, 32);
        //printstate(IN);

        aes_128_table_encrypt(IN, OUT);

        printstate(OUT, 0);

        return 0;
}
