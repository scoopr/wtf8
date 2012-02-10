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
        should_equal( res, str_er+1 );
        
    }

    it("should decode codepoint from utf8 string in the two octet range 80-7ff") {
        
        const unsigned char ustr1[]={ 0xc2u, 0x80u };
        const unsigned char ustr2[]={ 0xc4u, 0x80u };
        const unsigned char ustr3[]={ 0xdfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xdfu, 0xc0u };
        const unsigned char ustr_er2[]={ 0xdfu };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        const char* str_er2 = (const char*)ustr_er2;
        
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
        should_equal( res, str_er+2 );

        codepoint = 0;
        res = wtf8_decode(str_er2, 1, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er2+1 );
        
    }

    it("should decode codepoint from utf8 string in the three octet range 800-ffff") {
        
        const unsigned char ustr1[]={ 0xe0u, 0xa0u, 0x80u };
        const unsigned char ustr2[]={ 0xe1u, 0x80u, 0x80u };
        const unsigned char ustr3[]={ 0xefu, 0xbfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xefu, 0xbfu, 0xc0u };
        const unsigned char ustr_er2[]={ 0xefu, 0xbfu };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        const char* str_er2 = (const char*)ustr_er2;
        
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
        should_equal( res, str_er+3 );

        codepoint = 0;
        res = wtf8_decode(str_er2, 2, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er2+2 );
        
    }

    it("should decode codepoint from utf8 string in the four octet range 10000-1ffff") {
        
        const unsigned char ustr1[]={ 0xf0u, 0x90u, 0x80u, 0x80u };
        const unsigned char ustr2[]={ 0xf0u, 0x92u, 0x80u, 0x80u };
        const unsigned char ustr3[]={ 0xf0u, 0x9fu, 0xbfu, 0xbfu };
        const unsigned char ustr_er[]={ 0xf0u, 0x9fu, 0xbfu, 0xc0u };
        const unsigned char ustr_er2[]={ 0xf0u, 0x9fu, 0xbfu };
        
        const char* str1 = (const char*)ustr1;
        const char* str2 = (const char*)ustr2;
        const char* str3 = (const char*)ustr3;
        const char* str_er = (const char*)ustr_er;
        const char* str_er2 = (const char*)ustr_er2;
        
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
        should_equal( res, str_er+4 );

        codepoint = 0;
        res = wtf8_decode(str_er2, 3, &codepoint);
        should_equal( codepoint, 0xfffdu);
        should_equal( res, str_er2+3 );
        
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

    it("should not allow codepoints designated as surrogates") {
        for(size_t i = 0xa0; i <= 0xbf; ++i) {
            for(size_t j = 0x80; j <= 0xbf; ++j) {
                const unsigned char ustr1[]={ 0xedu, i, j };
                const char* str1 = (const char*)ustr1;
                unsigned int codepoint = 0;
                wtf8_decode(str1, 3, &codepoint);
                should_equal( codepoint, 0xfffdu);
            }
        }
    }
}



describe(wtf8, "wtf8_encode") {

    it("should encode all valid codepoints to utf8") {
        char buf[8];
        for(size_t i = 0; i < 0x1ffff; ++i)
        {
            // Skip surrogates, as they are not allowed in utf8
            if( i >= 0xd800 && i <= 0xdfff ) continue;

            memset(buf, 0, 8);

            const char* ret1 = wtf8_encode(i, buf);
            uint32_t res = 0;
            const char* ret2 = wtf8_decode(buf,7,&res);
            should_equal( i, res );
            should_equal( ret1, ret2 );
        }
    }
}


describe(wtf8, "wtf8_strlen") {

    it("should count distinct codepoints") {

        const char* str1 = "foobar";
        const char* str2 = "foob\xc3\xa6r";
        const char* str3 = "foob\xf0\x9f\x99\x88r";

        should_equal( wtf8_strlen(str1), 6);
        should_equal( wtf8_strlen(str2), 6);
        should_equal( wtf8_strlen(str3), 6);

    }

}

describe(wtf8, "wtf8_strnlen") {

    it("should count distinct codepoints") {

        const char* str1 = "foobar";
        const char* str2 = "foob\xc3\xa6r";
        const char* str3 = "foob\xf0\x9f\x99\x88r";

        should_equal( wtf8_strnlen(str1,6), 6);
        should_equal( wtf8_strnlen(str2,7), 6);
        should_equal( wtf8_strnlen(str3,9), 6);

    }

}

describe(wtf8, "wtf8_is_continuation_byte") {
    it("should return true if a given byte is not the initial byte of a utf8 sequence") {
        const char* str1 = "f";
        const char* str2 = "f\xc3\xa6r";
        const char* str3 = "f\xf0\x9f\x99\x88r";
        should_be_false( wtf8_is_continuation_byte( str1[0] ) );

        should_be_false( wtf8_is_continuation_byte( str2[0] ) );
        should_be_false( wtf8_is_continuation_byte( str2[1] ) );
        should_be_true( wtf8_is_continuation_byte( str2[2] ) );

        should_be_false( wtf8_is_continuation_byte( str3[0] ) );
        should_be_false( wtf8_is_continuation_byte( str3[1] ) );
        should_be_true( wtf8_is_continuation_byte( str3[2] ) );
        should_be_true( wtf8_is_continuation_byte( str3[3] ) );
        should_be_true( wtf8_is_continuation_byte( str3[4] ) );
    }
}

describe(wtf8, "wtf8_is_initial_byte") {
    it("should return true if a given byte is the initial byte of a utf8 sequence") {
        const char* str1 = "f";
        const char* str2 = "f\xc3\xa6r";
        const char* str3 = "f\xf0\x9f\x99\x88r";
        should_be_true( wtf8_is_initial_byte( str1[0] ) );

        should_be_true( wtf8_is_initial_byte( str2[0] ) );
        should_be_true( wtf8_is_initial_byte( str2[1] ) );
        should_be_false( wtf8_is_initial_byte( str2[2] ) );

        should_be_true( wtf8_is_initial_byte( str3[0] ) );
        should_be_true( wtf8_is_initial_byte( str3[1] ) );
        should_be_false( wtf8_is_initial_byte( str3[2] ) );
        should_be_false( wtf8_is_initial_byte( str3[3] ) );
        should_be_false( wtf8_is_initial_byte( str3[4] ) );
    }
}
