#include <stdio.h>
#include <stdint.h>

#define PARSE_ERROR  1
#define BOOL   _Bool
/*
Unicode符号范围     |        UTF-8编码方式
(十六进制)        |              （二进制）
----------------------+---------------------------------------------
0000 0000-0000 007F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/
/**
 * @brief utf8编码转unicode字符集(usc4)，最大支持4字节utf8编码，(4字节以上在中日韩文中为生僻字)
 * @param *utf8 utf8变长编码字节集1~4个字节
 * @param *unicode utf8编码转unicode字符集结果，最大4个字节，返回的字节序与utf8编码序一致
 * @return length 0：utf8解码异常，others：本次utf8编码长度
 */
uint8_t UTF8ToUnicode(uint8_t *utf8, uint32_t *unicode) {
    const uint8_t lut_size = 3;
    const uint8_t length_lut[] = {2, 3, 4};
    const uint8_t range_lut[] = {0xE0, 0xF0, 0xF8};
    const uint8_t mask_lut[] = {0x1F, 0x0F, 0x07};

    uint8_t length = 0;
    unsigned int b = *(utf8 + 0);
    uint32_t i = 0;

    if(utf8 == NULL) {
        *unicode = 0;
        return 1;
    }
    // utf8编码兼容ASCII编码,使用0xxxxxx 表示00~7F
    if(b < 0x80) {
        *unicode =  b;
        return 1;
    }
    // utf8不兼容ISO8859-1 ASCII拓展字符集
    // 同时最大支持编码6个字节即1111110X
    if(b < 0xC0 || b > 0xFD) {
        *unicode = 0;
        return PARSE_ERROR;
    }
    for(i = 0; i < lut_size; i++) {
        if(b < range_lut[i]) {
            *unicode = b & mask_lut[i];
            length = length_lut[i];
            break;
        }
    }
    // 超过四字节的utf8编码不进行解析
    if(length == 0) {
        *unicode = 0;
        return PARSE_ERROR;
    }
    // 取后续字节数据
    for(i = 1; i < length; i++ ) {
        b = *(utf8 + i);
        // 多字节utf8编码后续字节范围10xxxxxx‬~‭10111111‬
        if( b < 0x80 || b > 0xBF ) {
            break;
        }
        *unicode <<= 6;
        // ‭00111111‬
        *unicode |= (b & 0x3F);
    }
    // 长度校验
    return (i < length) ? PARSE_ERROR : length;
}



/**
 * @brief 4字节unicode(usc4)字符集转utf16编码
 * @param unicode unicode字符值
 * @param *utf16 utf16编码结果
 * @return utf16长度，(2字节)单位
 */
uint8_t UnicodeToUTF16(uint32_t unicode, uint16_t *utf16) {
    // Unicode范围 U+000~U+FFFF
    // utf16编码方式：2 Byte存储，编码后等于Unicode值
    if(unicode <= 0xFFFF) {
		if(utf16 != NULL) {
			*utf16 = (unicode & 0xFFFF);
		}
		return 1;
	}else if( unicode <= 0xEFFFF ) {
		if( utf16 != NULL ) {
		    // 高10位
		    *(utf16 + 0) = 0xD800 + (unicode >> 10) - 0x40;
            // 低10位
		    *(utf16 + 1) = 0xDC00 + (unicode &0x03FF);
		}
		return 2;
	}

    return 0;
}



/**
 * @brief 使用utf16.lut查找表查询unicode对应的gb2312编码
 * @brief unicode小端方式输入，gb2312大端方式输出
 * @param unicode 双字节unicode码, 小端模式
 * @return gb2312 gb2312字符集，大端模式
 * */
unsigned short bsearch_gb2312(uint16_t unicode) {
	FILE *fp;
	BOOL success;
	uint16_t readin = 0;
    unsigned char pack[4];
	uint32_t  group;
	int32_t start, middle, end;
	short gb2312  = 0;

	fp = fopen("gb2312.bin", "r");
	if(fp != NULL) {
        fseek(fp, 0, SEEK_END);
        long length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
		// 四字节一组，低两字节为unicode，高两字节为gb2312
		group = (length / sizeof(uint32_t));
		middle = group / 2;
		end = group;
		start = -1;
		do {
			// 二分法，从中间查起
			success = fread(pack, 1,sizeof(uint32_t), fp);
			if(!success || middle <= 0 || middle >= (group - 1)) {
				break;
			}
			readin = (uint16_t)(pack[0] | pack[1] << 8);
			if(unicode < readin) {
				// 向左查询
				end = middle;
				middle -= ((end - start) / 2);
			}else if(unicode > readin) {
				// 向右查询
				start = middle;
				middle += ((end - start) / 2);
			}
		}while(unicode != readin);

        //printf("%x %x %x %x\n", pack[0], pack[1], pack[2], pack[3]);
		gb2312 = pack[2] << 8 | pack[3];
	}
    fclose(fp);
	return gb2312;
}
