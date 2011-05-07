#ifndef WTF8_WTF8_H
#define WTF8_WTF8_H

#ifdef __cplusplus
extern "C" {
#endif


static inline const char* decode_utf8(const char* str, int maxbytes, unsigned int* result) {

    const unsigned char* ustr = (unsigned char*)str;
    const unsigned int replacement_char = 0xfffd;

    if(maxbytes <= 0) result = 0;

    if(maxbytes >= 1 && ustr[0] <= 0x7f) {
        *result = ustr[0];
        return str+1;
    }

    *result = replacement_char;
    return str;
    
}





#ifdef __cplusplus
}
#endif

#endif
