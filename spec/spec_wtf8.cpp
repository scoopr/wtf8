#include "../wtf8.h"

#include "spec.h"


describe(wtf8, "decode") {
    
    it("should decode codepoint from utf8 string in the single octet range 00-7f") {
        
        const char str1[]={ 1 };
        const char str2[]={ 0x32 };
        const char str3[]={ 0x7f };
        const char str_er[]={ 0x80 };
        
        unsigned int codepoint = 0;
        
        const char* res = 0;

        codepoint = 0;
        res = decode_utf8(str1, 1, &codepoint);
        should_equal( codepoint, 1);
        should_equal( res, str1+1 );

        codepoint = 0;
        res = decode_utf8(str2, 1, &codepoint);
        should_equal( codepoint, 0x32);
        should_equal( res, str2+1 );

        codepoint = 0;
        res = decode_utf8(str3, 1, &codepoint);
        should_equal( codepoint, 0x7f);
        should_equal( res, str3+1 );

        codepoint = 0;
        res = decode_utf8(str_er, 1, &codepoint);
        should_equal( codepoint, 0xfffd);
        should_equal( res, str_er );
        
    }
    
}

