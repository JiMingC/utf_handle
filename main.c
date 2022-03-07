#include <stdio.h>
#include <stdint.h>
#include "utf_handle.h"
/*0x554a*/

extern const unsigned char bin_data[];
int main() {
    char bin_data2[] = {
        0x00,0x00,0x07,0x7E,0x75,0x04,0x55,0x04,    0x55,0x74,0x55,0x54,0x56,0x54,0x55,0x54,
	    0x55,0x54,0x55,0x54,0x75,0x74,0x55,0x54,    0x06,0x04,0x04,0x04,0x04,0x14,0x04,0x08,
        	0x00,0x00,0x3E,0xFF,0x22,0x04,0x24,0x04,    0x24,0xF4,0x28,0x94,0x24,0x94,0x24,0x94,
	0x22,0x94,0x22,0x94,0x22,0xF4,0x34,0x94,    0x28,0x04,0x20,0x04,0x20,0x14,0x20,0x08,
	0x10,0x20,0x10,0x40,0x10,0x88,0x11,0x04,    0x13,0xFE,0x7C,0x82,0x10,0x80,0x11,0xFC,
	0x12,0x20,0x10,0x20,0x13,0xFF,0x1C,0x20,    0x70,0x50,0x20,0x88,0x01,0x04,0x06,0x03,
	0x10,0x20,0x10,0x40,0x10,0x88,0x11,0x04,    0x7B,0xFE,0x10,0x82,0x10,0x80,0x11,0xFC,
	0x1A,0x20,0x70,0x20,0x17,0xFF,0x10,0x20,    0x10,0x50,0x10,0x88,0x51,0x04,0x26,0x03,
    };
    unsigned char c;
    for (int i = 0; i < 128;i++) {
        c = bin_data2[i];
        for (int j =0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }
    uint32_t buffer;
    //uint8_t utf8[] = "\xE4\xB8\xA5";
    char* utf8 = "蔡";
    uint16_t utf16[2] = {0};

    uint8_t len = UTF8ToUnicode(utf8, &buffer);

    printf("len:%d\n", len);
    printf("buffer:%x\n", buffer);
    len = UnicodeToUTF16(buffer, utf16);
    printf("len:%d\n", len);
    printf("utf16[0]:%x\n", utf16[0]);
    printf("utf16[0]:%x\n", utf16[1]);

    unsigned short code = utf16[0] ;
    unsigned short gb = bsearch_gb2312(code);
    printf("gb:%x\n", gb);

    printfGB2312(GetGB2312TFTidx(gb));

    utf8 = "孔";
    len = UTF8ToUnicode(utf8, &buffer);
    len = UnicodeToUTF16(buffer, utf16);
    code = utf16[0] ;
    gb = bsearch_gb2312(code);
    for (int i = 0; i < 32;i++) {
       c = bin_data[((gb & 0xFF) - 0xa1 + ((gb >> 8 &0xff) - 0xb0)*94 )*32+i];
        for (int j = 0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }

    utf8 = "文";
    len = UTF8ToUnicode(utf8, &buffer);
    len = UnicodeToUTF16(buffer, utf16);
    code = utf16[0] ;
    gb = bsearch_gb2312(code);
    for (int i = 0; i < 32;i++) {
       c = bin_data[((gb & 0xFF) - 0xa1 + ((gb >> 8 &0xff) - 0xb0)*94 )*32+i];
        for (int j = 0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }
    utf8 = "君";
    len = UTF8ToUnicode(utf8, &buffer);
    len = UnicodeToUTF16(buffer, utf16);
    code = utf16[0] ;
    gb = bsearch_gb2312(code);
    for (int i = 0; i < 32;i++) {
       c = bin_data[((gb & 0xFF) - 0xa1 + ((gb >> 8 &0xff) - 0xb0)*94 )*32+i];
        for (int j = 0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }
    utf8 = "在";
    len = UTF8ToUnicode(utf8, &buffer);
    len = UnicodeToUTF16(buffer, utf16);
    code = utf16[0] ;
    gb = bsearch_gb2312(code);
    for (int i = 0; i < 32;i++) {
       c = bin_data[((gb & 0xFF) - 0xa1 + ((gb >> 8 &0xff) - 0xb0)*94 )*32+i];
        for (int j = 0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }
    utf8 = "吗";
    len = UTF8ToUnicode(utf8, &buffer);
    len = UnicodeToUTF16(buffer, utf16);
    code = utf16[0] ;
    gb = bsearch_gb2312(code);
    for (int i = 0; i < 32;i++) {
       c = bin_data[((gb & 0xFF) - 0xa1 + ((gb >> 8 &0xff) - 0xb0)*94 )*32+i];
        for (int j = 0; j < 8; j++) {
            if (c & 0x80) {
                printf("*");
            } else {
                printf(" ");
            }
            c <<= 1;
        }
        if (i%2)
            printf("|\n");

    }
    return 0;
}
