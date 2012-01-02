#ifndef WTF8_WTF8_H
#define WTF8_WTF8_H


#ifdef _WIN32
#define uint32_t unsigned int
#define uint8_t unsigned char
#else
#include <stdint.h>
#endif


// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#define UTF8_ACCEPT 0
#define UTF8_REJECT 12

static const uint8_t wtf8_utf8d[] = {
  // The first part of the table maps bytes to character classes that
  // to reduce the size of the transition table and create bitmasks.
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
   7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
   8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

  // The second part is a transition table that maps a combination
  // of a state of the automaton and a character class to a state.
   0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
  12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
  12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
  12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
  12,36,12,12,12,12,12,12,12,12,12,12, 
};

/** Decode utf8 codepoint a byte at a time. Uses explictly user provided state variable,
  * that should be initialized to zero before first use. Places the result to codep
  * @return Returns UTF8_ACCEPT when a full codepoint achieved
  */
static inline uint32_t wtf8_decode_state(uint32_t* state, uint32_t* codep, uint32_t byte) {
  uint32_t type = wtf8_utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = wtf8_utf8d[256 + *state + type];
  return *state;
}



/** Decode a utf8 codepoint from a byte array. Reads maximum of maxbytes from str.
  * Places the result to result
  * @return The start of next codepoint sequence
  */
static inline const char* wtf8_decode(const char* str, int maxbytes, uint32_t* result) {

    const unsigned char* ustr = (unsigned char*)str;
    uint32_t state = 0;
    while(maxbytes--) {
        int res = wtf8_decode_state(&state, result, *ustr);
        ustr++;
        if(res == UTF8_ACCEPT) return (const char*)ustr;
    }

    *result = 0xfffd;
    
    return str;
    
}


static inline const char* wtf8_encode(uint32_t codepoint, char* str) {

    if( codepoint <= 0x7f) {
        str[0] = codepoint;
        str+=1;
    } else if( codepoint <= 0x7ff ) {
        str[0] = 0xc0 + (codepoint >> 6);
        str[1] = 0x80 + (codepoint & 0x3f);
        str+=2;
    } else if( codepoint <= 0xffff) {
        str[0] = 0xe0 + (codepoint >> 12);
        str[1] = 0x80 + ((codepoint >> 6) & 63);
        str[2] = 0x80 + (codepoint & 63);
        str+=3;
    } else if( codepoint <= 0x1ffff) {
        str[0] = 0xf0 + (codepoint >> 18);
        str[1] = 0x80 + ((codepoint >> 12) & 0x3f);
        str[2] = 0x80 + ((codepoint >> 6) & 0x3f);
        str[3] = 0x80 + (codepoint & 0x3f);
        str+=4;
    }
    
    
    return str;
}


static inline int wtf8_strlen(const char* str) {

    int count = 0;
    uint32_t state = 0;

    const unsigned char* ustr = (unsigned char*)str;
    uint32_t tmp;
    while(*ustr != 0) {
        int res = wtf8_decode_state(&state, &tmp, *ustr);
        ustr++;
        if(res == UTF8_ACCEPT) { count++; }
    }


    return count;
}

static inline int wtf8_strnlen(const char* str, int bytes) {

    int count = 0;
    uint32_t state = 0;

    const unsigned char* ustr = (unsigned char*)str;
    uint32_t tmp;
    while(bytes--) {
        if(*ustr == 0) break;
        int res = wtf8_decode_state(&state, &tmp, *ustr);
        ustr++;
        if(res == UTF8_ACCEPT) { count++; }
    }


    return count;
}



#ifdef _WIN32
#undef uint32_t 
#undef uint8_t
#endif


#endif
