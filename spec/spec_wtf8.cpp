#include "../wtf8.h"

#include "spec.h"


describe(wtf8, "wtf8_decode") {
    
    it("should decode codepoint from utf8 string in the single octet range 00-7f") {
        
        const unsigned char ustr1[]={ 1 };
        const unsigned char ustr2[]={ 0x32 };
        const unsigned char ustr3[]={ 0x7f };
        const unsigned char ustr_er[]={ 0x80 };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        
        unsigned int codepoint = 0;
        
        const char* res = 0;

        codepoint = 0;
        res = wtf8_decode(str1, 1, &codepoint);
        should_equal( codepoint, 1u);
        should_equal( res, str1+1 );

        codepoint = 0;
        res = wtf8_decode(str2, 1, &codepoint);
        should_equal( codepoint, 0x32u);
        should_equal( res, str2+1 );

        codepoint = 0;
        res = wtf8_decode(str3, 1, &codepoint);
        should_equal( codepoint, 0x7fu);
        should_equal( res, str3+1 );

        codepoint = 0;
        res = wtf8_decode(str_er, 1, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er );
        
    }

    it("should decode codepoint from utf8 string in the two octet range 80-7ff") {
        
        const unsigned char ustr1[]={ 0xc2u, 0x80u };
        const unsigned char ustr2[]={ 0xc4u, 0x80u };
        const unsigned char ustr3[]={ 0xdfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xdfu, 0xc0u };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        
        unsigned int codepoint = 0;
        
        const char* res = 0;

        codepoint = 0;
        res = wtf8_decode(str1, 2, &codepoint);
        should_equal( codepoint, 0x80u);
        should_equal( res, str1+2 );

        codepoint = 0;
        res = wtf8_decode(str2, 2, &codepoint);
        should_equal( codepoint, 0x100u);
        should_equal( res, str2+2 );

        codepoint = 0;
        res = wtf8_decode(str3, 2, &codepoint);
        should_equal( codepoint, 0x7ffu);
        should_equal( res, str3+2 );
        
        codepoint = 0;
        res = wtf8_decode(str_er, 2, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er );
        
    }

    it("should decode codepoint from utf8 string in the three octet range 800-ffff") {
        
        const unsigned char ustr1[]={ 0xe0u, 0xa0u, 0x80u };
        const unsigned char ustr2[]={ 0xe1u, 0x80u, 0x80u };
        const unsigned char ustr3[]={ 0xefu, 0xbfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xefu, 0xbfu, 0xc0u };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        
        unsigned int codepoint = 0;
        
        const char* res = 0;

        codepoint = 0;
        res = wtf8_decode(str1, 3, &codepoint);
        should_equal( codepoint, 0x800u);
        should_equal( res, str1+3 );

        codepoint = 0;
        res = wtf8_decode(str2, 3, &codepoint);
        should_equal( codepoint, 0x1000u);
        should_equal( res, str2+3 );

        codepoint = 0;
        res = wtf8_decode(str3, 3, &codepoint);
        should_equal( codepoint, 0xffffu);
        should_equal( res, str3+3 );
        
        codepoint = 0;
        res = wtf8_decode(str_er, 3, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er );
        
    }

    it("should decode codepoint from utf8 string in the four octet range 10000-1ffff") {
        
        const unsigned char ustr1[]={ 0xf0u, 0x90u, 0x80u, 0x80u };
        const unsigned char ustr2[]={ 0xf0u, 0x92u, 0x80u, 0x80u };
        const unsigned char ustr3[]={ 0xf0u, 0x9fu, 0xbfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xf0u, 0x9fu, 0xbfu, 0xc0u };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        
        unsigned int codepoint = 0;
        
        const char* res = 0;

        codepoint = 0;
        res = wtf8_decode(str1, 4, &codepoint);
        should_equal( codepoint, 0x10000u);
        should_equal( res, str1+4 );

        codepoint = 0;
        res = wtf8_decode(str2, 4, &codepoint);
        should_equal( codepoint, 0x12000u);
        should_equal( res, str2+4 );

        codepoint = 0;
        res = wtf8_decode(str3, 4, &codepoint);
        should_equal( codepoint, 0x1ffffu);
        should_equal( res, str3+4 );
        
        codepoint = 0;
        res = wtf8_decode(str_er, 4, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er );
        
    }
    
    it("should not allow overlong sequences") {
        const unsigned char ustr1[]={ 0xc0u, 0xafu };
        const unsigned char ustr2[]={ 0xe0u, 0x80u, 0xafu };
        const unsigned char ustr3[]={ 0xf0u, 0x80u, 0x80u, 0xafu };
        const unsigned char ustr4[]={ 0xf8u, 0x80u, 0x80u, 0x80u, 0xafu };
        const unsigned char ustr5[]={ 0xfcu, 0x80u, 0x80u, 0x80u, 0x80u, 0xafu };

        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str4 = (const char*)ustr4;
        const char* str5 = (const char*)ustr5;
        
        unsigned int codepoint;

        codepoint = 0;
        wtf8_decode(str1, 2, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str2, 3, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str3, 4, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str4, 5, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str5, 6, &codepoint);
        should_equal( codepoint, 0xfffdu);

        
    }

    it("should not allow maximum overlong sequences") {
        const unsigned char ustr1[]={ 0xc1u, 0xbfu };
        const unsigned char ustr2[]={ 0xe0u, 0x9fu, 0xbfu };
        const unsigned char ustr3[]={ 0xf0u, 0x8fu, 0xbfu, 0xbfu };
        const unsigned char ustr4[]={ 0xf8u, 0x87u, 0xbfu, 0xbfu, 0xbfu };
        const unsigned char ustr5[]={ 0xfcu, 0x83u, 0xbfu, 0xbfu, 0xbfu, 0xbfu };

        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str4 = (const char*)ustr4;
        const char* str5 = (const char*)ustr5;
        
        unsigned int codepoint;

        codepoint = 0;
        wtf8_decode(str1, 2, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str2, 3, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str3, 4, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str4, 5, &codepoint);
        should_equal( codepoint, 0xfffdu);

        codepoint = 0;
        wtf8_decode(str5, 6, &codepoint);
        should_equal( codepoint, 0xfffdu);

        
    }

    
}

